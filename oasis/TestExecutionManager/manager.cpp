// $Id: manager.cpp 1793 2011-04-11 04:09:02Z hillj $

#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"
#include "ace/Signal.h"

#include "Manager_App.h"

#define OASIS_TESTEXECUTIONMANAGER_APP \
  ACE_Singleton <OASIS::TestExecutionManager_App, ACE_Null_Mutex>::instance ()

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  OASIS_TESTEXECUTIONMANAGER_APP->shutdown ();
  ACE_UNUSED_ARG (sig);
}

//
// register_sighandler
//
static void register_sighandler (void)
{
  ACE_Sig_Action sa (&server_sighandler);

  sa.register_action (SIGINT);
  sa.register_action (SIGTERM);
}

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  int retval = 0;

  // Register the signal handler.
  register_sighandler ();

  try
  {
    retval = OASIS_TESTEXECUTIONMANAGER_APP->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));

    retval = -1;
  }

  // Destroy the application.
  OASIS_TESTEXECUTIONMANAGER_APP->destroy ();

  return retval;
}
