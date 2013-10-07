// $Id: driver.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "oasis/DataChannel/Latest_Local_Data_Channel.h"
#include "oasis/probes/system/network/NetworkProbe_Impl.h"
#include "oasis/probes/system/network/NetworkProbe.h"
#include <iostream>
//
// validate
//
bool validate (const ::OASIS::System::Network::NetworkProbeImpl & p1,
               const ::OASIS::System::Network::NetworkProbe & p2)
{
  if (p1.uuid () != p2.uuid ()
      || p1.timestamp () != p2.timestamp ()
      || p1.sequence_number () != p2.sequence_number ()
      || p1.state () != p2.state ()
      || p1.data_size () != p2.data_size ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled header is not equal\n")),
                       false);

  //// Validate the recalled data.
  if (p1.sent_bytes () != p2.sent_bytes ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled bytes_sent is not equal\n")),
                       false);

  //// Validate the recalled data.
  if (p1.recv_bytes () != p2.recv_bytes ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled bytes_received is not equal\n")),
                       false);

  return true;
}

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  // Register the software probe with the EINode.
  ::OASIS::System::Network::SystemNetworkProbe_Impl net_probe;

  // Set the software probe's local data channel.
  OASIS::Latest_Local_Data_Channel channel;
  net_probe.set_data_channel (&channel);

  // Init the probe
  //if (0 != net_probe.init ("--nic=eth0"))
  if (0 != net_probe.init ("--nic=\"Intel(R) PRO/1000 MT Network Connection\""))
    ACE_ERROR_RETURN ((LM_ERROR,
                      ACE_TEXT ("%T (%t) - %M - probe impl failed to init\n")),
                      -1);

  // Get the data and flush
  if (0 != net_probe.handle_collect_data ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - probe impl failed to collect data\n")),
                       -1);

  net_probe.flush ();

  // Recall the data received on the data channel.
  ::OASIS::System::Network::NetworkProbe dup_probe;

  if (0 != dup_probe.recall (channel.get_data (),
                             channel.get_data_length (),
                             ACE_CDR::BYTE_ORDER_NATIVE))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to recall data\n")),
                       -1);
  }

  if (!validate (net_probe, dup_probe))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to validate probe data\n")),
                       -1);

#if defined (_WIN32)
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("  nic = %s\n")
              ACE_TEXT ("  recv_bytes = %q\n")
              ACE_TEXT ("  recv_packets = %q\n")
              ACE_TEXT ("  recv_errors = %q\n")
              ACE_TEXT ("  recv_drop = %q\n")
              ACE_TEXT ("  recv_multicast = %q\n")
              ACE_TEXT ("  sent_bytes = %q\n")
              ACE_TEXT ("  sent_packets = %q\n")
              ACE_TEXT ("  sent_errors = %q\n")
              ACE_TEXT ("  sent_drop = %q\n")
              ACE_TEXT ("  recv_unknown = %q\n")
              ACE_TEXT ("  outbound_queue_length = %q\n"),
              net_probe.nic ().c_str (),
              net_probe.recv_bytes (),
              net_probe.recv_packets (),
              net_probe.recv_errors (),
              net_probe.recv_drop (),
              net_probe.recv_multicast (),
              net_probe.sent_bytes (),
              net_probe.sent_packets (),
              net_probe.sent_errors (),
              net_probe.sent_drop (),
              net_probe.recv_unknown (),
              net_probe.outbound_queue_length ()));
#else
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("  nic = %s\n")
              ACE_TEXT ("  recv_bytes = %q\n")
              ACE_TEXT ("  recv_packets = %q\n")
              ACE_TEXT ("  recv_errors = %q\n")
              ACE_TEXT ("  recv_drop = %q\n")
              ACE_TEXT ("  recv_multicast = %q\n")
              ACE_TEXT ("  sent_bytes = %q\n")
              ACE_TEXT ("  sent_packets = %q\n")
              ACE_TEXT ("  sent_errors = %q\n")
              ACE_TEXT ("  sent_drop = %q\n")
              ACE_TEXT ("  recv_compressed = %q\n")
              ACE_TEXT ("  recv_fifo = %q\n")
              ACE_TEXT ("  recv_frames = %q\n")
              ACE_TEXT ("  sent_compressed = %q\n")
              ACE_TEXT ("  sent_fifo = %q\n")
              ACE_TEXT ("  sent_collision = %q\n")
              ACE_TEXT ("  sent_carrier = %q\n"),
              net_probe.nic ().c_str (),
              net_probe.recv_bytes (),
              net_probe.recv_packets (),
              net_probe.recv_errors (),
              net_probe.recv_drop (),
              net_probe.recv_multicast (),
              net_probe.sent_bytes (),
              net_probe.sent_packets (),
              net_probe.sent_errors (),
              net_probe.sent_drop (),
              net_probe.recv_compressed (),
              net_probe.recv_fifo (),
              net_probe.recv_frames (),
              net_probe.sent_compressed (),
              net_probe.sent_fifo (),
              net_probe.sent_collision (),
              net_probe.sent_carrier ()));
#endif

  return 0;
}
