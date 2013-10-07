// $Id: driver.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "../FooImpl.h"
#include "oasis/EINode/Standard_EINode.h"

int main (int argc, char * argv [])
{
  try
  {
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - initializing EINode\n")));

    // Initialize the EINode.
    OASIS::Standard_EINode einode;
    if (0 != einode.init (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to initialize ")
                         ACE_TEXT ("EINode\n")),
                         1);

    // Register the Foo software probe.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - registering software probe\n")));

    OASIS::FooImpl foo_impl;
    foo_impl.init ("--name=FooProbe");
    if (0 != einode.register_probe (&foo_impl))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to register ")
                         ACE_TEXT ("software probe\n")),
                         1);

    // Activate the EINode.
    if (0 != einode.activate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to activate the")
                         ACE_TEXT ("EINode\n")),
                         1);

    // Deactivate the EINode.
    if (0 != einode.deactivate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to deactivate the")
                         ACE_TEXT ("EINode\n")),
                         1);

    // Finally, we can destroy it.
    einode.destroy ();

    return 0;
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }

  return 1;
}
