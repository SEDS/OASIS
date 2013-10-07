// $Id: driver.cpp 2149 2012-04-03 16:29:09Z dfeiock $

#include "oasis/probes/system/network/NetworkProbe_Impl.h"
#include "oasis/EINode/Standard_EINode.h"
#include "ace/OS_NS_unistd.h"

//
// servant_test
//
bool servant_test (::OASIS::Standard_EINode & einode)
{
  try
  {
    // Register the Processor software probe.
    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - publisher: running servant test\n")));

    ::OASIS::System::Network::SystemNetworkProbe_Impl net_impl;

    // Init the probe, hardcoded to eth0 for now
    if (0 != net_impl.init ("--nic=eth0 --name=NetworkProbeImpl"))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - probe impl failed to init\n")),
                         false);

    if (0 != einode.register_probe (&net_impl))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to register net_impl")),
                         false);

    // Activate the EINode.
    if (0 != einode.activate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to activate the")
                         ACE_TEXT ("EINode\n")),
                         false);

    for (size_t i = 0; i < 10; i ++)
    {
      // Get the data
      if (0 != net_impl.handle_collect_data ())
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%T (%t) - %M - probe impl failed to collect data\n")),
                           false);

      // Flush the data to the DAC.
      net_impl.flush ();

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
                         false);

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

    // Execute the servant test. This means we have one
    // software probe in the application.
    if (!servant_test (einode))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - servant test failed\n")),
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
