// -*- C++ -*-

//=============================================================================
/**
 * @file        Websock_Stream.h
 *
 * $Id: Websock_Stream.h 2230 2013-01-24 14:47:29Z dfeiock $
 *
 * @author      Darshan G. Puranik<dpuranik@iupui.edu>
 */
//=============================================================================

#ifndef ACE_WEBSOCK_STREAM_H
#define ACE_WEBSOCK_STREAM_H
#include "ace/pre.h"

#include "ace/SOCK_Stream.h"

#if !defined(ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/INET_Addr.h"
#include "Websock_Frame.h"
#include "ace/Message_Block.h"

#include "Websock_Acceptor_Connector_export.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
*@class ACE_Websock_Stream
*
*This adds additional wrapper methods atop the ACE_SOCK_Stream
*class.
*
*/
class OASIS_WEBSOCK_ACCEPTOR_CONNECTOR_Export ACE_Websock_Stream
  : public ACE_SOCK_Stream
{
public:
  /// Enumeration for different opcode
  enum opcode
  {
    continuation_frame  = 0,
    text_frame          = 1,
    binary_frame        = 2,
    close_frame         = 8,
    ping_frame          = 9,
    pong_frame          = 10
  };


  // Initialization and termination methods.
  /// Constructor
  ACE_Websock_Stream (void);

  /// Constructor (sets the underlying ACE_HANDLE with @a h).
  ACE_Websock_Stream (ACE_HANDLE h);

  /// Destructor.
  ~ACE_Websock_Stream (void);

  /** @name Counted send/receive methods
  *
  * The counted send/receive methods attempt to transfer a specified number
  * of bytes even if they must block and retry the operation in order to
  * transfer the entire amount. The time spent blocking for the entire
  * transfer can be limited by a specified ACE_Time_Value object which is
  * a relative time (i.e., a fixed amount of time, not an absolute time
  * of day). These methods return the count of transferred bytes, or -1
  * if an error occurs or the operation times out before the entire requested
  * amount of data has been transferred. In error or timeout situations it's
  * possible that some data was transferred before the error
  * or timeout. The @c bytes_transferred parameter is used to obtain the
  * count of bytes transferred before the error or timeout occurred. If the
  * total specified number of bytes is transferred without error, the
  * method return value should equal the value of @c bytes_transferred.
  *
  * @param buf      The buffer to write from or receive into.
  * @param iov      An I/O vector containing a specified number of
  *                 count/pointer pairs directing the data to be transferred.
  * @param iovcnt   The number of I/O vectors to be used from @a iov.
  * @param len      The number of bytes to transfer.
  * @param flags    Flags that will be passed through to the @c recv()
  *                 system call.
  * @param timeout  Indicates how long to blocking trying to transfer data.
  *                 If no timeout is supplied (timeout == 0) the method will
  *                 wait indefinitely or until an error occurs for the
  *                 specified number of bytes to be transferred.
  *                 To avoid any waiting, specify a timeout value with
  *                 0 seconds. Note that the timeout period restarts on
  *                 each retried operation issued; therefore, an operation
  *                 that requires multiples retries may take longer than the
  *                 specified timeout to complete.
  * @param bytes_transferred If non-0, points to a location which receives
  *                 the total number of bytes transferred before the method
  *                 returns, even if it's less than the number requested.
  *
  * @retval      len, the complete number of bytes transferred.
  * @retval      0  EOF, i.e., the peer closed the connection.
  * @retval      -1 an error occurred before the entire amount was
  *                 transferred. Check @c errno for more information.
  *                 If the @a timeout period is reached, errno is ETIME.
  *
  * On partial transfers, i.e., if any data is transferred before
  * timeout/error/EOF, *@a bytes_transferred will contain the number of
  * bytes transferred.
  */
  //@{
  /// Try to recv exactly @a len bytes into @a buf from the connected socket.
  ssize_t recv_n (void *buf,
                  ACE_INT64 len,
                  const ACE_Time_Value *timeout = 0,
                  ACE_INT64 *bytes_transferred = 0) const;

  /// Try to send exactly @a len bytes from @a buf to the connected socket.
  ssize_t send_n (const void *buf,
                  size_t len,
                  const ACE_Time_Value *timeout = 0,
                  size_t *bytes_transferred = 0) const;

  /// Try to send exactly @a len bytes from @a buf to the connected socket.
  ssize_t send_n (const char *buf,
                  size_t len,
                  opcode frame_opcode,
                  bool masking = false,
                  const ACE_Time_Value *timeout = 0,
                  size_t *bytes_transferred = 0) const;

  /// Send all the message blocks chained through their @c next and
  /// @c cont pointers.  This call uses the underlying OS gather-write
  /// operation to reduce the domain-crossing penalty.
  ssize_t send_n (const ACE_Message_Block *message_block,
                  opcode frame_opcode,
                  const ACE_Time_Value *timeout = 0,
                  size_t *bytes_transferred = 0) const;

  /// Send an @c iovec of size @a iovcnt to the connected socket.
  ssize_t sendv_n (const iovec iov[],
                   int iovcnt,
                   opcode frame_opcode,
                   const ACE_Time_Value *timeout = 0,
                   size_t *bytes_transferred = 0) const;

  //@}

  /// intialize the stream
  int init (void);

  // = Meta-type info
  typedef ACE_INET_Addr PEER_ADDR;

  /// Dump the state of an object.
  void dump (void) const;

  /// Declare the dynamic allocation hooks
  ACE_ALLOC_HOOK_DECLARE;

  /// get web message length
  int get_web_message_length (void);

  /// receive web message for further processing
  int recv_web_message (ACE_Message_Block *message);

protected:
  /// handle websocket protocol pong frame
  virtual int handle_pong_frame (void);

  /// handle websocket protocol ping frame
  virtual int handle_ping_frame (void);

  /// handle websocket protocol close frame
  virtual int handle_close_frame (void);

private:
  /// encode payload if user want masking
  void encode_data (char *masks,
                    char *buf,
                    size_t len)const;

  /// websocket frame wrapper
  ACE_Websock_Frame frame_;

  /// convert binary to INT64
  ACE_INT64 binary_to_int64 (char *buffer, unsigned short num_of_bits);
};

ACE_END_VERSIONED_NAMESPACE_DECL

#if defined (__ACE_INLINE__)
#include "Websock_Stream.inl"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /* ACE_WEBSOCK_STREAM_H */
