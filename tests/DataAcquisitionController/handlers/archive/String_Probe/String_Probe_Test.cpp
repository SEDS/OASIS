// $Id: String_Probe_Test.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "oasis/EINode/Standard_EINode.h"
#include "ace/OS_NS_unistd.h"

#include "String_ProbeImpl.h"

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  try
  {
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - initializing the EINode\n")));

    // Initialize the EINode.
    OASIS::Standard_EINode einode;
    if (0 != einode.init (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to initialize EINode\n")),
                         -1);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - loading the EINode's configuration\n")));

    // Load the configuration.
    if (0 != einode.load_configuration ("String_Probe.einode"))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to load configuration\n")),
                         -1);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - registing the software probes\n")));

    Test::String_ProbeImpl str_probe;
    str_probe.init ("name=StringProbe.1");
    einode.register_probe (&str_probe);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - activating the EINode\n")));

    // Activate the EINode.
    if (0 != einode.activate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to activate EINode\n")),
                         -1);

    // Force 1 entry into the database.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - flushing probe and waiting for 5 seconds...\n")));

    str_probe.str_value ("Hello, World!");
    str_probe.flush ();

    str_probe.str_value ("This is another string value");
    str_probe.flush ();

    ACE_OS::sleep (5);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - deactivating the EINode\n")));

    if (0 != einode.deactivate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                   ACE_TEXT ("%T (%t) - %M - failed to deactivate EINode\n")),
                   -1);

    // Destroy the EINode.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - destoying the EINode\n")));

    einode.destroy ();

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - test completed successfully\n")));

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
