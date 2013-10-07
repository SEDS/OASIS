// -*- C++ -*-

//=============================================================================
/**
 *  @file         Websocket_Client_Handler.h
 *
 *  $Id: Websocket_Client_Handler.h 2230 2013-01-24 14:47:29Z dfeiock $
 *
 *  @author       Darshan G. Puranik
 */
//=============================================================================

#ifndef _WEBSOCKET_CLIENT_HANDLER_H_
#define _WEBSOCKET_CLIENT_HANDLER_H_

#include "oasis/middleware/websocket/acceptor-connector/Websock_Svc_Handler.h"
#include "Websocket_Command_Factory.h"
#include "oasis/DataAcquisitionController/Data_Handler.h"
#include <list>

namespace OASIS
{
/**
 * @class OASIS_Websocket_Client_Handler
 */
  class OASIS_Websocket_Client_Handler : public ACE_Websock_Svc_Handler
  {
  public:
    ///Default constructor
    OASIS_Websocket_Client_Handler (void);

    ///Default destructor
    ~OASIS_Websocket_Client_Handler (void);

    /// Handle data coming from web
    int handle_web_input (ACE_Message_Block *message);

    /// Send the data to clients subscribed to perticular probe
    int handle_data (const DAC::Data_Packet &packet);

    std::list<std::string>* get_subscribed_probes (void);

  private:
    /// list of subscribed probes.
    std::list<std::string> subscribed_probes_;

    //Factory to create commands
    OASIS_Websocket_Command_Factory command_factory_;
  };
}

#endif
