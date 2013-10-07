// $Id: Tena_Publisher_Service.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "Tena_Publisher_Service.h"

#include "oasis/middleware/tena/bridges/Software_Probe_Bridge_Manager.h"
#include "oasis/middleware/tena/bridges/Software_Probe_Bridge.h"

#include "oasis/probes/Software_Probe_Header.h"

#include "ace/Service_Config.h"
#include "ace/Get_Opt.h"

OASIS_DAC_DATA_HANDLER_IMPL (_make_OASIS_Tena_Publisher_Service, OASIS::Tena_Publisher_Service)

namespace OASIS
{

//
// Archive_Data_Handler
//
Tena_Publisher_Service::Tena_Publisher_Service (void)
{

}

//
// ~Archive_Data_Handler
//
Tena_Publisher_Service::~Tena_Publisher_Service (void)
{

}

//
// init
//
int Tena_Publisher_Service::init (int argc, char * argv [])
{
  try
  {
    // Parse the command-line arguments.
    if (0 != this->parse_args (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to parse command-line\n")),
                         -1);

    // Initialize the TENA ApplicationConfiguration
    Tena_Publisher_Configuration * tena_config;
    ACE_NEW_RETURN (tena_config,
                    Tena_Publisher_Configuration (argc, argv, this->tena_config_.c_str ()),
                    -1);
    this->config_.reset (tena_config);

    // Initialize the TENA middleware.
    this->runtime_ = ::TENA::Middleware::init (this->config_->tenaConfiguration ());

    // Join the execution in the configuration file.
    ::TENA::Middleware::Endpoint endpoint = this->config_->getSetting("emEndpoint").getValue < ::TENA::Middleware::Endpoint > ();
    this->execution_ = this->runtime_->joinExecution (endpoint);

    ACE_ERROR ((LM_INFO,
                ACE_TEXT ("%T (%t) - %M - joining execution %s\n"),
                endpoint.toString ().c_str ()));

    // Join the session in the configuration file.
    std::string session = this->config_->getSetting("sessionName").getValue < std::string > ();
    this->session_ = this->execution_->createSession (session);

    ACE_ERROR ((LM_INFO,
                ACE_TEXT ("%T (%t) - %M - creating session %s\n"),
                session.c_str ()));

    return 0;
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - unknown exception caught\n")));
  }

  // Peform any cleanup operations.
  this->cleanup ();

  return -1;
}

//
// parse_args
//
int Tena_Publisher_Service::parse_args (int argc, char * argv [])
{
  // Now, parse our command-line options.
  const char * optargs = "b:";
  ACE_Get_Opt get_opt (argc, argv, optargs, 0);

  get_opt.long_option ("bridge", 'b', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("initial-values", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("tena-config", ACE_Get_Opt::ARG_REQUIRED);

  int opt = 0;
  ACE_CString bridge_files;

  while (EOF != (opt = get_opt ()))
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("bridge", get_opt.long_option ()))
        if (0 != this->load_bridge_manager (get_opt.opt_arg ()))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT("%T (%t) - %M - failed to load bridge manager\n")),
                             -1);

      if (0 == ACE_OS::strcmp ("initial-values", get_opt.long_option ()))
        this->bridge_initial_values_ = get_opt.opt_arg ();

      if (0 == ACE_OS::strcmp ("tena-config", get_opt.long_option ()))
        this->tena_config_ = get_opt.opt_arg ();

      break;

    case 'b':
      if (0 != this->load_bridge_manager (get_opt.opt_arg ()))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT("%T (%t) - %M - failed to load bridge manager\n")),
                             -1);
      break;
    }
  }

  return 0;
}

//
// fini
//
int Tena_Publisher_Service::fini (void)
{
  // Perform any cleanup operations.
  this->cleanup ();

  return -1;
}

//
// handle_data
//
int Tena_Publisher_Service::
handle_data (const DAC::Data_Packet & packet)
{
  OASIS::Software_Probe_Header probe;
  int retval =
    probe.recall (packet.probe_data (),
                  packet.probe_data_length (),
                  packet.byte_order ());

  if (0 != retval)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to recall probe data\n")),
                       -1);

  // Try and locate the correct bridge for the data type.
  Software_Probe_Bridge * bridge = 0;
  const ACE_Utils::UUID & uuid = probe.uuid_;

  if (0 != this->loaded_bridges_.find (*uuid.to_string (), bridge))
    ACE_ERROR_RETURN ((LM_WARNING,
                       ACE_TEXT ("%T (%t) - %M - cannot handle data; ")
                       ACE_TEXT ("unknown probe type [uuid=%s]\n"),
                       uuid.to_string ()->c_str ()),
                       -1);

  // Publish the data.
  return 0 != bridge ? bridge->publish (packet) : -1;
}

//
// handle_registration
//
int Tena_Publisher_Service::
handle_registration (const DAC::Registration_Packet & packet)
{
  try
  {
    // We are going to iterate through each software probe instance
    // and (1) load its software probe bridge, and (2) create a
    // corresponding servant for the software probe instance.
    DAC::Software_Probe_Instances::const_iterator
      iter = packet.probes_.begin (), iter_end = packet.probes_.end ();

    for (; iter != iter_end; ++ iter)
    {
      Software_Probe_Bridge * bridge = 0;

      if (-1 != this->load_bridge (*iter->int_id_, bridge))
        bridge->create_servant (ACE_Utils::UUID (packet.einode_.c_str ()), *iter);
      else
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("%T (%t) - %M - failed to load software probe ")
                    ACE_TEXT ("bridge for %s\n"),
                    iter->ext_id_.c_str ()));
    }

    return 0;
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to load software probe; %s\n"),
                ex.what ()));
  }

  return -1;
}

//
// handle_unregister_einode
//
int Tena_Publisher_Service::
handle_unregister_einode (const DAC::Unregistration_Packet & packet)
{
  try
  {
    // Iterate through the software probe instances and
    // (1) find the appropriate bridge for the probe type,
    // and (2) tell the bridge to destory the servant whose
    // name is provided from the packet.
    DAC::Unregister_Software_Probe_Instances::const_iterator
      iter = packet.probes_.begin (), iter_end = packet.probes_.end ();

    for (; iter != iter_end; ++ iter)
    {
      Software_Probe_Bridge * bridge = 0;
      if (0 != this->loaded_bridges_.find (iter->first, bridge))
        continue;

      bridge->destroy_servant (iter->second);
    }

    return 0;
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to unregister probe: %s\n"),
                ex.what ()));
  }

  return -1;
}

//
// cleanup
//
void Tena_Publisher_Service::cleanup (void)
{
  this->bridge_factories_.unbind_all ();
  this->loaded_bridges_.unbind_all ();

  if (this->session_.isValid ())
    this->session_.reset ();

  if (this->runtime_.isValid ())
    this->runtime_.reset ();
}

//
// load_bridge_manager
//
int Tena_Publisher_Service::load_bridge_manager (const ACE_CString & file)
{
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - loading bridge manager from %s\n"),
              file.c_str ()));

  ACE_DLL module;

  if (0 != module.open (file.c_str (), ACE_DEFAULT_SHLIB_MODE, 0))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to load module %s\n"),
                       file.c_str ()),
                       -1);

  // Extract the entry point from the module.
  void * symbol = module.symbol (OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_FUNC_STR);

  if (symbol == 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - %s is not a bridge module; ")
                       ACE_TEXT ("failed to locate entry point '%s'\n"),
                       file.c_str (),
                       OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_FUNC_STR),
                       -1);

  // Convert to function pointer that returns to correct type.
  typedef ::OASIS::Software_Probe_Bridge_Manager * (* FACTORYMETHOD) (void);
  FACTORYMETHOD funcptr = (FACTORYMETHOD) symbol;
  Software_Probe_Bridge_Manager * bridge = funcptr ();

  // Extend the OM factories the tena publisher can handle
  bridge->register_factories (this->bridge_factories_);
  bridge->release ();

  return 0;
}

//
// load_bridge
//
int Tena_Publisher_Service::
load_bridge (const OASIS::Software_Probe_Metadata & metadata,
             Software_Probe_Bridge * & bridge_out)
{
  // We don't need to load a software probe bridge more than
  // once. So, let's perform this check first.
  if (0 == this->loaded_bridges_.find (*metadata.uuid_.to_string (), bridge_out))
    return 1;

  // Locate the factory method for the software probe.
  ::OASIS::TENA_Bridge::BRIDGE_FACTORY_METHOD factory_method = 0;
  if (0 != this->bridge_factories_.find (metadata.type_info_, factory_method))
    ACE_ERROR_RETURN ((LM_WARNING,
                       ACE_TEXT ("%T (%t) - %M - cannot load TENA probe bridge; ")
                       ACE_TEXT ("unknown probe type [type=%s]\n"),
                       metadata.type_info_.c_str ()),
                       -1);

  // Create the software probe bridge, then configure it.
  Software_Probe_Bridge * bridge = (*factory_method) ();

  if (0 == bridge)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to create TENA ")
                       ACE_TEXT ("probe bridge\n")),
                       -1);

  bridge->configure (*this->session_, this->bridge_initial_values_);

  // Store the software probe bridge for later use.
  this->loaded_bridges_.bind (*metadata.uuid_.to_string (), bridge);
  bridge_out = bridge;

  return 0;
}


}
