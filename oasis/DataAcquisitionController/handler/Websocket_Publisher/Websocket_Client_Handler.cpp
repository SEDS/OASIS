//$Id $
#include "ace/Message_Block.h"
#include "ace/CDR_Stream.h"

#include "oasis/DataAcquisitionController/Data_Packet.h"
#include "oasis/probes/Software_Probe_Header.h"

#include "Websocket_Command.h"
#include "Websocket_Client_Handler.h"


namespace OASIS
{
  //
  // Constructor
  //
  OASIS_Websocket_Client_Handler::OASIS_Websocket_Client_Handler (void)
  {
    // Implementation
  }

  //
  // Destructor
  //
  OASIS_Websocket_Client_Handler::~OASIS_Websocket_Client_Handler (void)
  {
    // Implementation
  }

  //
  // handle_web_input
  //
  int OASIS_Websocket_Client_Handler::handle_web_input (ACE_Message_Block *message)
  {
    ACE_InputCDR reader(message);
    char opcode;
    reader.read_char (opcode);
    message->rd_ptr(1);
    OASIS_Websocket_Command *command = this->command_factory_.create_command (opcode);
    command->execute(this, *message);
    return 0;
  }

  //
  //handle_data()
  //
  int
  OASIS_Websocket_Client_Handler::handle_data (const DAC::Data_Packet &packet)
  {
    Software_Probe_Header probe;
    int retval = probe.recall (packet.probe_data (),
                               packet.probe_data_length (),
                               packet.byte_order ());

    if (0 != retval)
    {
      ACE_Utils::UUID uuid;
      packet.einode_uuid (uuid);
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to recall data ")
                         ACE_TEXT ("from EINode %s\n"),
                         uuid.to_string ()->c_str ()),
                         -1);
    }

    std::list<std::string>::iterator iter;
    for (iter =this->subscribed_probes_.begin();
         iter != this->subscribed_probes_.end();
         iter++)
    {
      if (0 == (*iter).compare(probe.name_.c_str ()))
      {
        this->peer().send_n(packet.probe_data (),
                            packet.probe_data_length (),
                            ACE_Websock_Stream::binary_frame);
        break;
      }
    }

    return 0;
  }

  std::list<std::string>*
  OASIS_Websocket_Client_Handler::get_subscribed_probes (void)
  {
    return &this->subscribed_probes_;
  }

}
