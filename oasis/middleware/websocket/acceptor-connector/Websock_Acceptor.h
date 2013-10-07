/* -*- C++ -*- */

//=============================================================================
/**
*  @file    Websock_Acceptor.h
*
*  $Id: Websock_Acceptor.h 2230 2013-01-24 14:47:29Z dfeiock $
*
*  @author Darshan G. Puranik<dpuranik@iupui.edu>
*/
//=============================================================================

#ifndef ACE_WEBSOCK_ACCEPTOR_H
#define ACE_WEBSOCK_ACCEPTOR_H
#include /**/ "ace/pre.h"

#include "ace/SString.h"
#include "ace/SOCK_Acceptor.h"
#include "Websock_Stream.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

class ACE_Time_Value;
class ACE_Accept_QoS_Params;

/**
* @class ACE_Websock_Acceptor
*
* @brief Defines a factory that creates new ACE_WEBSOCK_Streams passively.
*
* The ACE_Websock_Acceptor has its own "passive-mode" socket.
* This serves as a factory to create so-called "data-mode"
* sockets, which are what the ACE_Websock_Stream encapsulates.
* Therefore, by inheriting from ACE_SOCK indirectly,
* ACE_Websock_Acceptor gets its very own socket.
*/
class OASIS_WEBSOCK_ACCEPTOR_CONNECTOR_Export ACE_Websock_Acceptor :
  public ACE_SOCK_Acceptor
{
public:
  // = Initialization and termination methods.
  /// Default constructor.
  ACE_Websock_Acceptor (void);

  /// Default dtor.
  ~ACE_Websock_Acceptor (void);

  // = Passive connection <accept> methods.
  /**
   * Accept a new ACE_Websock_Stream connection.  A @a timeout of 0
   * means block forever, a @a timeout of {0, 0} means poll.  @a restart
   * == true means "restart if interrupted," i.e., if errno == EINTR.
   * Note that @a new_stream inherits the "blocking mode" of @c this
   * ACE_SOCK_Acceptor, i.e., if @c this acceptor factory is in
   * non-blocking mode, the @a new_stream will be in non-blocking mode
   * and vice versa.
   */
  int accept (ACE_Websock_Stream &new_stream,
              ACE_Addr *remote_addr = 0,
              ACE_Time_Value *timeout = 0,
              bool restart = true,
              bool reset_new_handle = false) const;

  #if !defined (ACE_HAS_WINCE)
  /**
   * Accept a new ACE_Websock_Stream connection using the QoS
   * information in @a qos_params.  A @a timeout of 0 means block
   * forever, a @a timeout of {0, 0} means poll.  @a restart == true means
   * "restart if interrupted," i.e., if errno == EINTR.  Note that
   * @a new_stream inherits the "blocking mode" of @c this
   * ACE_SOCK_Acceptor, i.e., if @c this acceptor factory is in
   * non-blocking mode, the @a new_stream will be in non-blocking mode
   * and vice versa.
   */
  int accept (ACE_Websock_Stream &new_stream,
              ACE_Accept_QoS_Params qos_params,
              ACE_Addr *remote_addr = 0,
              ACE_Time_Value *timeout = 0,
              bool restart = true,
              bool reset_new_handle = false) const;
#endif  // ACE_HAS_WINCE

  // = Meta-type info
  typedef ACE_INET_Addr PEER_ADDR;
  typedef ACE_Websock_Stream PEER_STREAM;

  /// Dump the state of an object.
  void dump (void) const;

  /// Declare the dynamic allocation hooks.
  ACE_ALLOC_HOOK_DECLARE;

protected:
  /// Perform operations that must occur before <ACE_OS::accept> is
  /// called.
  int shared_accept_start (ACE_Time_Value *timeout,
                           bool restart,
                           int &in_blocking_mode) const;

  /// Perform operations that must occur after <ACE_OS::accept> is
  /// called.
  int shared_accept_finish (ACE_Websock_Stream new_stream,
                            int in_blocking_mode,
                            bool reset_new_handle) const;

private:
  /// Establish websocket connection
  int establish_websocket_connection (ACE_SOCK_Stream &new_stream) const;

  /// Generate the key by performing SHA1 hashing on secured web
  /// key
  ACE_CString get_server_response_key (ACE_CString secwebkey) const;

  /// Encode the hash to base64
  char* base64 (const unsigned char *input,
                int length) const;
};

ACE_END_VERSIONED_NAMESPACE_DECL

#if defined (__ACE_INLINE__)
#include "Websock_Acceptor.inl"
#endif /* __ACE_INLINE__ */

#include /**/ "ace/post.h"
#endif /* ACE_WEBSOCK_ACCEPTOR_H */
