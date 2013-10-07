// $Id: Execution_Context.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "Execution_Context.h"

#if !defined (__OASIS_INLINE__)
#include "Execution_Context.inl"
#endif

#include "Command_Channel.h"
#include "Data_Channel.h"
#include "Data_Handler.h"
#include "Data_Packet.h"
#include "Metametrics_Table.h"
#include "Registration_Packet.h"
#include "Unregistration_Packet.h"

#include "oasis/probes/Software_Probe.h"

#include "ace/Service_Config.h"
#include "ace/Dynamic_Service.h"
#include "ace/ARGV.h"

#include "boost/bind.hpp"
#include "boost/proto/traits.hpp"

#include <sstream>

namespace OASIS
{
namespace DAC
{

//
// load_DAC_service
//
template <typename T, typename MANAGER>
int load_DAC_service (MANAGER & mgr, const char * directive)
{
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - processing directive [%s]\n"),
              directive));

  // Extract the name of the service from the directive. It will be
  // the second word in the directive.
  std::istringstream istr (directive);
  std::string type, name;
  istr >> type >> name;

  if (0 != ACE_Service_Config::current ()->process_directive (directive))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to process ")
                       ACE_TEXT ("directive [%s]\n"),
                       directive),
                       -1);

  // Locate the recently loaded service.
  T * service =
    ACE_Dynamic_Service <T>::
    instance (ACE_Service_Config::current (), name.c_str ());

  // Store the service in the manager.
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - caching %s service\n"),
              name.c_str ()));

  mgr.bind (name.c_str (), service);

  return 0;
}

template <typename T, typename MANAGER>
int load_DAC_data_handler (MANAGER & mgr,
                           const DAC_Service_Configuration::Directive & dir)
{
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - loading data handler '%s' from %s\n"),
              dir.name_.c_str (),
              dir.module_.c_str ()));

  ACE_DLL module;

  if (0 != module.open (dir.module_.c_str (), ACE_DEFAULT_SHLIB_MODE, 0))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to load module %s\n"),
                       dir.module_.c_str ()),
                      -1);

  // Extract the entry point from the module.
  void * symbol = module.symbol (dir.symbol_.c_str ());

  if (symbol == 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - %s is not a bridge module; ")
                       ACE_TEXT ("failed to locate entry point '%s'\n"),
                       dir.module_.c_str (),
                       dir.symbol_.c_str ()),
                      -1);

  // Convert to function pointer that returns to correct type.
  typedef ::OASIS::DAC::Data_Handler * (* FACTORYMETHOD) (void);
  FACTORYMETHOD funcptr = (FACTORYMETHOD) symbol;

  OASIS::DAC::Data_Handler * handler = funcptr ();

  if (0 == handler)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("failed to create %s data handler\n"),
                       dir.name_.c_str ()),
                      -1);

  ACE_ARGV_T <char> args (dir.params_.c_str ());

  if (0 != handler->init (args.argc (), args.argv ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to initialize %s ")
                       ACE_TEXT ("data handler\n"),
                       dir.name_.c_str ()),
                      -1);

  mgr.bind (dir.name_.c_str (), handler);

  return 0;
}

//
// ~Execution_Context
//
Execution_Context::~Execution_Context (void)
{
  if (this->database_->is_connected ())
    this->database_->disconnect ();
}


//
// load_data_handler
//
int Execution_Context::
load_data_handler (const DAC_Service_Configuration::Directive & directive)
{
  return load_DAC_data_handler <Data_Handler> (this->handlers_, directive);
}

//
// load_data_channel
//
int Execution_Context::load_data_channel (const char * directive)
{
  return load_DAC_service <Data_Channel> (this->channels_, directive);
}

//
// activate
//
int Execution_Context::activate (void)
{
  // Notify all the handlers to enter the deactivate state. This
  // will allow them to perform any shutdown operations.
  std::for_each (this->handlers_.begin (),
                 this->handlers_.end (),
                 boost::bind (&Data_Handler::handle_activate,
                              boost::bind (&Data_Handler_Manager::ENTRY::int_id_, _1)));

  std::for_each (this->channels_.begin (),
                 this->channels_.end (),
                 boost::bind (&Data_Channel::handle_activate,
                              boost::bind (&Data_Channel_Manager::ENTRY::int_id_, _1)));

  return 0;
}

//
// deactivate
//
int Execution_Context::deactivate (void)
{
  // Notify all the handlers to enter the deactivate state. This
  // will allow them to perform any shutdown operations.
  std::for_each (this->handlers_.begin (),
                 this->handlers_.end (),
                 boost::bind (&Data_Handler::handle_deactivate,
                              boost::bind (&Data_Handler_Manager::ENTRY::int_id_, _1)));

  std::for_each (this->channels_.begin (),
                 this->channels_.end (),
                 boost::bind (&Data_Channel::handle_deactivate,
                              boost::bind (&Data_Channel_Manager::ENTRY::int_id_, _1)));

  return 0;
}

//
// handle_registration
//
int Execution_Context::
handle_registration (const Registration_Packet & packet)
{
  // Insert the EINode into the database
  this->database_.insert_einode (packet.einode_, packet.name_);

  if (0 != packet.probes_.current_size ())
  {
    // Insert the software probe metadata into the
    // database. This will ensure that all information needed by
    // any handler will already be in the database.
    ACE_ERROR ((LM_INFO,
                ACE_TEXT ("%T (%t) - %M - storing metadata for %d probe(s)\n"),
                packet.probes_.current_size ()));

    std::for_each (packet.probes_.begin (),
                   packet.probes_.end (),
                   boost::bind (&Database::insert_metadata,
                                boost::ref (this->database_),
                                boost::bind (&Software_Probe_Metadata_ptr::operator*,
                                  boost::bind (&Software_Probe_Instance::int_id_, _1))));

    std::for_each (packet.probes_.begin (),
                   packet.probes_.end (),
                   boost::bind (&Database::register_schema,
                                boost::ref (this->database_),
                                boost::bind (&Software_Probe_Metadata_ptr::operator*,
                                  boost::bind (&Software_Probe_Instance::int_id_, _1))));

    std::for_each (packet.probes_.begin (),
                   packet.probes_.end (),
                   boost::bind (&Database::insert_instance,
                                boost::ref (this->database_),
                                boost::bind (&Software_Probe_Instance::ext_id_, _1),
                                boost::bind (&Software_Probe_Metadata_ptr::operator*,
                                  boost::bind (&Software_Probe_Instance::int_id_, _1)),
                                packet.einode_));
  }

  // Store the command channel for this EI node. This will allow
  // use to send commands to the EI node at a later time.
  int retval =
    this->cmd_channels_.bind (ACE_CString (packet.name_.c_str ()),
                              packet.command_channel_);

  if (0 != retval)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to store command channel\n")));


  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - notifying handlers of new ")
              ACE_TEXT ("registration\n")));

  std::for_each (this->handlers_.begin (),
                 this->handlers_.end (),
                 boost::bind (&Data_Handler::handle_registration,
                              boost::bind (&Data_Handler_Manager::ENTRY::int_id_, _1),
                              boost::ref (packet)));

  return 0;
}

//
// handle_data
//
int Execution_Context::handle_data (const Data_Packet & packet)
{
  std::for_each (this->handlers_.begin (),
                 this->handlers_.end (),
                 boost::bind (&Data_Handler::handle_data,
                              boost::bind (&Data_Handler_Manager::ENTRY::int_id_, _1),
                              boost::ref (packet)));

  return 0;
}

//
// handle_command
//
int Execution_Context::
handle_command (const ACE_CString & einode, const ACE_CString & command)
{
  Command_Channel * cmd_channel = 0;
  if (0 != this->cmd_channels_.find (einode, cmd_channel))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to locate einode %s\n"),
                       einode.c_str ()),
                       -1);

  if (0 == cmd_channel)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - einode %s has invalid ")
                       ACE_TEXT ("command channel\n"),
                       einode.c_str ()),
                       -1);

  return cmd_channel->handle_command (command);
}

int Execution_Context::
handle_unregister_einode (const ACE_Utils::UUID & uuid)
{
  // Build the unregistration packet
  Unregistration_Packet packet;
  packet.uuid_ = uuid;
  this->database_.einode_name (uuid, packet.name_);

  if( 0 != this->database_.einode_probes (uuid, packet.probes_))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to identify ")
                       ACE_TEXT ("einode probes for Unregistration_Packet\n")),
                       -1);

  // Notify the handlers
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - notifying handlers of unregistration\n ")));

  std::for_each (this->handlers_.begin (),
                 this->handlers_.end (),
                 boost::bind (&Data_Handler::handle_unregister_einode,
                              boost::bind (&Data_Handler_Manager::ENTRY::int_id_, _1),
                              boost::ref (packet)));

  // Remove the command channel
  Command_Channel * cmd_channel = 0;
  this->cmd_channels_.unbind (packet.name_, cmd_channel);

  if (0 != cmd_channel)
    cmd_channel->destroy ();

  return 0;
}

}
}
