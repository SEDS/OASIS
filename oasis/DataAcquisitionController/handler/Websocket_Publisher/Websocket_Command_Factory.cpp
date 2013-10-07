// $ID $
#include "Websocket_Command.h"
#include "Websocket_Hertz_Command.h"
#include "Websocket_Registration_Command.h"
#include "Websocket_Unregistration_Command.h"
#include "Websocket_Send_Schema_Command.h"
#include "Websocket_Command_Factory.h"

namespace OASIS
{
  OASIS_Websocket_Command *
  OASIS_Websocket_Command_Factory::create_command (char opcode)
  {
     switch (opcode)
    {
      // cases are opcode

      // handle registration of probes
     case 0x01:
      {
        return new OASIS_Websocket_Registration_Command ();
      }
      //handle unregistration of probes;
      case 0x02:
      {
        return new OASIS_Websocket_Unregistration_Command ();
      }
      // handle hertz of probe
      case 0x03:
      {
        return new OASIS_Websocket_Hertz_Command ();
      }
      // sedn probe schema
      case 0x04:
      {
        return new OASIS_Websocket_Send_Schema_Command ();
      }
    }
     return 0;
  }
}