// $ID$
#include "TAO_Archive_Service.h"
#include "Query_i.h"
#include "Archive_Service.h"


namespace OASIS
{

TAO_Archive_Service::TAO_Archive_Service (void)
{

}

TAO_Archive_Service::~TAO_Archive_Service (void)
{

}

//
// init
//
int TAO_Archive_Service::
init (int argc, char *argv [],
      DAC_Archive_Service * archive_service)
{
  try
  {
    // Initialize the ORB. We are going to use the DAC's ORB.
    this->orb_ = ::CORBA::ORB_init (argc, argv);

    // Resolve the RootPOA.
    ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve ")
                         ACE_TEXT ("the RootPOA")),
                         -1);

    ::PortableServer::POA_var root_poa = ::PortableServer::POA::_narrow (obj.in ());
    if (::CORBA::is_nil (root_poa.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - object is not a POA")),
                         -1);

    this->register_query_factories ();

    // Activate the RootPOA's manager.
    ::PortableServer::POAManager_var mgr = root_poa->the_POAManager ();
    mgr->activate ();

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - Activating the Archive servant\n")));

    DAC_Archive_Service_i * archiver = 0;

    ACE_NEW_THROW_EX (archiver,
                      DAC_Archive_Service_i (root_poa.in (), archive_service),
                      ::CORBA::NO_MEMORY ());

    this->servant_.reset (archiver);

    this->servant_.activate (root_poa.in ());

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - initializing active objects\n")));

    return 0;
  }

  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }

  return -1;
}

//
// fini
//
int TAO_Archive_Service::fini (void)
{
  try
  {
    // Deactive the publisher and destroy the POA.
    this->servant_.deactivate ();
    this->the_POA_->destroy (0, 0);

    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }

  return -1;
}

//
// get_remote_service
//
RemoteService_ptr TAO_Archive_Service::get_remote_service (void)
{
  CORBA::Object_var obj = this->servant_.get_reference ();
  RemoteService_var remote_service = RemoteService::_narrow (obj.in ());
  return remote_service._retn ();
}

//
// register_query_factories
//
void TAO_Archive_Service::register_query_factories (void)
{
  OASIS_OBV_REGISTER_FACTORY (::OASIS::QueryFactory, Query_i);
  OASIS_OBV_REGISTER_FACTORY (::OASIS::EINodeQueryFactory, EINodeQuery_i);
  OASIS_OBV_REGISTER_FACTORY (::OASIS::ProbeQueryFactory, ProbeQuery_i);
  OASIS_OBV_REGISTER_FACTORY (::OASIS::TimeQueryFactory, TimeQuery_i);
  OASIS_OBV_REGISTER_FACTORY (::OASIS::TimeAfterQueryFactory, TimeAfterQuery_i);
  OASIS_OBV_REGISTER_FACTORY (::OASIS::TimeBeforeQueryFactory, TimeBeforeQuery_i);
}

}