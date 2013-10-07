// -*- C++ -*-

//=============================================================================
/**
 *  @file         Websocket_Command.h
 *
 *  $Id: Websocket_Command.h 2200 2012-06-08 05:20:00Z dpuranik $
 *
 *  @author       Darshan G. Puranik
 */
//=============================================================================

#ifndef _WEBSOCKET_COMMAND_H_
#define _WEBSOCKET_COMMAND_H_

#include "ace/Message_Block.h"
#include "Websocket_Client_Handler.h"

namespace OASIS
{
/**
 * @class OASIS_Websocket_Command
 */
  class OASIS_Websocket_Command
  {
  public:
    virtual int execute (OASIS_Websocket_Client_Handler *client_handler,
                         ACE_Message_Block &data) = 0;
  };
}

#endif //_WEBSOCKET_COMMAND_MANAGER_H_