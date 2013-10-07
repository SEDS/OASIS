// -*- C++ -*-

//=============================================================================
/**
 *  @file         Websocket_Client_Acceptor.h
 *
 *  $Id: Websocket_Client_Acceptor.h 2230 2013-01-24 14:47:29Z dfeiock $
 *
 *  @author       Darshan G. Puranik
 */
//=============================================================================

#ifndef _WEBSOCKET_CLIENT_ACCEPTOR_H_
#define _WEBSOCKET_CLIENT_ACCEPTOR_H_

#include <string>
#include "ace/Acceptor.h"
#include "ace/Reactor.h"
#include "ace/Containers_T.h"

#include "oasis/middleware/websocket/acceptor-connector/Websock_Acceptor.h"
#include "Websocket_Client_Handler.h"
#include "oasis/DataAcquisitionController/Registration_Packet.h"

namespace OASIS
{
/**
 * @class Websocket_Client_Acceptor
 */
class Websocket_Client_Acceptor :
  public ACE_Acceptor <OASIS_Websocket_Client_Handler, ACE_Websock_Acceptor>
{
public:
  ///
  typedef ACE_Unbounded_Stack_Iterator<OASIS_Websocket_Client_Handler *> iterator;

  /// Constructor
  Websocket_Client_Acceptor(ACE_Reactor* reactor);

  /// create new handler for each new connection
  int make_svc_handler (OASIS_Websocket_Client_Handler *& sh);

  /// delegating sending to handler
  int handle_data (const DAC::Data_Packet & packet);

private:
  ///keep record of clients connected to Websocket handler.
  ACE_Unbounded_Stack <OASIS_Websocket_Client_Handler *> clients_;
};

}

#endif
