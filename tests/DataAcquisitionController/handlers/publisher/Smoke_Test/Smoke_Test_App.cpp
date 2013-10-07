// $Id: Smoke_Test_App.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "Smoke_Test_App.h"
#include "Smoke_Test_ProbeImpl.h"

#include "oasis/EINode/Standard_EINode.h"
#include "ace/OS_NS_unistd.h"

//
// Smoke_Test_App
//
Smoke_Test_App::Smoke_Test_App (void)
{

}

//
// ~Smoke_Test_App
//
Smoke_Test_App::~Smoke_Test_App (void)
{

}

//
// run_main
//
int Smoke_Test_App::run_main (int argc, char * argv [])
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
    if (0 != einode.load_configuration ("Smoke_Test.xml"))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to load configuration\n")),
                         -1);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - registing the software probes\n")));

    SmokeTest::CImpl c_probe;
    c_probe.init ("--name=SmokeTest::C");
    einode.register_probe (&c_probe);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - activating the EINode\n")));

    // Activate the EINode.
    if (0 != einode.activate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to activate EINode\n")),
                         -1);

    // Send data to the DAC, which should be sent to the subscribers.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - activating the EINode\n")));

    for (size_t i = 0; i < 10; ++ i)
      c_probe.flush ();

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - deactivating the EINode\n")));

    // Let's sleep for 10 seconds...
    ACE_OS::sleep (10);

    if (0 != einode.deactivate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                   ACE_TEXT ("%T (%t) - %M - failed to deactivate EINode\n")),
                   -1);

    // Destroy the EINode.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - destoying the EINode\n")));

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
