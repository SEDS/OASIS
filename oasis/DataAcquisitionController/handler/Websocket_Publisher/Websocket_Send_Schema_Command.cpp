// $Id $

#include "Websocket_Send_Schema_Command.h"
#include "ace/CDR_Stream.h"
#include "Websocket_Client_Handler.h"

namespace OASIS
{
  int
  OASIS_Websocket_Send_Schema_Command::execute
                      (OASIS_Websocket_Client_Handler * client_handler,
                      ACE_Message_Block &data)
  {
    ACE_InputCDR reader (&data);
    // Read the data from message block use that data to complete command
    return 0;
  }
}