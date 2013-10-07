// $Id:

#include "oasis/middleware/tena/bridges/Configuration_Manager.h"
#include "oasis/middleware/tena/bridges/Configuration_Group.h"
#include "oasis/middleware/tena/bridges/Configuration_Exception.h"

#include <iostream>
#include "ace/Log_Msg.h"
//
// main
//
int main (int argc, char * argv [])
{
  OASIS::Configuration_Group group;
  OASIS::Configuration_Manager manager;

  if (true != manager.parse (group, "test.config"))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to parse config file\n")),
                       1);

  try
  {
    group.instance ("a");
    group.instance ("a")->member("b");
    group.instance ("a")->member("b")->member("c");

    group.instance ("b");
    group.instance ("b")->member("b");
    group.instance ("b")->member("b")->member("c");
  }
  catch (OASIS::Invalid_Child & ex)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - member structure failed\n")),
                       1);
  }

  try
  {
    group["a"]["b"]["c"].value ();
    group["b"]["b"]["c"].value ();
  }
  catch (OASIS::Invalid_Child & ex)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - [] operators failed\n")),
                       1);
  }

  if ("asdf 1234" != group["a"]["b"]["c"].value ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - a.b.c value was not set properly\n")),
                       1);

  if ("qwer 0987" != group["b"]["b"]["c"].value ())
  ACE_ERROR_RETURN ((LM_ERROR,
                     ACE_TEXT ("%T (%t) - %M - b.b.c value was not set properly.\n")),
                     1);

  try
  {
    group["asdf"]["a"].name ();
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - invalid instance exception failed\n")),
                       1);

  }
  catch (OASIS::Invalid_Child & ex){}

  try
  {
    group["a"]["adsf"].name ();
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - invalid member exception failed\n")),
                       1);
  }
  catch (OASIS::Invalid_Child & ex){}

  return 0;
}
