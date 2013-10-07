// $Id: Smoke_Test_Subscriber.cpp 2095 2012-01-05 15:51:11Z dfeiock $

#include "Smoke_Test_Subscriber.h"
#include "oasis/middleware/tao/ORB_Server_Task.h"
#include "oasis/middleware/tao/UUID.h"

//
// Smoke_Test_Subscriber
//
Smoke_Test_Subscriber::Smoke_Test_Subscriber (void)
: servant_ (&subscriber_impl_, false)
{

}

//
// ~Smoke_Test_Subscriber
//
Smoke_Test_Subscriber::~Smoke_Test_Subscriber (void)
{

}

//
// run_main
//
int Smoke_Test_Subscriber::run_main (int argc, char * argv [])
{
  try
  {
    if (0 != this->parse_args (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to parse ")
                         ACE_TEXT ("command-line arguments\n")),
                         -1);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - resolving DataAcquisitionController\n")));

    // Resolve the TestExecutionManager object.
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("DAC");
    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve DAC\n")),
                         -1);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - extracting DataAcquisitionController object\n")));

    // Narrow the object to a TestExecutionManager
    ::OASIS::DataAcquisitionController_var the_DAC =
      ::OASIS::DataAcquisitionController::_narrow (obj.in ());

    if (::CORBA::is_nil (the_DAC.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve DataAcquisitionController\n")),
                         -1);

    // Get the TaoPublisherService from this DAC.
    OASIS::RemoteService_var remote_service =
      the_DAC->get_service ("TaoPublisherService");

    if (CORBA::is_nil (remote_service.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to get TaoPublisherService\n")),
                         -1);

    OASIS::PublisherService_var publisher =
      OASIS::PublisherService::_narrow (remote_service.in ());

    if (CORBA::is_nil (publisher.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - object is not a TaoPublisherService\n")),
                         -1);

    if (0 != this->run_server (publisher.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to run server\n")),
                         -1);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - test completed successfully\n")));

    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
}

//
// run_server
//
int Smoke_Test_Subscriber::
run_server (OASIS::PublisherService_ptr publisher)
{
  // Resolve the RootPOA.
  CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
  if (CORBA::is_nil (obj.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to resolve RootPOA\n")),
                       -1);

  ::PortableServer::POA_var root_poa = ::PortableServer::POA::_narrow (obj.in ());
  if (::CORBA::is_nil (root_poa.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - object is not a POA")),
                       -1);

  // Activate the POA's manager.
  ::PortableServer::POAManager_var the_mgr = root_poa->the_POAManager ();
  the_mgr->activate ();

  using namespace OASIS;

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - requesting the publisher\n")));

  // Register the subscriber for the software probe.
  this->servant_.activate (root_poa.in ());

  ACE_Utils::UUID uuid ("2634666C-EB69-4A49-B9A6-C1F35CF86BE6");
  OASIS::UUID probe_uuid;
  probe_uuid <<= uuid;

  obj = this->servant_.get_reference ();
  DataSubscriber_var subscriber = DataSubscriber::_narrow (obj.in ());

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - subscribing to %s\n"),
              uuid.to_string ()->c_str ()));

  publisher->register_subscriber (probe_uuid, subscriber.in ());
  this->publisher_ = OASIS::PublisherService::_duplicate (publisher);

  // Activate the ORB task and wait for completion.
  ORB_Server_Task orb_task (this->orb_.in ());
  orb_task.activate ();

  // Wait for the task to complete.
  orb_task.wait ();
  return 0;
}

//
// shutdown
//
void Smoke_Test_Subscriber::shutdown (void)
{
  try
  {
    ACE_Utils::UUID uuid ("2634666C-EB69-4A49-B9A6-C1F35CF86BE6");
    OASIS::UUID probe_uuid;
    probe_uuid <<= uuid;

    CORBA::Object_var obj = this->servant_.get_reference ();
    OASIS::DataSubscriber_var subscriber = OASIS::DataSubscriber::_narrow (obj.in ());

    this->publisher_->unregister_subscriber (probe_uuid, subscriber.in ());
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));
  }
}

//
// parse_args
//
int Smoke_Test_Subscriber::parse_args (int argc, char * argv [])
{
  this->orb_ = CORBA::ORB_init (argc, argv);
  return 0;
}
