// -*- C++ -*-

//=============================================================================
/**
 *  @file         Websocket_Command_Factory.h
 *
 *  $Id: Websocket_Command_Factory.h 2200 2012-06-08 05:20:00Z dpuranik $
 *
 *  @author       Darshan G. Puranik
 */
//=============================================================================

#ifndef _WEBSOCKET_COMMAND_MANAGER_H_
#define _WEBSOCKET_COMMAND_MANAGER_H_

namespace OASIS
{
  //Forward Declaration
  class OASIS_Websocket_Command;

/**
 * @class OASIS_Websocket_Command_Manager
 */
  class OASIS_Websocket_Command_Factory
  {
  public:
    virtual OASIS_Websocket_Command *create_command (char opcode);
  };
}

#endif //_WEBSOCKET_COMMAND_MANAGER_H_
