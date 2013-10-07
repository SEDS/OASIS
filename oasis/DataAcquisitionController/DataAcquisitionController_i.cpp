// $Id: DataAcquisitionController_i.cpp 2207 2012-06-08 20:02:32Z dfeiock $

#include "DataAcquisitionController_i.h"

#if !defined (__OASIS_INLINE__)
#include "DataAcquisitionController_i.inl"
#endif

#include "Execution_Context.h"
#include "Data_Handler.h"
#include "Database.h"
#include "oasis/probes/Software_Probe_Instance.h"

//
// <<=
//
void operator <<= (OASIS::ProbeInstance & dst, const OASIS::Software_Probe_Instance & src)
{
  dst.inst_name = src.inst_name_.c_str ();
  dst.inst_uuid = src.inst_uuid_.to_string ()->c_str ();
  dst.inst_type_name = src.inst_type_name_.c_str ();
  dst.einode_name = src.einode_name_.c_str ();
}

namespace OASIS
{

//
// name
//
char * DataAcquisitionController_i::name (void)
{
  CORBA::String_var str =
    CORBA::string_dup (DAC::EXECUTION_CONTEXT::instance ()->name ().c_str ());

  return str._retn ();
}

//
// send_command
//
void DataAcquisitionController_i::
send_command (const char * einode, const char * command)
{
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - %s: sending %s command '%s'\n"),
              DAC::EXECUTION_CONTEXT::instance ()->name ().c_str (),
              einode,
              command));

  DAC::EXECUTION_CONTEXT::instance ()->handle_command (einode, command);
}

//
// get_service
//
RemoteService_ptr
DataAcquisitionController_i::get_service (const char * name)
{
  using DAC::EXECUTION_CONTEXT;

  // Locate the service.
  DAC::Data_Handler * handler = 0;
  int retval = EXECUTION_CONTEXT::instance ()->get_data_handlers ().find (name, handler);

  if (retval == -1)
    throw ServiceNotFound (name);

  // Before continuing, make sure the handler supports a remote
  // service. Otherwise, we need to raise an exception.
  RemoteService_var remote_service = handler->get_remote_service ();

  if (::CORBA::is_nil (remote_service.in ()))
    throw NoRemoteService (name);

  return remote_service._retn ();
}

//
// get_services
//
RemoteServiceList * DataAcquisitionController_i::get_services (void)
{
  using DAC::EXECUTION_CONTEXT;
  using DAC::Execution_Context;

  // Get the data handlers and allocate a list that can hold all
  // the data handlers. This does not mean that we will fill this
  // list completely since some services may not supporting remoting
  // capabilities.
  const Execution_Context::Data_Handler_Manager & handlers =
    EXECUTION_CONTEXT::instance ()->get_data_handlers ();

  RemoteServiceList_var list;
  ACE_NEW_THROW_EX (list,
                    RemoteServiceList (handlers.current_size ()),
                    CORBA::NO_MEMORY ());

  list->length (handlers.current_size ());

  // Iterate over all the handlers and insert only those that
  // support a remoting service into the list.
  Execution_Context::Data_Handler_Manager::CONST_ITERATOR iter (handlers);
  CORBA::ULong i = 0;

  for (; !iter.done (); ++ iter)
  {
    // Get this handler's remote service.
    RemoteService_var remote_service = iter->item ()->get_remote_service ();

    if (!CORBA::is_nil (remote_service.in ()))
      (*list)[i ++] = remote_service;
  }

  // Finally, make sure we size the list correctly. The current value
  // of 'i' is the number of remote services stored in the list.
  if (i < list->length ())
    list->length (i);

  return list._retn ();
}

//
// get_probe_instances
//
ProbeInstanceList * DataAcquisitionController_i::get_probe_instances (void)
{
  using DAC::EXECUTION_CONTEXT;
  DAC::Database & db = EXECUTION_CONTEXT::instance ()->get_database ();

  // Init and query probe instances
  std::vector < Software_Probe_Instance > instances;
  db.probe_instances (instances);

  // Init CORBA datatype
  ProbeInstanceList_var list;
  ACE_NEW_THROW_EX (list,
                    ProbeInstanceList (instances.size ()),
                    ::CORBA::NO_MEMORY ());

  list->length (instances.size ());

  // Iterate over oasis structure and copy to CORBA structure
  CORBA::ULong i = 0;

  for (std::vector < Software_Probe_Instance >::iterator iter = instances.begin ();
       iter != instances.end ();
       ++iter, ++i)
  {
    list[i] <<= *iter;
  }

  return list._retn ();
}

//
// get_schema
//
char * DataAcquisitionController_i::get_schema (const char * name, const char * einode)
{
  using DAC::EXECUTION_CONTEXT;
  DAC::Database & db = EXECUTION_CONTEXT::instance ()->get_database ();

  // Init and query probe instances
  ACE_CString schema;
  db.schema (name, einode, schema);

  // Init CORBA datatype
  CORBA::String_var str =
    CORBA::string_dup (schema.c_str ());

  return str._retn ();
}
}
