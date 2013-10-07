// $Id: client.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "oasis/EINode/Standard_EINode.h"

#include "Dummy_ProbeImpl.h"
#include "ace/OS_NS_unistd.h"
#include "ace/Signal.h"
#include "ace/Thread_Mutex.h"
#include "ace/Condition_T.h"

static ACE_Thread_Mutex test_lock;
static ACE_Condition <ACE_Thread_Mutex> wait_cond (test_lock);

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  ACE_GUARD (ACE_Thread_Mutex, guard, test_lock);
  wait_cond.signal ();

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
  try
  {
    OASIS::Standard_EINode einode;

    if (0 != einode.init (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to initialize ")
                         ACE_TEXT ("einode\n")),
                         1);

    Dummy_ProbeImpl probe;
    probe.init ("--name=DummyProbe");

    if (0 != einode.register_probe (&probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to register ")
                         ACE_TEXT ("dummy probe with einode\n")),
                         1);

    if (0 != einode.activate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to activate ")
                         ACE_TEXT ("einode\n")),
                         1);

    do
    {
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("%T (%t) - %M - waiting for test ")
                  ACE_TEXT ("to complete...\n")));

      ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, test_lock, 1);
      wait_cond.wait ();
    } while (0);

    if (0 != einode.deactivate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to deactivate ")
                         ACE_TEXT ("einode\n")),
                         1);

    // Finally, destroy the EI node.
    einode.destroy ();

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - test completed successfully\n")));

    return 0;
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - unknown exception\n")));


  }

  return 1;
}
