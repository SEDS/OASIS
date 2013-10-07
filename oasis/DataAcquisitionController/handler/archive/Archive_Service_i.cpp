// $Id: Archive_Service_i.cpp 2238 2013-03-08 20:50:44Z tmpeiris $
#include "Archive_Service_i.h"
#include "Archive_Service.h"
#include "Metrics_Table.h"
#include "Query_Visitor.h"


namespace OASIS
{

//
// DAC_Archive_Service_i
//
DAC_Archive_Service_i::
DAC_Archive_Service_i (::PortableServer::POA_ptr parent,
                       DAC_Archive_Service * archive_service)
: service_ (archive_service)
{
  // Construct the policy list for the POA.
  CORBA::PolicyList policies (6);
  policies.length (6);

  policies[0] = parent->create_thread_policy (PortableServer::ORB_CTRL_MODEL);
  policies[1] = parent->create_servant_retention_policy (PortableServer::RETAIN);
  policies[2] = parent->create_id_assignment_policy (PortableServer::SYSTEM_ID);
  policies[3] = parent->create_id_uniqueness_policy (PortableServer::UNIQUE_ID);
  policies[4] = parent->create_lifespan_policy (PortableServer::TRANSIENT);
  policies[5] = parent->create_request_processing_policy (PortableServer::USE_ACTIVE_OBJECT_MAP_ONLY);

  // Create the child POA
  this->archiver_poa_ = parent->create_POA ("DACArchiveServicePOA",
                                          ::PortableServer::POAManager::_nil (),
                                          policies);

  // Activate the POA manager.
  ::PortableServer::POAManager_var mgr = this->archiver_poa_->the_POAManager ();
  mgr->activate ();

  // Destroy the POA policies
  for (::CORBA::ULong i = 0; i < policies.length (); ++ i)
    policies[i]->destroy ();

}

//
// ~DAC_Archive_Service_i
//
DAC_Archive_Service_i::~DAC_Archive_Service_i (void)
{

}

//
// name
//
char * DAC_Archive_Service_i::name (void)
{
  CORBA::String_var service_name = CORBA::string_dup ("ArchiveService");
  return service_name._retn ();
}

//
// get_data
//
::OASIS::Cursor_ptr DAC_Archive_Service_i::
get_data (::OASIS::Query * query)
{
  Query_Visitor v;

  Query_i * q = dynamic_cast <Query_i *>(query);

  q->accept (v);

  Metric_Cursor_i * cursor =
    this->service_->get_data_cursor (v.sqlstr (), v.values ());

  //// Activate the servant. The POA now has ownership.
  ::PortableServer::ObjectId_var oid =
    this->archiver_poa_->activate_object (cursor);

  ::PortableServer::ServantBase_var servant_base (cursor);

  //// Get a reference to the servant.
  ::CORBA::Object_var obj = this->archiver_poa_->id_to_reference (oid.in ());
  ::OASIS::MetricCursor_var mcursor = ::OASIS::MetricCursor::_narrow (obj.in ());

  return mcursor._retn ();
}

}