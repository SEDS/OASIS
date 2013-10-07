//$ID$

#include "Websocket_Hertz_Command.h"
#include "oasis/DataAcquisitionController/Execution_Context.h"
#include "ace/SString.h"
#include "ace/CDR_Stream.h"
#include "Websocket_Client_Handler.h"

namespace OASIS
{
  //
  // execute ()
  //
  int OASIS_Websocket_Hertz_Command::execute
                  (OASIS_Websocket_Client_Handler * client_handler,
                   ACE_Message_Block &data)
  {
    ACE_InputCDR reader (&data);

    ACE_CString einode_name;
    reader.read_string (einode_name);

    ACE_CString probe_name;
    reader.read_string (probe_name);

    ACE_CString hertz;
    reader.read_string (hertz);

    ACE_CString command =probe_name;
    command += " ";
    command += "--hertz=";
    command += hertz;

   int retval = OASIS::DAC::EXECUTION_CONTEXT::instance ()->handle_command(einode_name,command);

    if (0 != retval)
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - handle_command () had %d error(s)\n"),
                  retval));

   return 0;
  }
}