// -*- C++ -*-

//=============================================================================
/**
 * @file        DAC_Websocket_Publisher_Service.h
 *
 * $Id: Websocket_Publisher_Service.h 2230 2013-01-24 14:47:29Z dfeiock $
 *
 * @author      Darshan G. Puranik
 */
//=============================================================================

#ifndef _OASIS_DAC_WEBSOCKET_SERVICE_H_
#define _OASIS_DAC_WEBSOCKET_SERVICE_H_

#include "Websocket_Publisher_Service_export.h"
#include "oasis/DataAcquisitionController/Data_Handler.h"
#include "oasis/middleware/websocket/acceptor-connector/Websock_Acceptor.h"
#include "Websocket_Client_Acceptor.h"
#include "oasis/middleware/websocket/acceptor-connector/Websock_Acceptor_Task.h"
#include "ace/Reactor.h"

namespace OASIS
{
// Forward decl.
class Software_Probe_Metadata;

/**
 * @class DAC_Websocket_Service
 *
 */
class DAC_Websocket_Publisher_Service
  : public DAC::Data_Handler
{
public:
  /// Default constructor.
  DAC_Websocket_Publisher_Service (void);

  /// Destructor.
  virtual ~DAC_Websocket_Publisher_Service (void);

  /// Initialize the service.
  virtual int init (int argc, char *argv []);
  virtual int fini (void);

  /// Handle a new data packet.
  virtual int handle_data (const DAC::Data_Packet &);

  /// Callback for handling new registration data.
  virtual int handle_registration (const DAC::Registration_Packet &);

  /// Callback for handling the destruction of einodes/probes.
  virtual int handle_unregister_einode (const DAC::Unregistration_Packet &);

private:
  /// Reator to run a loop which will handle I/O
  ACE_Reactor reactor_;

  /// Accept the connection
  Websocket_Client_Acceptor acceptor_;

  /// Task to accept connections in separate thread
  ACE_Websock_Acceptor_Task acceptor_task_;

  /// Helper method for parsing command-line options.
  int parse_args (int argc, char *argv [] );
};

}

//Declare the service factory.
OASIS_DAC_DATA_HANDLER_DECL (OASIS_DAC_WEBSOCKET_PUBLISHER_SERVICE, _make_OASIS_DAC_Websocket_Publisher_Service);

#endif
