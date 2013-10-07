// $Id: Websock_Stream.cpp 2230 2013-01-24 14:47:29Z dfeiock $

#include "Websock_Stream.h"
#include "ace/SString.h"
#include "Websock_Frame.h"

#include <bitset>
#include <iostream>
#include <cmath>
#include <sstream>

#if !defined (__ACE_INLINE__)
#include "WEBSOCK_Stream.inl"
#endif /* __ACE_INLINE__ */

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_ALLOC_HOOK_DEFINE(ACE_Websock_Stream)

#pragma pack (push , 2)
  union header_t
  {
    struct
    {
      unsigned char opcode: 4;
      unsigned char rsv3: 1;
      unsigned char rsv2: 1;
      unsigned char rsv1: 1;
      unsigned char fin: 1;
      unsigned char payload_length: 7;
      unsigned char mask: 1;
    } bitmask;
    unsigned short value;
  };
#pragma pack (pop)

void
ACE_Websock_Stream::dump (void) const
{
#if defined (ACE_HAS_DUMP)
ACE_TRACE ("ACE_Websock_Stream::dump");
#endif /* ACE_HAS_DUMP */
}

int
ACE_Websock_Stream::init (void)
{
  char header[2];
  ACE_SOCK_Stream::recv(header,2);

  std::bitset<CHAR_BIT> header_temp (header[0]);
  // code to discard pong frame if it is there.
  // 0xA is hex value for pong frame
  if (0xA == header[0] || 0x8 == header[0] || 0x9 == header[0] || 0 == header_temp[7])
  {
    // This code is for testing
    std::bitset<CHAR_BIT> test (header[0]);

    // TODO : Handle control frames.

    // Finding out frame is real data from browser or garbage
    if (0x81 == header[1] || 0x82 == header[1])
    {
      header[0] = header[1];
      char temp[1];
      ACE_SOCK_Stream::recv(temp,1);
      header[1] = temp[0];
    }
    else
      return -1;
  }

  std::bitset<CHAR_BIT> header_t (header[0]);

  this->frame_.header_.value=0;
  this->frame_.header_.bitmask.fin = header_t[7];

  // hiding the fin bit to get the value for opcode
  header_t[7] = 0;
  this->frame_.header_.bitmask.opcode = header_t.to_ulong();

  header_t = header[1];
  this->frame_.header_.bitmask.mask = header_t[7];

  //hiding the mask bit to get the length from rest of 7 bits
  header_t[7] = 0;
  short length = header_t.to_ulong();

  switch (length)
  {
    case 126:
    {
      char buffer [2];
      ACE_SOCK_Stream::recv (buffer,2);
      this->frame_.payload_length (binary_to_int64(buffer,16));
      break;
    }
    case 127:
    {
      char buffer [8];
      ACE_SOCK_Stream::recv (buffer,8);
      this->frame_.payload_length (binary_to_int64(buffer,64));
      break;
    }
    default:
    {
      this->frame_.payload_length((ACE_INT64)length);
    }
  }

  if (1 == this->frame_.header_.bitmask.mask)
    ACE_SOCK_Stream::recv_n (this->frame_.masks(),4);;

  return this->frame_.header_.bitmask.fin;
}

ACE_INT64
ACE_Websock_Stream::binary_to_int64 (char *buffer, unsigned short num_of_bits)
{
  std::bitset<8> buf;
  ACE_INT64 value = 0;
  int bit_pos = 0;
  int counter = num_of_bits/8;
  for (int i = counter - 1; i > -1; i--)
  {
    buf = buffer[i];
    for (int j = 0; j < 8; j++)
    {
      if (1 == buf[j])
        value += pow((double)2, bit_pos);

      bit_pos++;
    }
  }

  return value;
}

int
ACE_Websock_Stream::recv_web_message (ACE_Message_Block *message)
{
  size_t bytes_transferred=0;
  ACE_SOCK_Stream::recv_n (message->base (),
                           message->capacity (),
                           0,
                           &bytes_transferred);

  message->wr_ptr(bytes_transferred);
  this->frame_.encode_or_decode_payload(message->base());

  return 0;
}

ssize_t
ACE_Websock_Stream::recv_n (void *buf,
                            ACE_INT64 len,
                            const ACE_Time_Value *timeout,
                            ACE_INT64 *bytes_transferred) const
{
  ACE_INT64 payload_length = this->frame_.payload_length();
  if (payload_length > len)
  {
    bytes_transferred = &payload_length;
    return -1;
  }

  ACE_SOCK_Stream::recv_n(buf,
                          payload_length);

  this->frame_.encode_or_decode_payload((char *)buf);

  return 0;
}
//
////This method send the data as a text_frame if user doesnt provide
////opcode.
ssize_t
ACE_Websock_Stream::send_n (const void *buf,
                            size_t len,
                            const ACE_Time_Value *timeout,
                            size_t *bytes_transferred) const
{
  ACE_TRACE ("ACE_Websock_Stream::send_n");
  return this->send_n ((const char *)buf,
                       len,
                       binary_frame,
                       false,
                       timeout,
                       bytes_transferred);
}

ssize_t
ACE_Websock_Stream::send_n (const char *buf,
                            size_t len,
                            opcode frame_opcode,
                            bool is_masking,
                            const ACE_Time_Value *timeout,
                            size_t *bytes_transferred) const
{
  ACE_TRACE ("ACE_Websock_Stream::send_n");

  iovec iov[4];
  header_t header;
  header.value = 0;
  header.bitmask.fin = 1;
  header.bitmask.opcode = frame_opcode;

  if ( 125 < len && 65536 > len)
  {
    header.bitmask.payload_length = 126;

    char masks[4];
    if (is_masking)
    {
      header.bitmask.mask = 1;
      this->encode_data(masks, (char *)buf, len);
      iov[2].iov_base = masks;
      iov[2].iov_len = 4;
    }
    else
      iov[2].iov_len = 0;

    iov[0].iov_base = (char*) &header.bitmask;
    iov[0].iov_len = 2;

    union
    {
      unsigned short length;
      char length_char[2];
    }length_union;

    length_union.length = (unsigned short) len;
    char temp[2];
    temp[0] = length_union.length_char[1];
    temp[1] = length_union.length_char[0];

    iov[1].iov_base = temp;
    iov[1].iov_len = 2;

    iov[3].iov_base = (char *) buf;
    iov[3].iov_len = len;
  }
  else if (65536 < len)
  {
    header.bitmask.payload_length = 127;

    char masks[4];
    if (is_masking)
    {
      header.bitmask.mask = 1;
      this->encode_data(masks, (char *)buf, len);
      iov[2].iov_base = masks;
      iov[2].iov_len = 4;
    }
    else
      iov[2].iov_len = 0;

    iov[0].iov_base = (char*) &header.bitmask;
    iov[0].iov_len = 2;

    ACE_INT64 length = (ACE_INT64) len;
    iov[1].iov_base = (char *) &len;
    iov[1].iov_len = 8;

    iov[3].iov_base = (char *) buf;
    iov[3].iov_len = len;
  }
  else
  {
    header.bitmask.payload_length = len;

    char masks[4];
    if (is_masking)
    {
      header.bitmask.mask = 1;
      this->encode_data(masks, (char *)buf, len);
      iov[2].iov_base = masks;
      iov[2].iov_len = 4;
    }
    else
      iov[2].iov_len = 0;

    iov[0].iov_base = (char*) &header.bitmask;
    iov[0].iov_len = 2;

    iov[1].iov_len = 0;

    iov[3].iov_base = (char *) buf;
    iov[3].iov_len = len;
  }

  size_t bytes_xferred;
  ACE_SOCK_Stream::sendv_n(iov,
                           4,
                           timeout,
                           &bytes_xferred);

  if(0x00 != bytes_transferred)
    return *bytes_transferred = bytes_xferred - 2;

  return bytes_xferred - 2;
}

void
ACE_Websock_Stream::encode_data (char *mask,
                                 char *buf,
                                 size_t len) const
{
  for (int i = 0; i < len;i++)
    buf[i] = buf[i] ^ mask[i%4];
}

ssize_t
ACE_Websock_Stream::send_n (const ACE_Message_Block *message_block,
                            opcode frame_opcode,
                            const ACE_Time_Value *timeout,
                            size_t *bytes_transferred) const
{
  ACE_TRACE ("ACE_Websock_Stream::send_n");

  header_t header;
  header.value = 0;
  header.bitmask.fin = 1;
  header.bitmask.opcode = frame_opcode;
  header.bitmask.payload_length = message_block->total_length();

  ACE_Message_Block* frame = new ACE_Message_Block((const char *)& header.bitmask,
                                                    sizeof(header));

  frame->wr_ptr(sizeof(header));
  frame->cont(const_cast<ACE_Message_Block *>(message_block));

  size_t bytes_xferred;
  return ACE_SOCK_Stream::send_n(frame,
                                 timeout,
                                 &bytes_xferred);

  if(0x00 != bytes_transferred)
    return *bytes_transferred = bytes_xferred - sizeof(header);

  return bytes_xferred- sizeof(header);
}

ssize_t
ACE_Websock_Stream::sendv_n (const iovec iov[],
                             int n,
                             opcode frame_opcode,
                             const ACE_Time_Value *timeout,
                             size_t *bytes_transferred) const
{
  ACE_TRACE ("ACE_Websock_Stream::send_n");

  int total_vectors = n + 1;
  iovec* frame = new iovec[total_vectors];

  header_t header;
  header.value = 0;
  header.bitmask.fin = 1;
  header.bitmask.opcode = frame_opcode;

  for (int vector_count = 0; vector_count < n; vector_count++)
  {
    header.bitmask.payload_length += iov[vector_count].iov_len;
    frame[vector_count + 1] = iov[vector_count];
  }

  frame[0].iov_base = (char *)& header.bitmask;
  frame[0].iov_len = sizeof(header);

  size_t bytes_xferred;
  ACE_SOCK_Stream::sendv_n(frame,
                           total_vectors,
                           timeout,
                           &bytes_xferred);

  if(0x00 != bytes_transferred)
    return *bytes_transferred = bytes_xferred - sizeof(header);

  return bytes_xferred - sizeof(header);
}

ACE_END_VERSIONED_NAMESPACE_DECL
