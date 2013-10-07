// $Id$

#include "NetworkProbeImpl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{
  namespace System
  {
    namespace Network
    {

      // 
      // NetworkProbeImpl
      // 
      NetworkProbeImpl::NetworkProbeImpl (void) 
      {
         this->uuid_ = this->metadata ().uuid_;
      }

      // 
      // NetworkProbeImpl::__metadata__
      // 
      const ::OASIS::System::Network::NetworkProbe_Metadata NetworkProbeImpl::__metadata__ =
      ::OASIS::System::Network::NetworkProbe_Metadata ();


      // 
      // NetworkProbeImpl::metadata
      // 
      const ::OASIS::System::Network::NetworkProbe_Metadata & NetworkProbeImpl::metadata (void) const 
      {
        return ::OASIS::System::Network::NetworkProbeImpl::__metadata__;
      }

      // 
      // ~NetworkProbeImpl
      // 
      NetworkProbeImpl::~NetworkProbeImpl (void) 
      {
      }

      // 
      // package_data
      // 
      int NetworkProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
      {
        if (0 != ::OASIS::Software_Probe_Impl::package_data (p))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                            -1);
        if (!(p.data_stream () << this->nic_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package nic\n")),
                            -1);

        if (!(p.data_stream () << this->recv_bytes_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package recv_bytes\n")),
                            -1);

        if (!(p.data_stream () << this->recv_packets_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package recv_packets\n")),
                            -1);

        if (!(p.data_stream () << this->recv_errors_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package recv_errors\n")),
                            -1);

        if (!(p.data_stream () << this->recv_drop_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package recv_drop\n")),
                            -1);

        if (!(p.data_stream () << this->recv_multicast_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package recv_multicast\n")),
                            -1);

        if (!(p.data_stream () << this->sent_bytes_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package sent_bytes\n")),
                            -1);

        if (!(p.data_stream () << this->sent_packets_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package sent_packets\n")),
                            -1);

        if (!(p.data_stream () << this->sent_errors_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package sent_errors\n")),
                            -1);

        if (!(p.data_stream () << this->sent_drop_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package sent_drop\n")),
                            -1);

        return p.data_stream ().good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void NetworkProbeImpl::dump (std::ostream & output) 
      {
        ::OASIS::Software_Probe_Impl::dump (output);
        output << "  nic: " << this->nic () << std::endl;
        output << "  recv_bytes: " << this->recv_bytes () << std::endl;
        output << "  recv_packets: " << this->recv_packets () << std::endl;
        output << "  recv_errors: " << this->recv_errors () << std::endl;
        output << "  recv_drop: " << this->recv_drop () << std::endl;
        output << "  recv_multicast: " << this->recv_multicast () << std::endl;
        output << "  sent_bytes: " << this->sent_bytes () << std::endl;
        output << "  sent_packets: " << this->sent_packets () << std::endl;
        output << "  sent_errors: " << this->sent_errors () << std::endl;
        output << "  sent_drop: " << this->sent_drop () << std::endl;
      }

      // 
      // nic
      // 
      void NetworkProbeImpl::nic (const ACE_CString & nic)
      {
        this->nic_ = nic;
      }

      // 
      // nic
      // 
      const ACE_CString & NetworkProbeImpl::nic (void) const
      {
        return this->nic_;
      }

      // 
      // recv_bytes
      // 
      void NetworkProbeImpl::recv_bytes (ACE_UINT64 recv_bytes)
      {
        this->recv_bytes_ = recv_bytes;
      }

      // 
      // recv_bytes
      // 
      ACE_UINT64 NetworkProbeImpl::recv_bytes (void) const
      {
        return this->recv_bytes_;
      }

      // 
      // recv_packets
      // 
      void NetworkProbeImpl::recv_packets (ACE_UINT64 recv_packets)
      {
        this->recv_packets_ = recv_packets;
      }

      // 
      // recv_packets
      // 
      ACE_UINT64 NetworkProbeImpl::recv_packets (void) const
      {
        return this->recv_packets_;
      }

      // 
      // recv_errors
      // 
      void NetworkProbeImpl::recv_errors (ACE_UINT64 recv_errors)
      {
        this->recv_errors_ = recv_errors;
      }

      // 
      // recv_errors
      // 
      ACE_UINT64 NetworkProbeImpl::recv_errors (void) const
      {
        return this->recv_errors_;
      }

      // 
      // recv_drop
      // 
      void NetworkProbeImpl::recv_drop (ACE_UINT64 recv_drop)
      {
        this->recv_drop_ = recv_drop;
      }

      // 
      // recv_drop
      // 
      ACE_UINT64 NetworkProbeImpl::recv_drop (void) const
      {
        return this->recv_drop_;
      }

      // 
      // recv_multicast
      // 
      void NetworkProbeImpl::recv_multicast (ACE_UINT64 recv_multicast)
      {
        this->recv_multicast_ = recv_multicast;
      }

      // 
      // recv_multicast
      // 
      ACE_UINT64 NetworkProbeImpl::recv_multicast (void) const
      {
        return this->recv_multicast_;
      }

      // 
      // sent_bytes
      // 
      void NetworkProbeImpl::sent_bytes (ACE_UINT64 sent_bytes)
      {
        this->sent_bytes_ = sent_bytes;
      }

      // 
      // sent_bytes
      // 
      ACE_UINT64 NetworkProbeImpl::sent_bytes (void) const
      {
        return this->sent_bytes_;
      }

      // 
      // sent_packets
      // 
      void NetworkProbeImpl::sent_packets (ACE_UINT64 sent_packets)
      {
        this->sent_packets_ = sent_packets;
      }

      // 
      // sent_packets
      // 
      ACE_UINT64 NetworkProbeImpl::sent_packets (void) const
      {
        return this->sent_packets_;
      }

      // 
      // sent_errors
      // 
      void NetworkProbeImpl::sent_errors (ACE_UINT64 sent_errors)
      {
        this->sent_errors_ = sent_errors;
      }

      // 
      // sent_errors
      // 
      ACE_UINT64 NetworkProbeImpl::sent_errors (void) const
      {
        return this->sent_errors_;
      }

      // 
      // sent_drop
      // 
      void NetworkProbeImpl::sent_drop (ACE_UINT64 sent_drop)
      {
        this->sent_drop_ = sent_drop;
      }

      // 
      // sent_drop
      // 
      ACE_UINT64 NetworkProbeImpl::sent_drop (void) const
      {
        return this->sent_drop_;
      }


      // 
      // LinuxNetworkProbeImpl
      // 
      LinuxNetworkProbeImpl::LinuxNetworkProbeImpl (void) 
      {
         this->uuid_ = this->metadata ().uuid_;
      }

      // 
      // LinuxNetworkProbeImpl::__metadata__
      // 
      const ::OASIS::System::Network::LinuxNetworkProbe_Metadata LinuxNetworkProbeImpl::__metadata__ =
      ::OASIS::System::Network::LinuxNetworkProbe_Metadata ();


      // 
      // LinuxNetworkProbeImpl::metadata
      // 
      const ::OASIS::System::Network::LinuxNetworkProbe_Metadata & LinuxNetworkProbeImpl::metadata (void) const 
      {
        return ::OASIS::System::Network::LinuxNetworkProbeImpl::__metadata__;
      }

      // 
      // ~LinuxNetworkProbeImpl
      // 
      LinuxNetworkProbeImpl::~LinuxNetworkProbeImpl (void) 
      {
      }

      // 
      // package_data
      // 
      int LinuxNetworkProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
      {
        if (0 != ::OASIS::System::Network::NetworkProbeImpl::package_data (p))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                            -1);
        if (!(p.data_stream () << this->recv_compressed_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package recv_compressed\n")),
                            -1);

        if (!(p.data_stream () << this->recv_fifo_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package recv_fifo\n")),
                            -1);

        if (!(p.data_stream () << this->recv_frames_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package recv_frames\n")),
                            -1);

        if (!(p.data_stream () << this->sent_compressed_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package sent_compressed\n")),
                            -1);

        if (!(p.data_stream () << this->sent_fifo_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package sent_fifo\n")),
                            -1);

        if (!(p.data_stream () << this->sent_collision_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package sent_collision\n")),
                            -1);

        if (!(p.data_stream () << this->sent_carrier_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package sent_carrier\n")),
                            -1);

        return p.data_stream ().good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void LinuxNetworkProbeImpl::dump (std::ostream & output) 
      {
        ::OASIS::System::Network::NetworkProbeImpl::dump (output);
        output << "  recv_compressed: " << this->recv_compressed () << std::endl;
        output << "  recv_fifo: " << this->recv_fifo () << std::endl;
        output << "  recv_frames: " << this->recv_frames () << std::endl;
        output << "  sent_compressed: " << this->sent_compressed () << std::endl;
        output << "  sent_fifo: " << this->sent_fifo () << std::endl;
        output << "  sent_collision: " << this->sent_collision () << std::endl;
        output << "  sent_carrier: " << this->sent_carrier () << std::endl;
      }

      // 
      // recv_compressed
      // 
      void LinuxNetworkProbeImpl::recv_compressed (ACE_UINT64 recv_compressed)
      {
        this->recv_compressed_ = recv_compressed;
      }

      // 
      // recv_compressed
      // 
      ACE_UINT64 LinuxNetworkProbeImpl::recv_compressed (void) const
      {
        return this->recv_compressed_;
      }

      // 
      // recv_fifo
      // 
      void LinuxNetworkProbeImpl::recv_fifo (ACE_UINT64 recv_fifo)
      {
        this->recv_fifo_ = recv_fifo;
      }

      // 
      // recv_fifo
      // 
      ACE_UINT64 LinuxNetworkProbeImpl::recv_fifo (void) const
      {
        return this->recv_fifo_;
      }

      // 
      // recv_frames
      // 
      void LinuxNetworkProbeImpl::recv_frames (ACE_UINT64 recv_frames)
      {
        this->recv_frames_ = recv_frames;
      }

      // 
      // recv_frames
      // 
      ACE_UINT64 LinuxNetworkProbeImpl::recv_frames (void) const
      {
        return this->recv_frames_;
      }

      // 
      // sent_compressed
      // 
      void LinuxNetworkProbeImpl::sent_compressed (ACE_UINT64 sent_compressed)
      {
        this->sent_compressed_ = sent_compressed;
      }

      // 
      // sent_compressed
      // 
      ACE_UINT64 LinuxNetworkProbeImpl::sent_compressed (void) const
      {
        return this->sent_compressed_;
      }

      // 
      // sent_fifo
      // 
      void LinuxNetworkProbeImpl::sent_fifo (ACE_UINT64 sent_fifo)
      {
        this->sent_fifo_ = sent_fifo;
      }

      // 
      // sent_fifo
      // 
      ACE_UINT64 LinuxNetworkProbeImpl::sent_fifo (void) const
      {
        return this->sent_fifo_;
      }

      // 
      // sent_collision
      // 
      void LinuxNetworkProbeImpl::sent_collision (ACE_UINT64 sent_collision)
      {
        this->sent_collision_ = sent_collision;
      }

      // 
      // sent_collision
      // 
      ACE_UINT64 LinuxNetworkProbeImpl::sent_collision (void) const
      {
        return this->sent_collision_;
      }

      // 
      // sent_carrier
      // 
      void LinuxNetworkProbeImpl::sent_carrier (ACE_UINT64 sent_carrier)
      {
        this->sent_carrier_ = sent_carrier;
      }

      // 
      // sent_carrier
      // 
      ACE_UINT64 LinuxNetworkProbeImpl::sent_carrier (void) const
      {
        return this->sent_carrier_;
      }


      // 
      // WindowsNetworkProbeImpl
      // 
      WindowsNetworkProbeImpl::WindowsNetworkProbeImpl (void) 
      {
         this->uuid_ = this->metadata ().uuid_;
      }

      // 
      // WindowsNetworkProbeImpl::__metadata__
      // 
      const ::OASIS::System::Network::WindowsNetworkProbe_Metadata WindowsNetworkProbeImpl::__metadata__ =
      ::OASIS::System::Network::WindowsNetworkProbe_Metadata ();


      // 
      // WindowsNetworkProbeImpl::metadata
      // 
      const ::OASIS::System::Network::WindowsNetworkProbe_Metadata & WindowsNetworkProbeImpl::metadata (void) const 
      {
        return ::OASIS::System::Network::WindowsNetworkProbeImpl::__metadata__;
      }

      // 
      // ~WindowsNetworkProbeImpl
      // 
      WindowsNetworkProbeImpl::~WindowsNetworkProbeImpl (void) 
      {
      }

      // 
      // package_data
      // 
      int WindowsNetworkProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
      {
        if (0 != ::OASIS::System::Network::NetworkProbeImpl::package_data (p))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                            -1);
        if (!(p.data_stream () << this->recv_unknown_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package recv_unknown\n")),
                            -1);

        if (!(p.data_stream () << this->outbound_queue_length_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package outbound_queue_length\n")),
                            -1);

        return p.data_stream ().good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void WindowsNetworkProbeImpl::dump (std::ostream & output) 
      {
        ::OASIS::System::Network::NetworkProbeImpl::dump (output);
        output << "  recv_unknown: " << this->recv_unknown () << std::endl;
        output << "  outbound_queue_length: " << this->outbound_queue_length () << std::endl;
      }

      // 
      // recv_unknown
      // 
      void WindowsNetworkProbeImpl::recv_unknown (ACE_UINT64 recv_unknown)
      {
        this->recv_unknown_ = recv_unknown;
      }

      // 
      // recv_unknown
      // 
      ACE_UINT64 WindowsNetworkProbeImpl::recv_unknown (void) const
      {
        return this->recv_unknown_;
      }

      // 
      // outbound_queue_length
      // 
      void WindowsNetworkProbeImpl::outbound_queue_length (ACE_UINT64 outbound_queue_length)
      {
        this->outbound_queue_length_ = outbound_queue_length;
      }

      // 
      // outbound_queue_length
      // 
      ACE_UINT64 WindowsNetworkProbeImpl::outbound_queue_length (void) const
      {
        return this->outbound_queue_length_;
      }
    }
  }
}

