// $Id: subscriber.cpp 1805 2011-06-04 21:46:30Z hillj $

#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"
#include "ace/Signal.h"

#include "Smoke_Test_Subscriber.h"

typedef ACE_Singleton <Smoke_Test_Subscriber, ACE_Null_Mutex> SMOKE_TEST_SUBSCRIBER;

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  SMOKE_TEST_SUBSCRIBER::instance ()->shutdown ();
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
    return SMOKE_TEST_SUBSCRIBER::instance ()->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));
  }

  return 1;
}
