// $Id: Standard_DAC_App.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "Standard_DAC_App.h"

#if !defined (__OASIS_INLINE__)
#include "Standard_DAC_App.inl"
#endif

#include "Execution_Context.h"

#include "oasis/probes/Software_Probe.h"

#if defined (OASIS_HAS_TAO_DAC_SERVANT)
#include "oasis/TestExecutionManager/TestExecutionManagerC.h"
#endif

#include "ace/Get_Opt.h"
#include "ace/streams.h"

#include "boost/bind.hpp"

#include <algorithm>

namespace OASIS
{

//
// run_main
//
int Standard_DAC_App::run_main (int argc, char * argv [])
{
  try
  {
    // Parse the command-line options.
    if (0 != this->parse_args (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to parse command-line\n")),
                         -1);

    // Open the database and make sure it is created.
    DAC::Execution_Context * ctx = DAC::EXECUTION_CONTEXT::instance ();
    DAC::Database & db = ctx->get_database ();

    db->connect (this->connstr_);
    db.create ();

    // Initialize the services. This must be done after we have
    // open a connection to the database because some services
    // may need to use the database.
    if (0 != this->initialize_services ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to initialize services\n")),
                         -1);

#if defined (OASIS_HAS_TAO_DAC_SERVANT)
    ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");

    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve RootPOA\n")),
                         -1);

    ::PortableServer::POA_var root_poa = PortableServer::POA::_narrow (obj.in ());

    if (::CORBA::is_nil (root_poa.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - object is not a POA\n")),
                         -1);

    // Activate the POA manager.
    PortableServer::POAManager_var poa_mgr = root_poa->the_POAManager ();
    poa_mgr->activate ();

    // Set the servant's IOR table name.
    this->servant_.set_trait_value (IOR_Table_Trait (), "OASIS/DAC");

    // Activate the servant.
    ACE_ERROR ((LM_INFO,
                ACE_TEXT ("%T (%t) - %M - activating DAC servant\n")));

    this->servant_.activate (root_poa.in ());

    // Finally, activate a task to handle the CORBA calls.
    this->orb_task_.reset (this->orb_.in ());
    this->orb_task_.activate ();

    this->register_with_TEM ();
#endif

    // We can now activate the execution context.
    ctx->activate ();

    // Wait until the DAC has been killed.
    ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->lock_, -1);
    this->exit_.wait ();

#if defined (OASIS_HAS_TAO_DAC_SERVANT)
    // Unregister with the TEM
    this->unregister_with_TEM ();

    // Deactivate the servant.
    ACE_DEBUG ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - deactivating the DAC's servant\n")));
    this->servant_.deactivate ();

    // Shutdown the ORB and wait for its task to return.
    ACE_DEBUG ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - shutting down ORB task\n")));
    this->orb_->shutdown ();

    ACE_DEBUG ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - waiting for ORB task to return\n")));
    this->orb_task_.wait ();
#endif

    // Deactivate the execution context.
    ACE_DEBUG ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - deactivating the DAC's execution context\n")));
                ctx->deactivate ();

#if defined (OASIS_HAS_TAO_DAC_SERVANT)
    // Shutdown and destroy the ORB.
    ACE_DEBUG ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - destroying the DAC's ORB\n")));
                this->orb_->destroy ();
#endif

    ACE_DEBUG ((LM_ERROR,
    ACE_TEXT ("%T (%t) - %M - DAC is exiting...\n")));

    return 0;
  }
#if defined (OASIS_HAS_TAO_DAC_SERVANT)
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
#endif
  catch (const ADBC::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.message ().c_str ()));
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
// initialize_services
//
int Standard_DAC_App::initialize_services (void)
{
  if (!this->svc_config_.channels ().empty ())
    std::for_each (this->svc_config_.channels ().begin (),
                   this->svc_config_.channels ().end (),
                   boost::bind (&DAC::Execution_Context::load_data_channel,
                                DAC::EXECUTION_CONTEXT::instance (),
                                boost::bind (&std::string::c_str, _1)));

  if (!this->svc_config_.handlers ().empty ())
    std::for_each (this->svc_config_.handlers ().begin (),
                   this->svc_config_.handlers ().end (),
                   boost::bind (&DAC::Execution_Context::load_data_handler,
                                DAC::EXECUTION_CONTEXT::instance (),
                                _1));
  return 0;
}

//
// shutdown
//
void Standard_DAC_App::shutdown (void)
{
  try
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s received shutdown signal\n"),
                DAC::EXECUTION_CONTEXT::instance ()->name ().c_str ()));

    // Signal the application to exit.
    ACE_GUARD (ACE_Thread_Mutex, guard, this->lock_);
    this->exit_.signal ();
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
    ACE_TEXT ("%T (%t) - %M - caught unknown exception [%N:%l]\n")));
  }
}

//
// parse_args
//
int Standard_DAC_App::parse_args (int argc, char * argv [])
{
#if defined (OASIS_HAS_TAO_DAC_SERVANT)
  this->orb_ = CORBA::ORB_init (argc, argv);
#endif

  const char * optstr = "n:hd:c:v";

  ACE_Get_Opt get_opt (argc, argv, optstr);
  get_opt.long_option ("name", 'n', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("database", 'd', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("config", 'c', ACE_Get_Opt::ARG_REQUIRED);

  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("verbose", 'v', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("debug", ACE_Get_Opt::NO_ARG);

#if defined (OASIS_HAS_TAO_DAC_SERVANT)
  get_opt.long_option ("ior-file", ACE_Get_Opt::ARG_REQUIRED);
#endif

  ACE_CString config;

  // Parse the remaining command-line arguments.
  int opt = 0;

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("name", get_opt.long_option ()))
      {
        DAC::EXECUTION_CONTEXT::instance ()->name (get_opt.long_option ());
      }
      else if (0 != ACE_OS::strcmp ("database", get_opt.long_option ()))
      {
        this->connstr_ = get_opt.opt_arg ();
      }
      else if (0 == ACE_OS::strcmp ("config", get_opt.long_option ()))
      {
        config = get_opt.opt_arg ();
      }
      else if (0 == ACE_OS::strcmp ("help", get_opt.long_option ()))
      {
        this->print_help ();
      }
      else if (0 == ACE_OS::strcmp ("verbose", get_opt.long_option ()))
      {
        this->enable_log_level (LM_INFO);
      }
      else if (0 == ACE_OS::strcmp ("debug", get_opt.long_option ()))
      {
        this->enable_log_level (LM_DEBUG);
      }
#if defined (OASIS_HAS_TAO_DAC_SERVANT)
      else if (0 == ACE_OS::strcmp ("ior-file", get_opt.long_option ()))
      {
        this->servant_.set_trait_value (IOR_File_Trait (), get_opt.opt_arg ());
      }
#endif

      break;

    case 'n':
      DAC::EXECUTION_CONTEXT::instance ()->name (get_opt.opt_arg ());
      break;

    case 'h':
      this->print_help ();
      break;

    case 'd':
      this->connstr_ = get_opt.opt_arg ();
      break;

    case 'v':
      this->enable_log_level (LM_INFO);
      break;

    case 'c':
      config = get_opt.opt_arg ();
      break;
    }
  }

  if (!config.empty ())
  {
    // Load the specified configuration, if it exists.
    ACE_ERROR ((LM_INFO,
                ACE_TEXT ("%T (%t) - %M - loading DAC service configuration %s\n"),
                config.c_str ()));

    if (!this->svc_config_.load_file (config.c_str ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to load configuration ")
                         ACE_TEXT ("[file=%s]\n"),
                         config.c_str ()),
                         -1);
  }

  return 0;
}

//
// enable_log_level
//
void Standard_DAC_App::enable_log_level (int level)
{
  // Get the current priority levels.
  u_long prio = ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

  // Update the priority levels.
  prio |= level;
  ACE_Log_Msg::instance ()->priority_mask (prio, ACE_Log_Msg::PROCESS);
}

//
// print_help
//
void Standard_DAC_App::print_help (void)
{
  static const char * help_msg =
    "Standard implementation of an OASIS Data Acquisition Controller (DAC)\n"
    "\n"
    "USAGE: oasis_dac [OPTIONS]\n"
    "\n"
    "General options:\n"
    "  --name=NAME\t\t\tName of the DAC\n"
    "  -c, --config=FILE\t\tConfiguration file\n"
    "\n"
#if defined (OASIS_HAS_TAO_DAC_SERVANT)
    "  --ior-file=FILE\t\tOutput file for IOR\n"
    "\n"
#endif
    "Output options:\n"
    "  -v, --verbose\t\t\tVerbose output\n"
    "  --debug\t\t\tShow debugging output\n"
    "  -h, --help\t\t\tPrint this help message\n";

  // Print the help message.
  std::cerr << help_msg << std::endl;

  ACE_OS::exit (1);
}

#if defined (OASIS_HAS_TAO_DAC_SERVANT)
//
// register_with_TEM
//
void Standard_DAC_App::register_with_TEM (void)
{
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - registering %s with TEM\n"),
              DAC::EXECUTION_CONTEXT::instance ()->name ().c_str ()));

  // Find the TEM
  try
  {
    ::CORBA::Object_var tem_obj = this->orb_->resolve_initial_references ("TEM");
    if (::CORBA::is_nil (tem_obj.in ()))
      return;

    // Verify it is a TEM object
    ::OASIS::TestExecutionManager_var test_mgr = ::OASIS::TestExecutionManager::_narrow (tem_obj.in ());
    if (::CORBA::is_nil (test_mgr.in ()))
      return;

    // Get the DAC
    ::CORBA::Object_var obj = this->servant_.get_reference ();
    ::OASIS::DataAcquisitionController_var dac = ::OASIS::DataAcquisitionController::_narrow (obj.in ());

    // Register the DAC
    test_mgr->register_DAC (dac.in ());
  }
  catch (...)
  {
    return;
  }
}

//
// unregister_with_TEM
//
void Standard_DAC_App::unregister_with_TEM (void)
{
  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("%T (%t) - %M - unregistering %s from TEM\n"),
              DAC::EXECUTION_CONTEXT::instance ()->name ().c_str ()));

  try
  {
    // Find the TEM
    ::CORBA::Object_var tem_obj = this->orb_->resolve_initial_references ("TEM");
    if (::CORBA::is_nil (tem_obj.in ()))
      return;

    // Verify it is a TEM object
    ::OASIS::TestExecutionManager_var test_mgr = ::OASIS::TestExecutionManager::_narrow (tem_obj.in ());
    if (::CORBA::is_nil (test_mgr.in ()))
      return;

    // Get the DAC
    ::CORBA::Object_var obj = this->servant_.get_reference ();
    ::OASIS::DataAcquisitionController_var dac = ::OASIS::DataAcquisitionController::_narrow (obj.in ());

    // Register the DAC
    test_mgr->unregister_DAC (dac.in ());
  }
  catch (...)
  {
    return;
  }
}


#endif

}
