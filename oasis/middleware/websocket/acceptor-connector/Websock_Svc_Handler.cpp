// $Id $

#include "Websock_Svc_Handler.h"

#include "ace/Log_Msg.h"

#include <bitset>
#include <iostream>
#include <string>

ACE_BEGIN_VERSIONED_NAMESPACE_DECL
//
//Constructor
//
ACE_Websock_Svc_Handler::ACE_Websock_Svc_Handler (void)
  : head_(new ACE_Message_Block()),
    curr_(head_)

{

}

//
//Destructor
//
ACE_Websock_Svc_Handler::~ACE_Websock_Svc_Handler (void)
{
  this->head_->release ();
}

//
//handle_input
//
int ACE_Websock_Svc_Handler::handle_input (ACE_HANDLE fd)
{
  //This switch case is dependent on Fin bit of received wesocket frame.
  //If Fin bit is 0(case 0) that means this frame is one of the frame
  //fragmented message and we should receive the next frame and bind it
  //with previous frames. If Fin bit 1 (case 1) that means this is the
  //last frame of fragmented message and after receiving this frame we
  //process the message.
  switch (this->peer().init ())
  {
  case 0:
    {
      ACE_Message_Block *temp = new ACE_Message_Block
                               (this->peer ().get_web_message_length ());

      this->peer().recv_web_message (temp);

      this->curr_->cont (temp);
      this->curr_ = this->curr_->cont ();

      break;
    }
  case 1:
    {
      ACE_Message_Block *temp = new ACE_Message_Block
                               (this->peer ().get_web_message_length ());

      this->peer().recv_web_message (temp);

      this->curr_->cont (temp);

      if (0 == this->handle_web_input (this->head_->cont ()))
        this->head_->cont()->release();

      break;
    }
  }

  return 0;
}

int ACE_Websock_Svc_Handler::handle_web_input (ACE_Message_Block *message)
{
  return 0;
}

ACE_END_VERSIONED_NAMESPACE_DECL
