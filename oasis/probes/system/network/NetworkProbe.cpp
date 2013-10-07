// $Id$

#include "NetworkProbe.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{
  namespace System
  {
    namespace Network
    {

      // 
      // NetworkProbe::__metadata__
      // 
      const NetworkProbe::METADATA_TYPE NetworkProbe::__metadata__;

      // 
      // NetworkProbe::metadata
      // 
      const NetworkProbe::METADATA_TYPE & NetworkProbe::metadata (void) const 
      {
        return ::OASIS::System::Network::NetworkProbe::__metadata__;
      }

      // 
      // NetworkProbe
      // 
      NetworkProbe::NetworkProbe (void) 
      {
      }

      // 
      // ~NetworkProbe
      // 
      NetworkProbe::~NetworkProbe (void) 
      {
      }

      // 
      // recall
      // 
      int NetworkProbe::
      recall (const char * data, size_t length, int byte_order) 
      {
        ::OASIS::Software_Probe_Data_Preparer prep (data, length);
        ACE_InputCDR input (prep.message_block (), byte_order);
        return ::OASIS::System::Network::NetworkProbe::recall (input);
      }


      // 
      // recall
      // 
      int NetworkProbe::recall (ACE_InputCDR & in) 
      {
        if (0 != ::OASIS::Software_Probe::recall (in))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to recall ")
                             ACE_TEXT ("::OASIS::Software_Probe data\n")),
                            -1);

        if (!(in >> this->nic_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage nic\n")),
                            -1);

        if (!(in >> this->recv_bytes_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage recv_bytes\n")),
                            -1);

        if (!(in >> this->recv_packets_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage recv_packets\n")),
                            -1);

        if (!(in >> this->recv_errors_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage recv_errors\n")),
                            -1);

        if (!(in >> this->recv_drop_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage recv_drop\n")),
                            -1);

        if (!(in >> this->recv_multicast_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage recv_multicast\n")),
                            -1);

        if (!(in >> this->sent_bytes_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage sent_bytes\n")),
                            -1);

        if (!(in >> this->sent_packets_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage sent_packets\n")),
                            -1);

        if (!(in >> this->sent_errors_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage sent_errors\n")),
                            -1);

        if (!(in >> this->sent_drop_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage sent_drop\n")),
                            -1);

        return in.good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void NetworkProbe::dump (std::ostream & output) 
      {
        ::OASIS::Software_Probe::dump (output);
        output << "  nic: " << this->nic_ << std::endl;
        output << "  recv_bytes: " << this->recv_bytes_ << std::endl;
        output << "  recv_packets: " << this->recv_packets_ << std::endl;
        output << "  recv_errors: " << this->recv_errors_ << std::endl;
        output << "  recv_drop: " << this->recv_drop_ << std::endl;
        output << "  recv_multicast: " << this->recv_multicast_ << std::endl;
        output << "  sent_bytes: " << this->sent_bytes_ << std::endl;
        output << "  sent_packets: " << this->sent_packets_ << std::endl;
        output << "  sent_errors: " << this->sent_errors_ << std::endl;
        output << "  sent_drop: " << this->sent_drop_ << std::endl;
      }

      // 
      // nic
      // 
      const ACE_CString & NetworkProbe::nic (void) const
      {
        return this->nic_;
      }

      // 
      // recv_bytes
      // 
      ACE_UINT64 NetworkProbe::recv_bytes (void) const
      {
        return this->recv_bytes_;
      }

      // 
      // recv_packets
      // 
      ACE_UINT64 NetworkProbe::recv_packets (void) const
      {
        return this->recv_packets_;
      }

      // 
      // recv_errors
      // 
      ACE_UINT64 NetworkProbe::recv_errors (void) const
      {
        return this->recv_errors_;
      }

      // 
      // recv_drop
      // 
      ACE_UINT64 NetworkProbe::recv_drop (void) const
      {
        return this->recv_drop_;
      }

      // 
      // recv_multicast
      // 
      ACE_UINT64 NetworkProbe::recv_multicast (void) const
      {
        return this->recv_multicast_;
      }

      // 
      // sent_bytes
      // 
      ACE_UINT64 NetworkProbe::sent_bytes (void) const
      {
        return this->sent_bytes_;
      }

      // 
      // sent_packets
      // 
      ACE_UINT64 NetworkProbe::sent_packets (void) const
      {
        return this->sent_packets_;
      }

      // 
      // sent_errors
      // 
      ACE_UINT64 NetworkProbe::sent_errors (void) const
      {
        return this->sent_errors_;
      }

      // 
      // sent_drop
      // 
      ACE_UINT64 NetworkProbe::sent_drop (void) const
      {
        return this->sent_drop_;
      }


      // 
      // LinuxNetworkProbe::__metadata__
      // 
      const LinuxNetworkProbe::METADATA_TYPE LinuxNetworkProbe::__metadata__;

      // 
      // LinuxNetworkProbe::metadata
      // 
      const LinuxNetworkProbe::METADATA_TYPE & LinuxNetworkProbe::metadata (void) const 
      {
        return ::OASIS::System::Network::LinuxNetworkProbe::__metadata__;
      }

      // 
      // LinuxNetworkProbe
      // 
      LinuxNetworkProbe::LinuxNetworkProbe (void) 
      {
      }

      // 
      // ~LinuxNetworkProbe
      // 
      LinuxNetworkProbe::~LinuxNetworkProbe (void) 
      {
      }

      // 
      // recall
      // 
      int LinuxNetworkProbe::
      recall (const char * data, size_t length, int byte_order) 
      {
        ::OASIS::Software_Probe_Data_Preparer prep (data, length);
        ACE_InputCDR input (prep.message_block (), byte_order);
        return ::OASIS::System::Network::LinuxNetworkProbe::recall (input);
      }


      // 
      // recall
      // 
      int LinuxNetworkProbe::recall (ACE_InputCDR & in) 
      {
        if (0 != ::OASIS::System::Network::NetworkProbe::recall (in))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to recall ")
                             ACE_TEXT ("::OASIS::System::Network::NetworkProbe data\n")),
                            -1);

        if (!(in >> this->recv_compressed_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage recv_compressed\n")),
                            -1);

        if (!(in >> this->recv_fifo_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage recv_fifo\n")),
                            -1);

        if (!(in >> this->recv_frames_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage recv_frames\n")),
                            -1);

        if (!(in >> this->sent_compressed_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage sent_compressed\n")),
                            -1);

        if (!(in >> this->sent_fifo_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage sent_fifo\n")),
                            -1);

        if (!(in >> this->sent_collision_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage sent_collision\n")),
                            -1);

        if (!(in >> this->sent_carrier_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage sent_carrier\n")),
                            -1);

        return in.good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void LinuxNetworkProbe::dump (std::ostream & output) 
      {
        ::OASIS::System::Network::NetworkProbe::dump (output);
        output << "  recv_compressed: " << this->recv_compressed_ << std::endl;
        output << "  recv_fifo: " << this->recv_fifo_ << std::endl;
        output << "  recv_frames: " << this->recv_frames_ << std::endl;
        output << "  sent_compressed: " << this->sent_compressed_ << std::endl;
        output << "  sent_fifo: " << this->sent_fifo_ << std::endl;
        output << "  sent_collision: " << this->sent_collision_ << std::endl;
        output << "  sent_carrier: " << this->sent_carrier_ << std::endl;
      }

      // 
      // recv_compressed
      // 
      ACE_UINT64 LinuxNetworkProbe::recv_compressed (void) const
      {
        return this->recv_compressed_;
      }

      // 
      // recv_fifo
      // 
      ACE_UINT64 LinuxNetworkProbe::recv_fifo (void) const
      {
        return this->recv_fifo_;
      }

      // 
      // recv_frames
      // 
      ACE_UINT64 LinuxNetworkProbe::recv_frames (void) const
      {
        return this->recv_frames_;
      }

      // 
      // sent_compressed
      // 
      ACE_UINT64 LinuxNetworkProbe::sent_compressed (void) const
      {
        return this->sent_compressed_;
      }

      // 
      // sent_fifo
      // 
      ACE_UINT64 LinuxNetworkProbe::sent_fifo (void) const
      {
        return this->sent_fifo_;
      }

      // 
      // sent_collision
      // 
      ACE_UINT64 LinuxNetworkProbe::sent_collision (void) const
      {
        return this->sent_collision_;
      }

      // 
      // sent_carrier
      // 
      ACE_UINT64 LinuxNetworkProbe::sent_carrier (void) const
      {
        return this->sent_carrier_;
      }


      // 
      // WindowsNetworkProbe::__metadata__
      // 
      const WindowsNetworkProbe::METADATA_TYPE WindowsNetworkProbe::__metadata__;

      // 
      // WindowsNetworkProbe::metadata
      // 
      const WindowsNetworkProbe::METADATA_TYPE & WindowsNetworkProbe::metadata (void) const 
      {
        return ::OASIS::System::Network::WindowsNetworkProbe::__metadata__;
      }

      // 
      // WindowsNetworkProbe
      // 
      WindowsNetworkProbe::WindowsNetworkProbe (void) 
      {
      }

      // 
      // ~WindowsNetworkProbe
      // 
      WindowsNetworkProbe::~WindowsNetworkProbe (void) 
      {
      }

      // 
      // recall
      // 
      int WindowsNetworkProbe::
      recall (const char * data, size_t length, int byte_order) 
      {
        ::OASIS::Software_Probe_Data_Preparer prep (data, length);
        ACE_InputCDR input (prep.message_block (), byte_order);
        return ::OASIS::System::Network::WindowsNetworkProbe::recall (input);
      }


      // 
      // recall
      // 
      int WindowsNetworkProbe::recall (ACE_InputCDR & in) 
      {
        if (0 != ::OASIS::System::Network::NetworkProbe::recall (in))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to recall ")
                             ACE_TEXT ("::OASIS::System::Network::NetworkProbe data\n")),
                            -1);

        if (!(in >> this->recv_unknown_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage recv_unknown\n")),
                            -1);

        if (!(in >> this->outbound_queue_length_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage outbound_queue_length\n")),
                            -1);

        return in.good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void WindowsNetworkProbe::dump (std::ostream & output) 
      {
        ::OASIS::System::Network::NetworkProbe::dump (output);
        output << "  recv_unknown: " << this->recv_unknown_ << std::endl;
        output << "  outbound_queue_length: " << this->outbound_queue_length_ << std::endl;
      }

      // 
      // recv_unknown
      // 
      ACE_UINT64 WindowsNetworkProbe::recv_unknown (void) const
      {
        return this->recv_unknown_;
      }

      // 
      // outbound_queue_length
      // 
      ACE_UINT64 WindowsNetworkProbe::outbound_queue_length (void) const
      {
        return this->outbound_queue_length_;
      }
    }
  }
}

