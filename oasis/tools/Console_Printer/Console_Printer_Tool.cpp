// $Id: Console_Printer_Tool.cpp 2095 2012-01-05 15:51:11Z dfeiock $

#include "Console_Printer_Tool.h"

#include "oasis/TestExecutionManager/TestExecutionManagerC.h"
#include "oasis/middleware/tao/ORB_Server_Task.h"
#include "oasis/middleware/tao/UUID.h"

#include "ace/Get_Opt.h"

namespace OASIS
{

//
// Console_Printer_Tool
//
Console_Printer_Tool::Console_Printer_Tool (void)
: servant_ (&subscriber_impl_, false)
{

}

//
// ~Console_Printer_Tool
//
Console_Printer_Tool::~Console_Printer_Tool (void)
{

}

//
// run_main
//
int Console_Printer_Tool::run_main (int argc, char * argv [])
{
  try
  {
    if (0 != this->parse_args (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to parse ")
                         ACE_TEXT ("command-line arguments\n")),
                         -1);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - resolving TestExecutionManager\n")));

    // Resolve the TestExecutionManager object.
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("TestExecutionManager");
    if (CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve TestExecutionManager\n")),
                         -1);

    TestExecutionManager_var test_mgr = TestExecutionManager::_narrow (obj.in ());
    if (CORBA::is_nil (test_mgr.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - object is not a OASIS::TestExecutionManager\n")),
                         -1);

    // Get the current list of DACs.
    DataAcquisitionControllerSeq_var the_DACs = test_mgr->get_DACs ();
    CORBA::ULong length = the_DACs->length ();

    for (CORBA::ULong i = 0; i < length; ++ i)
    {
      // Get the DAC's name.
      CORBA::String_var name = the_DACs[i]->name ();

      if (0 == ACE_OS::strcmp (name.in (), this->dac_name_.c_str ()))
      {
        // Register the subscriber with the DAC.
        this->register_subscriber (the_DACs[i].in ());

        if (0 != this->run_server ())
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to run server\n")),
                             -1);

        break;
      }
    }

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
// register_subscriber
//
int Console_Printer_Tool::
register_subscriber (DataAcquisitionController_ptr the_DAC)
{
  // Get the TaoPublisherService from this DAC.
  RemoteService_var remote_service = the_DAC->get_service ("TaoPublisherService");

  if (CORBA::is_nil (remote_service.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - %s does not have a %s"),
                       this->dac_name_.c_str (),
                       ACE_TEXT ("TaoPublisherService")),
                       -1);

  this->pulisher_service_ = PublisherService::_narrow (remote_service.in ());

  if (CORBA::is_nil (this->pulisher_service_.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - object is not a PublisherService\n")),
                       -1);

  CORBA::Object_var obj = this->servant_.get_reference ();
  DataSubscriber_var subscriber = DataSubscriber::_narrow (obj.in ());

  // Subscribe to the probe's updates.
  OASIS::UUID probe_uuid;
  probe_uuid <<= this->probe_;
  this->pulisher_service_->register_subscriber (probe_uuid, subscriber.in ());

  return 0;
}

//
// run_server
//
int Console_Printer_Tool::run_server (void)
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

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - requesting the publisher\n")));

  // Activate the servant.
  this->servant_.activate (root_poa.in ());

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
void Console_Printer_Tool::shutdown (void)
{
  try
  {

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
int Console_Printer_Tool::parse_args (int argc, char * argv [])
{
  // Initialize the CORBA orb.
  this->orb_ = CORBA::ORB_init (argc, argv);

  // Parse the remaining command-line arguments.
  const char * optargs = "p:d:";
  ACE_Get_Opt get_opt (argc, argv, optargs);

  get_opt.long_option ("probe", 'p', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("dac", 'd', ACE_Get_Opt::ARG_REQUIRED);

  int opt = 0;

  while (EOF != (opt = get_opt ()))
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("probe", get_opt.long_option ()))
        this->probe_.from_string (get_opt.opt_arg ());
      else if (0 == ACE_OS::strcmp ("dac", get_opt.long_option ()))
        this->dac_name_ = get_opt.opt_arg ();

      break;

    case 'p':
      this->probe_.from_string (get_opt.opt_arg ());
      break;

    case 'd':
      this->dac_name_ = get_opt.opt_arg ();
      break;
    }
  }

  return 0;
}

}
