// $Id: Standard_EINode.cpp 2235 2013-02-06 20:18:09Z dfeiock $

#include "Standard_EINode.h"

#if !defined (__OASIS_INLINE__)
#include "Standard_EINode.inl"
#endif

#include "LocalDataChannel_i.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include "oasis/probes/Software_Probe_Factory.h"

#include "ace/Get_Opt.h"
#include "ace/Dynamic_Service.h"
#include "ace/Service_Config.h"
#include "ace/OS_NS_unistd.h"

#include "boost/bind.hpp"

#include <sstream>

namespace OASIS
{
//
// Standard_EINode
//
Standard_EINode::Standard_EINode (void)
: is_active_ (false),
  reconnect_timeout_ (1),
  connect_task_ (this)
{
  Local_Data_Channel_i * channel = 0;
  ACE_NEW (channel,
           Local_Data_Channel_i (this));
  this->local_channel_.reset (channel);
}

//
// ~Standard_EINode
//
Standard_EINode::~Standard_EINode (void)
{
  if (this->is_active_)
  {
    this->deactivate ();
    this->destroy ();
  }
  else
  {
    if (0 != this->channel_)
      this->destroy ();
  }
}

//
// get_directive_name
//
std::string get_directive_name (const std::string & directive)
{
  std::istringstream istr (directive);
  std::string type, name;

  istr >> type >> name;

  return name;
}

//
// init
//
int Standard_EINode::init (int argc, char * argv [])
{
  ACE_CString config_file;

  // Parse the remaining command-line options. These options will
  // be specific to OASIS and the EINode.
  const char * optargs = "c:";
  ACE_Get_Opt get_opt (argc, argv, optargs);

  get_opt.long_option ("config", 'c', ACE_Get_Opt::ARG_REQUIRED);

  int opt = 0;

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("config", get_opt.long_option ()))
        config_file = get_opt.opt_arg ();
      break;

    case 'c':
      config_file = get_opt.opt_arg ();
      break;
    }
  }

  if (!config_file.empty ())
  {
    // We should load the configuration if it was defined in the
    // command-line options.
    if (0 != this->load_configuration (config_file.c_str ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to load configuration\n")),
                         -1);
  }

  return 0;
}

//
// destroy
//
void Standard_EINode::destroy (void)
{
  // Cleanup probes
  {
    ACE_Write_Guard<ACE_RW_Thread_Mutex> guard(this->probes_.mutex());

    for (SoftwareProbe_Hash_Map::iterator it = this->probes_.begin();
         it != this->probes_.end();
         ++it )
    {
  	std::auto_ptr<Software_Probe_Impl> probe(it->item());
        it->item() = 0;
	probe->fini();     
    }
  }
  this->probes_.unbind_all();

  // Remove the data channel service from the EI node.
  std::string name = get_directive_name (this->config_.data_channel ().directive_);

  if (0 != ACE_Service_Config::global ()->remove (name.c_str ()))
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to remove %s service\n"),
                name.c_str ()));

  this->channel_ = 0;
}

//
// load_software_probe
//
int Standard_EINode::
load_software_probe (const Einode_Configuration::Software_Probe & probe)
{
  ACE_DLL module;

  if (0 != module.open (probe.location_.c_str (), ACE_DEFAULT_SHLIB_MODE, 0))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open %s; %s"),
                       probe.location_.c_str (),
                       module.error ()),
                       -1);

  // Extract the entry point from the module.
  void * symbol = module.symbol (probe.entrypoint_.c_str ());

  if (symbol == 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - symbol '%s' does not exist\n"),
                       probe.entrypoint_.c_str ()),
                       -1);

  // Convert to function pointer that returns to correct type.
  typedef ::OASIS::Software_Probe_Factory * (* ENTRYPOINT) (void);
  ENTRYPOINT funcptr = (ENTRYPOINT) symbol;

  // Create the software probe factory.
  std::auto_ptr<Software_Probe_Factory> factory(funcptr ());

  if (0 == factory.get())
    return -1;

  // Now, create the software probe using the factory.
  std::auto_ptr<Software_Probe_Impl> probe_impl(factory->create ());

  // Initialize the software probe and register it.
  if (0 != probe_impl->init (probe.params_.c_str (), probe.name_.c_str ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to initialize probe %s\n"),
                       probe.name_.c_str ()),
                       -1);

  if (0 != this->register_probe (probe_impl.get()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to register probe %s\n"),
                       probe.name_.c_str ()),
                       -1);
  probe_impl.release();

  return 0;
}

//
// register_probe
//
int Standard_EINode::
register_probe (Software_Probe_Impl * probe)
{
  if (!probe->is_initalized ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - cannot register an uninitalized probe\n")),
                       -1);

  int retval = this->probes_.bind (probe->instance_name ().c_str (), probe);

  if (0 != retval)
    return retval;

  // Update the probes instance name and set its local channel.
  probe->set_data_channel (this->local_channel_.get ());

  return 0;
}

//
// activate
//
int Standard_EINode::activate (void)
{
  // Make sure there is a data channel is set. There is no need to
  // continue if there is no data channel. This means that there is
  // no place to send the data!
  if (0 == this->channel_)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - the data channel is NIL\n")),
                       -1);

  // Activate the connect task if the channel isn't connected
  if (this->channel_->is_connected ())
    return 0;

  this->connect_task_.set_data_channel (this->channel_);
  this->connect_task_.activate (this->reconnect_timeout_);
  return 0;
}

//
// deactivate
//
int Standard_EINode::deactivate (void)
{
  for (SoftwareProbe_Hash_Map::iterator iter = this->probes_.begin ();
       iter != this->probes_.end ();
       ++iter)
    (*iter).int_id_->deactivate ();

  this->connect_task_.deactivate ();
  this->is_active_ = false;

  return 0;
}

//
// unregister_probe
//
void Standard_EINode::unregister_probe (const char * name)
{
  // Remove the probe from the collection.
  Software_Probe_Impl * probe = 0;
  this->probes_.unbind (name, probe);

  if (0 != probe)
  {
    // Finalize the probe.
    if (0 != probe->fini ())
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - fini () failed for %s\n"),
                  probe->instance_name ().c_str ()));

    delete probe;
  }
}

//
// load_configuration
//
int Standard_EINode::load_configuration (const char * config)
{
  // Load the configuration file.
  if (!this->config_.load_file (config))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read %s\n"),
                       config),
                       -1);

  if (!this->config_.validate ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - invalid configuration\n"),
                       config),
                       -1);

  // Load the one and only data channel, which is defined as an
  // ACE service.
  int retval =
    ACE_Service_Config::global ()->process_directive (
    this->config_.data_channel ().directive_.c_str ());

  if (0 != retval)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to initalize ")
                       ACE_TEXT ("data channel for directive [%s]\n"),
                       this->config_.data_channel ().directive_.c_str ()),
                       -1);

  // Locate the loaded data channel. We can do this by extracting
  // its name, then locating it in the service repository.
  std::string name = get_directive_name (this->config_.data_channel ().directive_);

  this->channel_ =
    ACE_Dynamic_Service <Data_Channel_Service>::
    instance (ACE_Service_Config::global (), name.c_str ());

  if (0 == this->channel_)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to located channel\n")),
                       -1);

  this->channel_->set_einode (this);
  this->local_channel_->packager (this->channel_->packager ());

  // Load each of the software probes.
  std::for_each (this->config_.data_channel ().probes_.begin (),
                 this->config_.data_channel ().probes_.end (),
                 boost::bind (&Standard_EINode::load_software_probe, this, _1));

  // Finally, set the reconnect timeout from the config
  this->reconnect_timeout_ = this->config_.reconnect_timeout ();

  return 0;
}

//
// handle_command
//
int Standard_EINode::handle_command (const char * command)
{
  // Locate the probe's name in the command.
  const char * pass_thru = ACE_OS::strchr (command, ' ');

  if (pass_thru == 0)
    return -1;

  // Extract the probe's name from the command, the locate the probe
  // in the probes that are currently loaded into memory.
  ACE_CString probe_name (command, pass_thru - command);

  Software_Probe_Impl * probe_impl = 0;
  if (0 != this->probes_.find (probe_name, probe_impl))
    return -1;

  // Pass the remaining portion of the command to the probe.
  probe_impl->handle_command (pass_thru);

  return 0;
}

//
// send_data
//
void Standard_EINode::send_data (const char * data, size_t length)
{
  if (0 != this->channel_ && this->is_active_)
  {
    try
    {
      this->channel_->send_data (data, length);
    }
    catch (const ::OASIS::Transient_Error & ex)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - %s\n"),
                  ex.what ()));
      this->activate ();
    }
  }
}

//
// handle_connect
//
int Standard_EINode::handle_connect (void)
{
  // Connect the data channel
  this->channel_->connect ();

  // Register the software probes with the DAC.
  if (0 != this->channel_->perform_registration (this->probes_))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - registration failed\n")),
                       -1);

  // Activate the probes
  for (SoftwareProbe_Hash_Map::iterator iter = this->probes_.begin ();
       iter != this->probes_.end ();
       ++iter)
  {
    if (ACE_Time_Value::zero != (*iter).int_id_->flush_interval ())
      (*iter).int_id_->activate ();
  }

  this->is_active_ = true;
  return 0;
}

}

