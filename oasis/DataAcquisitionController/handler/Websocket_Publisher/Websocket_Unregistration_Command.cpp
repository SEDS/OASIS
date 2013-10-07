// $Id $
#include "ace/CDR_Stream.h"

#include "Websocket_Unregistration_Command.h"
#include "Websocket_Client_Handler.h"

namespace OASIS
{
  int
  OASIS_Websocket_Unregistration_Command::execute
                        (OASIS_Websocket_Client_Handler *client_handler,
                        ACE_Message_Block &data)
  {
    ACE_InputCDR reader (&data);

    char *einode_name;
    reader.read_string(einode_name);
    char *probe_name;
    reader.read_string (probe_name);

    for (std::list<std::string>::iterator it=client_handler->get_subscribed_probes()->begin(), end= client_handler->get_subscribed_probes()->end();
         it!=end;
         it++)
    {
      if ( 0 == (*it).compare (probe_name))
      {
        it = client_handler->get_subscribed_probes()->erase (it);
        break;
      }
    }
    return 0;
  }
}