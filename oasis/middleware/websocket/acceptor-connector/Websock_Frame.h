/* -*- C++ -*- */

//=============================================================================
/**
*  @file    Websock_Frame.h
*
*  $Id $
*
*  @author Darshan G. Puranik<dpuranik@iupui.edu>
*/
//=============================================================================

#ifndef ACE_WEBSOCK_FRAME_H
#define ACE_WEBSOCK_FRAME_H
#include /**/ "ace/pre.h"

#include "ace/Basic_Types.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

// Forward declarations.
class ACE_Message_Block;

/**
* @class ACE_Websock_Frame
*
* @brief Defines a frame defined by Websocket protocol to send and receive data.
*        This is the base class for all different versions of websocket frames.
*/
class ACE_Websock_Frame
{
public:
  /// This is true constant part of Websocket header
  union fixed_header
  {
    struct
    {
      unsigned char opcode: 4;
      unsigned char rsv3: 1;
      unsigned char rsv2: 1;
      unsigned char rsv1: 1;
      unsigned char fin: 1;
      unsigned char length: 7;
      unsigned char mask: 1;
    }bitmask;
    unsigned short value;
  }header_;

  // = Initialization and termination methods.
  /// Default constructor.
  ACE_Websock_Frame (void);

  /// Default dtor.
  ~ACE_Websock_Frame (void);

  /// get the payload
  virtual char* payload (void);

  /// set the payload
  virtual void payload (char *payload);

  /// get payload length
  virtual ACE_INT64 payload_length (void) const;

  /// get payload length
  virtual void payload_length (ACE_INT64 len);

  /// get websocket frame to send over wire
  char* frame (void);

  /// encode/decode the payload using mask
  void encode_or_decode_payload (char *buf) const;

  /// set the mask
  void masks (char masks[]);

  /// get the mask
  char* masks (void);

private:
  /// Payload of the frame.
  char *payload_;

  /// length of payload
  ACE_INT64 payload_length_;

  /// masks for masking payload data
  char masks_[4];
};

ACE_END_VERSIONED_NAMESPACE_DECL



#include /**/ "ace/post.h"
#endif /* ACE_WEBSOCK_FRAME_H */
