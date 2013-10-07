// $Id: Smoke_Test_App.cpp 2207 2012-06-08 20:02:32Z dfeiock $

#include "Smoke_Test_App.h"
#include "oasis/TestExecutionManager/TestExecutionManagerC.h"

#include "ace/OS_NS_unistd.h"
#include "ace/Get_Opt.h"

//
// Smoke_Test_App
//
Smoke_Test_App::Smoke_Test_App (void)
{

}

//
// ~Smoke_Test_App
//
Smoke_Test_App::~Smoke_Test_App (void)
{

}

//
// run_main
//
int Smoke_Test_App::run_main (int argc, char * argv [])
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
    CORBA::Object_var obj = this->orb_->resolve_initial_references ("TEM");
    if (CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve TEM\n")),
                         -1);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - extracting TestExecutionManager object\n")));

    // Narrow the object to a TestExecutionManager
    OASIS::TestExecutionManager_var test_mgr =
      OASIS::TestExecutionManager::_narrow (obj.in ());

    if (CORBA::is_nil (test_mgr.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve TestExecutionManager\n")),
                         -1);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - requesting list of DACs\n")));

    // Get the list of DACs. For the smoke test, there should only
    // be one DAC listed and its name should be SmokeTest.
    OASIS::DataAcquisitionControllerSeq_var the_DACs = test_mgr->get_DACs ();

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - DAC list is %d\n"),
                the_DACs->length ()));

    if (this->expected_value_ != the_DACs->length ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - DAC list length should be %u\n"),
                         this->expected_value_),
                         -1);

    if (this->expected_value_ != 0)
    {
      OASIS::DataAcquisitionController_ptr the_DAC =
        the_DACs[static_cast <CORBA::ULong> (0)];

      if (::CORBA::is_nil (the_DAC))
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%T (%t) - %M - DAC reference is NIL!!\n")),
                           -1);

      ::CORBA::String_var dac_name = the_DAC->name ();
      if (0 != ACE_OS::strcmp (dac_name.in (), "SmokeTest"))
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%T (%t) - %M - DAC name should be SmokeTest\n")),
                           -1);

      OASIS::ProbeInstanceList_var the_probes = the_DAC->get_probe_instances ();
      if (::CORBA::is_nil (the_probes))
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%T (%t) - %M - the probes reference is NIL!!\n")),
                           -1);

      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - probes list is %d\n"),
                  the_probes->length ()));

      ::CORBA::String_var probe_schema = the_DAC->get_schema ("ProcessorProbe_SmokeTest", "SmokeTest");
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - probe schema is %s\n"),
                  probe_schema.in ()));

    }

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - test completed successfully\n")));

    // Make sure we destroy our ORB.
    this->orb_->destroy ();

    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M [%N:%l] - %s\n"),
                ex._info ().c_str ()));
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }

  if (!::CORBA::is_nil (this->orb_.in ()))
    this->orb_->destroy ();

  return -1;
}

//
// parse_args
//
int Smoke_Test_App::parse_args (int argc, char * argv [])
{
  this->orb_ = CORBA::ORB_init (argc, argv);

  const char * optstr = "v:";

  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("value", 'v', ACE_Get_Opt::ARG_REQUIRED);

  // Parse the remaining command-line arguments
  int opt = 0;

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("value", get_opt.long_option ()))
        this->expected_value_ = ACE_OS::atoi (get_opt.opt_arg ());
      break;

    case 'v':
      this->expected_value_ = ACE_OS::atoi (get_opt.opt_arg ());
      break;
    }
  }
  return 0;
}
