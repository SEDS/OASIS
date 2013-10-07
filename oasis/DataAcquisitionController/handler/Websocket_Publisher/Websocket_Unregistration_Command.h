// -*- C++ -*-

//=============================================================================
/**
 *  @file         Websocket_Handle_Unregistration_Command.h
 *
 *  $Id: Websocket_Unregistration_Command.h 2200 2012-06-08 05:20:00Z dpuranik $
 *
 *  @author       Darshan G. Puranik
 */
//=============================================================================

#ifndef _WEBSOCKET_HANDLE_UNREGISTRATION_COMMAND_H_
#define _WEBSOCKET_HANDLE_UNREGISTRATION_COMMAND_H_

#include "ace/Message_Block.h"
#include "Websocket_Command.h"

namespace OASIS
{
/**
 * @class OASIS_Websocket_Handle_Hertz_Command
 */
  class OASIS_Websocket_Unregistration_Command : public OASIS_Websocket_Command
  {
  public:
    //Execute command
    virtual int execute (OASIS_Websocket_Client_Handler *client_handler,
                         ACE_Message_Block &data);
  };
}
#endif //_WEBSOCKET_HANDLE_UNREGISTRATION_COMMAND_H_