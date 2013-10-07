// $Id: Websocket_Publisher_Service.cpp 2204 2012-06-08 17:56:19Z dpuranik $

#include "Websocket_Publisher_Service.h"

#include "ace/INET_Addr.h"
#include "ace/Log_Msg.h"
#include "ace/streams.h"

#include "oasis/probes/Software_Probe.h"
#include "oasis/DataAcquisitionController/Data_Packet.h"
#include "oasis/DataAcquisitionController/Execution_Context.h"

OASIS_DAC_DATA_HANDLER_IMPL (_make_OASIS_DAC_Websocket_Publisher_Service, OASIS::DAC_Websocket_Publisher_Service);

namespace OASIS
{
  //
  // DAC_Websocket_Publisher_Service
  //
  DAC_Websocket_Publisher_Service::DAC_Websocket_Publisher_Service (void)
    : acceptor_(&reactor_),
      acceptor_task_(&reactor_)
  {
    //std::cerr << "DAC_Websocket_Publisher_Service ()" << std::endl;
  }

  //
  // ~DAC_Archive_Service
  //
  DAC_Websocket_Publisher_Service::~DAC_Websocket_Publisher_Service (void)
  {
  }

  //
  // init
  //
  int DAC_Websocket_Publisher_Service::init (int argc, ACE_TCHAR * argv [])
  {
    ACE_INET_Addr ipaddr (argv[0], argv[1]);

    if (0 != this->acceptor_.open (ipaddr,&this->reactor_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to listen on %s:%d\n"),
                         ipaddr.get_host_name (),
                         ipaddr.get_port_number ()),
                        -1);

    if (-1 == acceptor_task_.activate())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to activate task.\n")),
                         -1);

    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - listening on %s:%d\n"),
                ipaddr.get_host_name (),
                ipaddr.get_port_number ()));

    return 0;
  }

  //
  // fini
  //
  int DAC_Websocket_Publisher_Service::fini (void)
  {
    this->acceptor_.reactor()->end_reactor_event_loop ();

    return 0;
  }

  //
  // handle_data
  //
  int DAC_Websocket_Publisher_Service::handle_data (const DAC::Data_Packet & packet)
  {
    this->acceptor_.handle_data(packet);

    return 0;
  }

  //
  //handle_registration()
  //
  int DAC_Websocket_Publisher_Service::handle_registration (const DAC::Registration_Packet & packet)
  {
    return 1;
  }

  //
  //handle_unregister_einode()
  //
  int DAC_Websocket_Publisher_Service::handle_unregister_einode (const DAC::Unregistration_Packet & packet)
  {
    return 1;
  }
}


