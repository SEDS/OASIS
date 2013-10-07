// $Id $
#include "ace/CDR_Stream.h"

#include "Websocket_Registration_Command.h"
#include "Websocket_Client_Handler.h"

namespace OASIS
{
  int
  OASIS_Websocket_Registration_Command::execute
                              (OASIS_Websocket_Client_Handler *client_handler,
                              ACE_Message_Block &data)
  {
    ACE_InputCDR reader (&data);

    char *einode_name;
    reader.read_string(einode_name);
    char *probe_name;
    reader.read_string (probe_name);

    client_handler->get_subscribed_probes()->push_back ((std::string)probe_name);

    return 0;
  }
}