// $Id: Websocket_Client_Acceptor.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "ace/Log_Msg.h"

#include "Websocket_Client_Acceptor.h"

namespace OASIS
{
  //
  // Constructor
  //
  Websocket_Client_Acceptor::
  Websocket_Client_Acceptor(ACE_Reactor *reactor)
  : ACE_Acceptor <OASIS_Websocket_Client_Handler, ACE_Websock_Acceptor>(reactor)
  {}

  //
  // make_svc_handler
  //
  int Websocket_Client_Acceptor::
  make_svc_handler (OASIS_Websocket_Client_Handler *& handler)
  {
    if (handler == 0)
      ACE_NEW_RETURN (handler,
                      OASIS_Websocket_Client_Handler,
                      -1);

    handler->reactor (this->reactor ());

    //inserting each client handler to the stack to keep reference
    if(-1 == this->clients_.push(handler))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to push handler on stack\n")),
                         -1);
    return 0;
  }

  //
  //handle_data
  //
  int Websocket_Client_Acceptor::
  handle_data(const DAC::Data_Packet &packet)
  {
    if(0 != this->clients_.size())
    {
      iterator iter(this->clients_);
      for (iter.first(); 1 != iter.done();iter.advance())
      {
        OASIS_Websocket_Client_Handler **handler;
        iter.next(handler);
        (*handler)->handle_data (packet);
      }
    }
    return 0;
  }
}
