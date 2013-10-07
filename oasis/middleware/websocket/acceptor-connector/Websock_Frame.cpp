//$Id $

#include "Websock_Frame.h"
#include "ace/Message_Block.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_Websock_Frame::ACE_Websock_Frame (void)
{

}

ACE_Websock_Frame::~ACE_Websock_Frame (void)
{
  delete[] payload_;
}

ACE_INT64
ACE_Websock_Frame::payload_length (void) const
{
  return this->payload_length_;
}

void
ACE_Websock_Frame::payload_length (ACE_INT64 len)
{
  this->payload_length_ = len;
  this->payload_= new char[this->payload_length_];
}

char*
ACE_Websock_Frame::payload (void)
{
  return this->payload_;
}

void
ACE_Websock_Frame::payload (char *payload)
{
  this->payload_ = payload;
}

void
ACE_Websock_Frame::masks (char masks[])
{
  for (int i = 0; i < 4; i++)
    this->masks_[i] = masks[i];
}

char*
ACE_Websock_Frame::masks (void)
{
  return this->masks_;
}

void
ACE_Websock_Frame::encode_or_decode_payload (char *buf) const
{
  for (int i = 0; i<this->payload_length_;i++)
  {
    buf[i] = buf[i] ^ this->masks_[i%4];
  }
}

char*
ACE_Websock_Frame::frame (void)
{
  // TODO : Use the memeber of this class and create the frame according to
  //        websocket protocol.
  char* frame;

  return frame;
}

ACE_END_VERSIONED_NAMESPACE_DECL