// $Id: Smoke_Test.cpp 1797 2011-04-11 21:47:50Z hillj $

#include "ace/Null_Mutex.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/Singleton.h"

#include "Smoke_Test_App.h"

typedef ACE_Singleton <Smoke_Test_App, ACE_Null_Mutex> SMOKE_TEST_APP;

//
// main
//
int main (int argc, char * argv [])
{
  try
  {
    return SMOKE_TEST_APP::instance ()->run_main (argc, argv);
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));
  }
}
