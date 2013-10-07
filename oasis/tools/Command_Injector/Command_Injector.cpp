// $Id: Command_Injector.cpp 1971 2011-10-03 20:07:30Z hillj $

//=============================================================================
/**
 *  @file         Command_Injector.cpp
 *
 *  $Id: Command_Injector.cpp 1971 2011-10-03 20:07:30Z hillj $
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _OASIS_COMMAND_INJECTOR_H_
#define _OASIS_COMMAND_INJECTOR_H_

#include "ace/Null_Mutex.h"
#include "ace/Signal.h"
#include "ace/Singleton.h"

#include "Command_Injector_App.h"

#define OASIS_COMMAND_INJECTOR_APP \
  ACE_Singleton <OASIS::Command_Injector_App, ACE_Null_Mutex>

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  OASIS_COMMAND_INJECTOR_APP::instance ()->shutdown ();
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
    ::register_sighandler ();

    int retval = OASIS_COMMAND_INJECTOR_APP::instance ()->run_main (argc, argv);
    return retval == 0 ? 0 : 1;
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception ")
                ACE_TEXT ("in main\n")));
  }

  return 1;
}

#endif  // !defined _OASIS_COMMAND_INJECTOR_H_
