// $Id: Standard_DAC.cpp 1897 2011-09-07 22:11:00Z hillj $

#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"
#include "ace/Signal.h"

#include "Standard_DAC_App.h"

#define OASIS_STANDARD_DAC_APP \
  ACE_Singleton <OASIS::Standard_DAC_App, ACE_Null_Mutex>::instance ()

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  OASIS_STANDARD_DAC_APP->shutdown ();
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

  // Get the current priority levels.
  u_long prio = LM_ALERT | LM_CRITICAL | LM_EMERGENCY | LM_ERROR | LM_WARNING;
  ACE_Log_Msg::instance ()->priority_mask (prio, ACE_Log_Msg::PROCESS);

  // Register the signal handler.
  register_sighandler ();

  try
  {
    retval = OASIS_STANDARD_DAC_APP->run_main (argc, argv);
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));

    retval = 1;
  }

  return retval;
}
