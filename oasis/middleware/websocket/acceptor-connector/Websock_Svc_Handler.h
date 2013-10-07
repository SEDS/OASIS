// -*- C++ -*-

//=============================================================================
/**
 * @file        Websock_Svc_Handler.h
 *
 * $ id $
 *
 * @author      Darshan G. Puranik
 */
//=============================================================================

#ifndef _WEBSOCKET_CLIENT_SERVICE_H_
#define _WEBSOCKET_CLIENT_SERVICE_H_
#include "ace/pre.h"

#if !defined(ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "Websock_Stream.h"
#include "ace/Svc_Handler.h"
#include "ace/Message_Block.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

class OASIS_WEBSOCK_ACCEPTOR_CONNECTOR_Export ACE_Websock_Svc_Handler
  : public ACE_Svc_Handler<ACE_Websock_Stream, ACE_MT_SYNCH>
{
public:
  /// constructor
  ACE_Websock_Svc_Handler (void);

  /// destructor
  ~ACE_Websock_Svc_Handler (void);

  /// receive data on listening port
  int handle_input (ACE_HANDLE fd = ACE_INVALID_HANDLE);

protected:
  /// handle the web input
  virtual int handle_web_input (ACE_Message_Block *message);

private:
  /// head of singly linked list of frames in a continuous message
  ACE_Message_Block *head_;

  /// current frame in a message
  ACE_Message_Block *curr_;
};


ACE_END_VERSIONED_NAMESPACE_DECL

#include "ace/post.h"
#endif
