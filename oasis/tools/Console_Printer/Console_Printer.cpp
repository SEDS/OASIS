// $Id: Console_Printer.cpp 2095 2012-01-05 15:51:11Z dfeiock $

#include "ace/Null_Mutex.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/Singleton.h"
#include "ace/Signal.h"

#include "Console_Printer_Tool.h"

typedef ACE_Singleton <OASIS::Console_Printer_Tool, ACE_Null_Mutex> OASIS_CONSOLE_PRINTER_TOOL;

//
// server_sighandler
//
static void server_sighandler (int sig)
{
  OASIS_CONSOLE_PRINTER_TOOL::instance ()->shutdown ();
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
// main
//
int main (int argc, char * argv [])
{
  try
  {
    return OASIS_CONSOLE_PRINTER_TOOL::instance ()->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));
  }
}
