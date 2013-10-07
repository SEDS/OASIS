// $Id: driver.cpp 2149 2012-04-03 16:29:09Z dfeiock $

#include "oasis/EINode/Standard_EINode.h"
#include "oasis/probes/logging/ace/ACE_Logging_Software_Probe.h"

//
// init
//
int ACE_TMAIN (int argc, ACE_TCHAR * argv [])
{
  try
  {
    OASIS::Standard_EINode einode;

    // Initialize the EINode.
    if (0 != einode.init (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to initialize einode\n")),
                         1);

    // Load the configuration.
    if (0 != einode.load_configuration ("ace_logger.einode"))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to initialize einode\n")),
                         1);

    // Install the software probe.
    OASIS::ACE_Logging_Software_Probe ace_logger;
    ace_logger.init ("name=");

    einode.register_probe (&ace_logger);

    // Set the message callback for the logging framework. In this
    // case, its the software probe.
    ACE_Log_Msg * alm = ACE_Log_Msg::instance ();
    alm->set_flags (ACE_Log_Msg::MSG_CALLBACK);
    alm->clr_flags (ACE_Log_Msg::STDERR);

    alm->msg_callback (&ace_logger);

    // Activate the EINode
    if (0 != einode.activate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to activate EINode\n")),
                         1);

    // Send messages via ACE_Log_Msg.
    ACE_LOG_MSG->log (LM_INFO, "This is message 1");
    ACE_LOG_MSG->log (LM_INFO, "This is message 2");
    ACE_LOG_MSG->log (LM_INFO, "This is message 3");

    if (0 != einode.deactivate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to deactivate EINode\n")),
                         1);

    // Finally, destroy the EINode.
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
