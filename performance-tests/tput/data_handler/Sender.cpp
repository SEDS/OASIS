// $Id: Sender.cpp 2142 2012-03-26 18:02:24Z dfeiock $

#include "ace/Null_Mutex.h"
#include "ace/Signal.h"
#include "ace/Singleton.h"

#include "Sender_App.h"

#define SENDER_APP \
  ACE_Singleton <Sender_App, ACE_Null_Mutex>::instance ()

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  SENDER_APP->shutdown ();
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
    // Register the signal handlers.
    register_sighandler ();

    return SENDER_APP->run_main (argc, argv);
  }
  catch (...)
  {

  }

  return 1;
}
