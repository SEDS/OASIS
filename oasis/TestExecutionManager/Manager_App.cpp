// $Id: Manager_App.cpp 2187 2012-05-30 17:28:06Z dfeiock $

#include "Manager_App.h"

#include "oasis/middleware/tao/ORB_Server_Task.h"

#include "ace/Get_Opt.h"
#include "ace/streams.h"

namespace OASIS
{

//
// TestExecutionManager_App
//
TestExecutionManager_App::TestExecutionManager_App (void)
: name_ ("OASIS")
{

}

//
// ~TestExecutionManager_App
//
TestExecutionManager_App::~TestExecutionManager_App (void)
{

}

//
// run_main
//
int TestExecutionManager_App::run_main (int argc, char * argv [])
{
  try
  {
    // Parse the command-line arguments.
    if (0 != this->parse_args (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to parse ")
                         ACE_TEXT ("command-line arguments\n")),
                         -1);

    // Get the root POA for this ORB.
    ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");

    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve RootPOA")),
                         -1);

    this->root_poa_ = ::PortableServer::POA::_narrow (obj.in ());

    if (::CORBA::is_nil (this->root_poa_.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - object is not a POA")),
                         -1);

    // Activate the POA manager.
    ::PortableServer::POAManager_var poa_mgr = this->root_poa_->the_POAManager ();
    poa_mgr->activate ();

    // Finish initializing the servant, then activate it.
    const ACE_CString iortbl_name = "OASIS/TEM";
    this->servant_.set_trait_value (IOR_Table_Trait (), iortbl_name);
    TestExecutionManager_i * test_mgr = 0;

    ACE_NEW_THROW_EX (test_mgr,
                      TestExecutionManager_i (*this),
                      CORBA::NO_MEMORY ());

    this->servant_.reset (test_mgr);
    this->servant_.activate (this->root_poa_.in ());

    // Update the ORB task.
    ORB_Server_Task orb_task (this->orb_.in ());

    // Run the ORB's event loop, and wait for it to exit.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - running ORB's event loop\n")));

    orb_task.activate ();
    orb_task.wait ();

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
// parse_args
//
int TestExecutionManager_App::parse_args (int argc, char * argv [])
{
  // Initialize the CORBA ORB, then parse the remaining arguments.
  this->orb_ = CORBA::ORB_init (argc, argv);

  const char * optargs = "n:";
  ACE_Get_Opt get_opt (argc, argv, optargs);

  get_opt.long_option ("name", 'n', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("ior-file", ACE_Get_Opt::ARG_REQUIRED);

  int opt = 0;

  while (EOF != (opt = get_opt ()))
  {
    switch (opt)
    {
    case 0:
      if (0 != ACE_OS::strcmp ("name", get_opt.long_option ()))
      {
        this->name_ = get_opt.opt_arg ();
      }
      else if (0 != ACE_OS::strcmp ("ior-file", get_opt.long_option ()))
      {
        this->servant_.set_trait_value (IOR_File_Trait (), get_opt.opt_arg ());
      }
      break;

    case 'n':
      this->name_ = get_opt.opt_arg ();
      break;
    }
  }

  return 0;
}

//
// shutdown
//
void TestExecutionManager_App::shutdown (void)
{
  try
  {
    // Deactivate the servants.
    this->servant_.deactivate ();

    // Shutdown the ORB.
    if (!::CORBA::is_nil (this->orb_.in ()))
      this->orb_->shutdown ();
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception ")
                ACE_TEXT ("at shutdown\n")));
  }
}

//
// destroy
//
void TestExecutionManager_App::destroy (void)
{
  try
  {
    if (!::CORBA::is_nil (this->root_poa_.in ()))
    {
      // Destroy the RootPOA.
      this->root_poa_->destroy (0, 0);
      this->root_poa_ = PortableServer::POA::_nil ();
    }

    if (!::CORBA::is_nil (this->orb_.in ()))
    {
      // Destroy the ORB and reset its resources.
      this->orb_->destroy ();
      this->orb_ = CORBA::ORB::_nil ();
    }
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception ")
                ACE_TEXT ("during destroy\n")));
  }
}

//
// name
//
const ACE_CString & TestExecutionManager_App::name (void) const
{
  return this->name_;
}

}
