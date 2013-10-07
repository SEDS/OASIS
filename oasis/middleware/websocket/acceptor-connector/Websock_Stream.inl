// -*- C++ -*-
//
// $Id: Websock_Stream.inl 2230 2013-01-24 14:47:29Z dfeiock $

#include "Websock_Stream.h"

#include "ace/OS_NS_sys_socket.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE
ACE_Websock_Stream::ACE_Websock_Stream (void)
{
  // ACE_TRACE ("ACE_Websock_Stream::ACE_Websock_Stream");
}

ACE_INLINE
ACE_Websock_Stream::ACE_Websock_Stream (ACE_HANDLE h)
{
  // ACE_TRACE ("ACE_Websock_Stream::ACE_Websock_Stream");
  this->set_handle (h);
}

ACE_INLINE
ACE_Websock_Stream::~ACE_Websock_Stream (void)
{
  // ACE_TRACE ("ACE_Websock_Stream::~ACE_Websock_Stream");
}

ACE_INLINE
int ACE_Websock_Stream::get_web_message_length (void)
{
  return this->frame_.payload_length();
}

ACE_INLINE
int ACE_Websock_Stream::handle_pong_frame (void)
{
  return 1;
}

ACE_INLINE
int ACE_Websock_Stream::handle_ping_frame (void)
{
  return 1;
}

ACE_INLINE
int ACE_Websock_Stream::handle_close_frame (void)
{
  return 1;
}

ACE_END_VERSIONED_NAMESPACE_DECL