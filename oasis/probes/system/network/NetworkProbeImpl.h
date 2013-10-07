// -*- C++ -*-

//============================================================================
/**
 * @file        NetworkProbeImpl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _NETWORKPROBEIMPL_H_
#define _NETWORKPROBEIMPL_H_

#include "oasis/probes/Data_Types.h"
#include "NetworkProbe_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

#include "NetworkProbe_stub_export.h"

namespace OASIS
{
  namespace System
  {
    namespace Network
    {
      /**
       * @class NetworkProbeImpl
       */
      class OASIS_NETWORKPROBE_STUB_Export NetworkProbeImpl :
        public virtual ::OASIS::Software_Probe_Impl
      {
        public:
        /// The metadata for the software probe.
        static const ::OASIS::System::Network::NetworkProbe_Metadata __metadata__;

        /// Default constructor
        NetworkProbeImpl (void);

        /// Destructor
        virtual ~NetworkProbeImpl (void) = 0;

        /// Getter for the probe's metadata
        virtual const ::OASIS::System::Network::NetworkProbe_Metadata & metadata (void) const;

        /// Package the software probe's data.
        protected:
        virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


        public:
        /// Impl_Dump the software probe's data.
        virtual void dump (std::ostream & output);


        public:
        // Setter and getter methods for nic
        void nic (const ACE_CString & nic);
        const ACE_CString & nic (void) const;

        // Setter and getter methods for recv_bytes
        void recv_bytes (ACE_UINT64 recv_bytes);
        ACE_UINT64 recv_bytes (void) const;

        // Setter and getter methods for recv_packets
        void recv_packets (ACE_UINT64 recv_packets);
        ACE_UINT64 recv_packets (void) const;

        // Setter and getter methods for recv_errors
        void recv_errors (ACE_UINT64 recv_errors);
        ACE_UINT64 recv_errors (void) const;

        // Setter and getter methods for recv_drop
        void recv_drop (ACE_UINT64 recv_drop);
        ACE_UINT64 recv_drop (void) const;

        // Setter and getter methods for recv_multicast
        void recv_multicast (ACE_UINT64 recv_multicast);
        ACE_UINT64 recv_multicast (void) const;

        // Setter and getter methods for sent_bytes
        void sent_bytes (ACE_UINT64 sent_bytes);
        ACE_UINT64 sent_bytes (void) const;

        // Setter and getter methods for sent_packets
        void sent_packets (ACE_UINT64 sent_packets);
        ACE_UINT64 sent_packets (void) const;

        // Setter and getter methods for sent_errors
        void sent_errors (ACE_UINT64 sent_errors);
        ACE_UINT64 sent_errors (void) const;

        // Setter and getter methods for sent_drop
        void sent_drop (ACE_UINT64 sent_drop);
        ACE_UINT64 sent_drop (void) const;

        protected:
        ACE_CString nic_;

        ACE_UINT64 recv_bytes_;

        ACE_UINT64 recv_packets_;

        ACE_UINT64 recv_errors_;

        ACE_UINT64 recv_drop_;

        ACE_UINT64 recv_multicast_;

        ACE_UINT64 sent_bytes_;

        ACE_UINT64 sent_packets_;

        ACE_UINT64 sent_errors_;

        ACE_UINT64 sent_drop_;
      };

      /**
       * @class LinuxNetworkProbeImpl
       */
      class OASIS_NETWORKPROBE_STUB_Export LinuxNetworkProbeImpl :
        public ::OASIS::System::Network::NetworkProbeImpl
      {
        public:
        /// The metadata for the software probe.
        static const ::OASIS::System::Network::LinuxNetworkProbe_Metadata __metadata__;

        /// Default constructor
        LinuxNetworkProbeImpl (void);

        /// Destructor
        virtual ~LinuxNetworkProbeImpl (void);

        /// Getter for the probe's metadata
        virtual const ::OASIS::System::Network::LinuxNetworkProbe_Metadata & metadata (void) const;

        /// Package the software probe's data.
        protected:
        virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


        public:
        /// Impl_Dump the software probe's data.
        virtual void dump (std::ostream & output);


        public:
        // Setter and getter methods for recv_compressed
        void recv_compressed (ACE_UINT64 recv_compressed);
        ACE_UINT64 recv_compressed (void) const;

        // Setter and getter methods for recv_fifo
        void recv_fifo (ACE_UINT64 recv_fifo);
        ACE_UINT64 recv_fifo (void) const;

        // Setter and getter methods for recv_frames
        void recv_frames (ACE_UINT64 recv_frames);
        ACE_UINT64 recv_frames (void) const;

        // Setter and getter methods for sent_compressed
        void sent_compressed (ACE_UINT64 sent_compressed);
        ACE_UINT64 sent_compressed (void) const;

        // Setter and getter methods for sent_fifo
        void sent_fifo (ACE_UINT64 sent_fifo);
        ACE_UINT64 sent_fifo (void) const;

        // Setter and getter methods for sent_collision
        void sent_collision (ACE_UINT64 sent_collision);
        ACE_UINT64 sent_collision (void) const;

        // Setter and getter methods for sent_carrier
        void sent_carrier (ACE_UINT64 sent_carrier);
        ACE_UINT64 sent_carrier (void) const;

        protected:
        ACE_UINT64 recv_compressed_;

        ACE_UINT64 recv_fifo_;

        ACE_UINT64 recv_frames_;

        ACE_UINT64 sent_compressed_;

        ACE_UINT64 sent_fifo_;

        ACE_UINT64 sent_collision_;

        ACE_UINT64 sent_carrier_;
      };

      /**
       * @class WindowsNetworkProbeImpl
       */
      class OASIS_NETWORKPROBE_STUB_Export WindowsNetworkProbeImpl :
        public ::OASIS::System::Network::NetworkProbeImpl
      {
        public:
        /// The metadata for the software probe.
        static const ::OASIS::System::Network::WindowsNetworkProbe_Metadata __metadata__;

        /// Default constructor
        WindowsNetworkProbeImpl (void);

        /// Destructor
        virtual ~WindowsNetworkProbeImpl (void);

        /// Getter for the probe's metadata
        virtual const ::OASIS::System::Network::WindowsNetworkProbe_Metadata & metadata (void) const;

        /// Package the software probe's data.
        protected:
        virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


        public:
        /// Impl_Dump the software probe's data.
        virtual void dump (std::ostream & output);


        public:
        // Setter and getter methods for recv_unknown
        void recv_unknown (ACE_UINT64 recv_unknown);
        ACE_UINT64 recv_unknown (void) const;

        // Setter and getter methods for outbound_queue_length
        void outbound_queue_length (ACE_UINT64 outbound_queue_length);
        ACE_UINT64 outbound_queue_length (void) const;

        protected:
        ACE_UINT64 recv_unknown_;

        ACE_UINT64 outbound_queue_length_;
      };
    }
  }
}

#endif  // !defined __NETWORKPROBEIMPL_H__

