// $Id:

#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"
#include "ace/Signal.h"

#include "System_Probe_Daemon.h"

#define OASIS_SYSTEM_PROBE_DAEMON \
  ACE_Singleton <OASIS::System::System_Probe_Daemon, ACE_Null_Mutex>::instance ()

//
// daemon_sighandler
//
static void daemon_sighandler (int sig)
{
  OASIS_SYSTEM_PROBE_DAEMON->shutdown ();
  ACE_UNUSED_ARG (sig);
}

//
// register_sighandler
//
static void register_sighandler (void)
{
  ACE_Sig_Action sa (&daemon_sighandler);

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
    retval = OASIS_SYSTEM_PROBE_DAEMON->run_main (argc, argv);
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
