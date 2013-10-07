// $Id: driver.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "../FooImpl.h"
#include "oasis/EINode/Standard_EINode.h"
#include "ace/OS_NS_unistd.h"

//
// multiple_servant_test
//
bool multiple_servant_test (::OASIS::Standard_EINode & einode)
{
  try
  {
    // Register the Foo software probe.
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - publisher: running multiple servant test\n")));

    ::OASIS::FooImpl foo_impl_1, foo_impl_2, foo_impl_3;
    foo_impl_1.init ("--name=FooImpl.1");
    foo_impl_2.init ("--name=FooImpl.2");
    foo_impl_3.init ("--name=FooImpl.3");

    if (0 != einode.register_probe (&foo_impl_1))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to register foo_impl_1")),
                         1);

    if (0 != einode.register_probe (&foo_impl_2))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to register foo_impl_1")),
                         1);

    if (0 != einode.register_probe (&foo_impl_3))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to register foo_impl_1")),
                         1);

    // Activate the EINode.
    if (0 != einode.activate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to activate the")
                         ACE_TEXT ("EINode\n")),
                         1);

    for (size_t i = 0; i < 10; i ++)
    {
      // Flush the data to the DAC.
      foo_impl_1.flush ();
      foo_impl_2.flush ();
      foo_impl_3.flush ();

      // Wait 1 second before sending the next event.
      ACE_OS::sleep (1);
    }

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - publisher: deactivating the EINode\n")));

    // Deactivate the EINode.
    if (0 != einode.deactivate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to deactivate the")
                         ACE_TEXT ("EINode\n")),
                         1);

    return true;
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - publisher exception: %s\n"),
                ex.what ()));
  }

  return false;
}

//
// main
//
int main (int argc, char * argv [])
{
  try
  {
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - publisher: initializing EI node\n")));

    // Initialize the EINode.
    ::OASIS::Standard_EINode einode;
    if (0 != einode.init (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to initialize EI node\n")),
                         1);

    // Execute the multiple servant test. This means we have multiple
    // software probe in the application.
    if (!multiple_servant_test (einode))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - multiple servant test failed\n")),
                         1);

    // Finally, we can destroy it.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - publisher: destroying EI node\n")));

    einode.destroy ();

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - publisher: test is complete!!\n")));

    return 0;
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - publisher: %s\n"),
                ex.what ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - publisher: caught unknown exception\n")));
  }

  return 1;
}
