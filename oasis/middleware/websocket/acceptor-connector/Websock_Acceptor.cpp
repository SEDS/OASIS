// $Id: Websock_Acceptor.cpp 2230 2013-01-24 14:47:29Z dfeiock $

#include "Websock_Acceptor.h"

#include "ace/Log_Msg.h"
#include "ace/OS_Errno.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_sys_socket.h"
#include "ace/os_include/os_fcntl.h"

#include "openssl/sha.h"
#include "openssl/hmac.h"
#include "openssl/evp.h"
#include "openssl/bio.h"
#include "openssl/buffer.h"

#include <iostream>

#define SEC_WEB_KEY_LENGTH        24
#define CLIENT_HANDSHAKE_LENGTH   185

#if !defined (__ACE_INLINE__)
#include "Websock_Acceptor.inl"
#endif /* __ACE_INLINE__ */

#if !defined (ACE_HAS_WINCE)
#include "ace/OS_QoS.h"
#endif  // ACE_HAS_WINCE



ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_ALLOC_HOOK_DEFINE(ACE_Websock_Acceptor)


// General purpose routine for accepting new connections.

int
ACE_Websock_Acceptor::accept (ACE_Websock_Stream &new_stream,
                              ACE_Addr *remote_addr,
                              ACE_Time_Value *timeout,
                              bool restart,
                              bool reset_new_handle) const
{
  ACE_TRACE ("ACE_Websock_Acceptor::accept");

  ACE_SOCK_Stream stream;
  ACE_SOCK_Acceptor::accept (stream,
                             remote_addr,
                             timeout,
                             restart,
                             reset_new_handle);

  //Here ACE_SOCK_Acceptor completes the normal TCP connection but we
  //need websocket connection so we have to receive and send handshake
  //to upgrade the TCP connection to Websocket connection.
  //After successful handshke,we can commmunicate over websocket connection.
  if (0 !=this->establish_websocket_connection (stream))
    return -1;

  new_stream.set_handle (stream.get_handle ());
  stream.set_handle (ACE_INVALID_HANDLE);

  return 1;
}

#if !defined (ACE_HAS_WINCE)
int
ACE_Websock_Acceptor::accept (ACE_Websock_Stream &new_stream,
                              ACE_Accept_QoS_Params qos_params,
                              ACE_Addr *remote_addr,
                              ACE_Time_Value *timeout,
                              bool restart,
                              bool reset_new_handle) const
{
  ACE_TRACE ("ACE_Websock_Acceptor::accept");

  ACE_SOCK_Stream stream;
  ACE_SOCK_Acceptor::accept(stream,
                            qos_params,
                            remote_addr,
                            timeout,
                            restart,
                            reset_new_handle);

  //Here ACE_SOCK_Acceptor completes the normal TCP connection but we
  //need websocket connection so we have to receive and send handshake
  //to upgrade the TCP connection to Websocket connection.
  //After successful handshke,we can commmunicate over websocket connection.
  //server.
  if (0 !=this->establish_websocket_connection (stream))
    return -1;

  new_stream.set_handle (stream.get_handle ());
  stream.set_handle (ACE_INVALID_HANDLE);

  return 0;
}
#endif  // ACE_HAS_WINCE

void
ACE_Websock_Acceptor::dump (void) const
{
#if defined (ACE_HAS_DUMP)
  ACE_TRACE ("ACE_Websock_Acceptor::dump");
#endif /* ACE_HAS_DUMP */
}

int ACE_Websock_Acceptor::
establish_websocket_connection(ACE_SOCK_Stream &stream) const
{
  char buf[CLIENT_HANDSHAKE_LENGTH];
  ACE_CString client_handshake;
  ssize_t bytes_received = -1;

  //Read the handshake from client, there can be numerous
  //errors when starting to read from the socket for some reason.
  do
  {
    bytes_received = stream.recv(buf,sizeof(buf));
    if (bytes_received > 0)
      client_handshake.append(buf, bytes_received);
  }
  while (bytes_received > 0 || client_handshake.length() == 0);

  //Construct and Send handshake to client
  ACE_CString handshake;
  handshake+="HTTP/1.1 101 Switching Protocols\r\n";
  handshake+="Upgrade: websocket\r\n";
  handshake+="Connection: Upgrade\r\n";
  handshake+="Sec-WebSocket-Accept: ";
  handshake+=this->get_server_response_key(client_handshake);
  handshake+="\r\n";
  handshake+="\r\n";

  ssize_t bytes_sent = stream.send_n (handshake.c_str(),handshake.length());

  if (bytes_sent != handshake.length ())
    return -1;

  return 0;
}

ACE_CString
ACE_Websock_Acceptor::get_server_response_key (ACE_CString client_handshake) const
{
  int start_secwebkey = client_handshake.find("Sec-WebSocket-Key") +
                        strlen("Sec-WebSocket-Key")+ 2;

  ACE_CString secwebkey = client_handshake.substr(start_secwebkey,SEC_WEB_KEY_LENGTH);

  //Combining client webkey with GUID given in SPEC
  secwebkey +="258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

  //SHA1 encodign use OpenSSSL
  unsigned char key_for_base64_encoding[SHA_DIGEST_LENGTH];
  ::SHA1 ((const unsigned char *)secwebkey.c_str (),
          secwebkey.length(),
          key_for_base64_encoding);

  //Encode the string for base64 and return the string
  return this->base64 (key_for_base64_encoding, SHA_DIGEST_LENGTH);
}

char*
ACE_Websock_Acceptor::base64 (const unsigned char *input,
                              int length) const
{
  BIO *bmem, *b64;
  BUF_MEM *bptr;

  b64 = BIO_new(BIO_f_base64());
  bmem = BIO_new(BIO_s_mem());
  b64 = BIO_push(b64, bmem);
  BIO_write(b64, input, length);
  BIO_flush(b64);
  BIO_get_mem_ptr(b64, &bptr);

  char * buff = 0;
  ACE_NEW_RETURN (buff, char[bptr->length], 0);
  memcpy(buff, bptr->data, bptr->length-1);
  buff[bptr->length-2] = '=';
  buff[bptr->length-1] =0;
  BIO_free_all(b64);

  return buff;
}

ACE_END_VERSIONED_NAMESPACE_DECL