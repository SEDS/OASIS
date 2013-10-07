// $Id: OASIS_PDL.cpp 1896 2011-09-07 14:56:19Z hillj $

#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"
#include "OASIS_PDL_App.h"

#define OASIS_PDL_APP \
  ACE_Singleton <OASIS_PDL_App, ACE_Null_Mutex>::instance ()

//
// main
//
int ACE_TMAIN (int argc, char * argv [])
{
  try
  {
    // Initialize the logging priorities.
    const u_long default_mask = LM_EMERGENCY |
                                LM_ALERT |
                                LM_CRITICAL |
                                LM_ERROR |
                                LM_WARNING |
                                LM_NOTICE;

    ACE_LOG_MSG->priority_mask (default_mask, ACE_Log_Msg::PROCESS);

    return OASIS_PDL_APP->run_main (argc, argv);
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }

  return 1;
}
