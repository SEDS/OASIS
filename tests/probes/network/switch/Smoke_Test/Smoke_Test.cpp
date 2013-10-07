// $Id: Smoke_Test.cpp 2214 2012-08-10 15:00:08Z dfeiock $

#include "oasis/EINode/Standard_EINode.h"
#include "ace/OS_NS_unistd.h"
#include "ace/Log_Msg.h"

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  try
  {
    OASIS::Standard_EINode einode;
    static const char * einode_config = "Smoke_Test.einode";

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - initializing the Einode\n"),
                einode_config));

    if (0 != einode.init (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to initialize EINode\n")),
                         -1);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - loading configuration %s\n"),
                einode_config));

    if (0 != einode.load_configuration (einode_config))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to load %s"),
                         einode_config),
                         -1);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - activating the Einode\n")));

    if (0 != einode.activate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to activate Einode")),
                         -1);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - sleeping...\n")));

    // Sleep for some time.
    ACE_OS::sleep (5);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - deactivating the Einode\n")));

    // Deactivate the EINode, and destroy it.
    if (0 != einode.deactivate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to deactivate Einode\n")),
                         -1);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - destroying the Einode\n")));

    // Destroy the EINode and its resources.
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
