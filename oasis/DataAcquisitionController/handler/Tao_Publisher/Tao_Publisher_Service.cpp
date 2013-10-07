// $Id: Tao_Publisher_Service.cpp 2071 2011-12-01 15:48:16Z hillj $

#include "Tao_Publisher_Service.h"
#include "ace/Service_Config.h"

namespace OASIS
{

//
// Archive_Data_Handler
//
Tao_Publisher_Service::Tao_Publisher_Service (void)
: servant_ (&publisher_, false)
{

}

//
// ~Archive_Data_Handler
//
Tao_Publisher_Service::~Tao_Publisher_Service (void)
{

}

//
// init
//
int Tao_Publisher_Service::init (int argc, ACE_TCHAR *argv [])
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

    // Initialize the POA for this service, then activate the servant.
    this->initialize_POA (root_poa.in ());
    this->servant_.activate (this->the_POA_.in ());

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
int Tao_Publisher_Service::fini (void)
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
// handle_data
//
int Tao_Publisher_Service::handle_data (const DAC::Data_Packet & packet)
{
  return this->publisher_.handle_data (packet);
}

//
// get_remote_service
//
RemoteService_ptr Tao_Publisher_Service::get_remote_service (void)
{
  CORBA::Object_var obj = this->servant_.get_reference ();
  RemoteService_var remote_service = RemoteService::_narrow (obj.in ());
  return remote_service._retn ();
}

//
// initialize_POA
//
void Tao_Publisher_Service::initialize_POA (PortableServer::POA_ptr poa)
{
  // Construct the policy list for the LoggingServerPOA.
  ::CORBA::PolicyList policies (6);
  policies.length (6);

  policies[0] = poa->create_thread_policy (PortableServer::SINGLE_THREAD_MODEL);
  policies[1] = poa->create_servant_retention_policy (PortableServer::RETAIN);
  policies[2] = poa->create_id_assignment_policy (PortableServer::SYSTEM_ID);
  policies[3] = poa->create_id_uniqueness_policy (PortableServer::UNIQUE_ID);
  policies[4] = poa->create_lifespan_policy (PortableServer::TRANSIENT);
  policies[5] = poa->create_request_processing_policy (PortableServer::USE_ACTIVE_OBJECT_MAP_ONLY);

  // Create the child POA for the test logger factory servants.
  this->the_POA_ =
    poa->create_POA ("TaoPublisherServicePOA",
                     ::PortableServer::POAManager::_nil (),
                     policies);

  for (size_t i = 0; i < 6; ++ i)
    policies[i]->destroy ();

  PortableServer::POAManager_var the_mgr = this->the_POA_->the_POAManager ();
  the_mgr->activate ();
}

}

OASIS_DAC_DATA_HANDLER_IMPL (_make_OASIS_Tao_Publisher_Service, OASIS::Tao_Publisher_Service)
