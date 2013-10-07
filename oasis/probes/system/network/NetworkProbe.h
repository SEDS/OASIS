// -*- C++ -*-

//============================================================================
/**
 * @file        NetworkProbe.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _NETWORKPROBE_H_
#define _NETWORKPROBE_H_

#include "oasis/probes/Data_Types.h"
#include "oasis/probes/Software_Probe.h"
#include "NetworkProbe_Metadata.h"
#include <iostream>

#include "NetworkProbe_stub_export.h"

namespace OASIS
{
  namespace System
  {
    namespace Network
    {
      /**
       * @class NetworkProbe
       */
      class OASIS_NETWORKPROBE_STUB_Export NetworkProbe :
        public virtual ::OASIS::Software_Probe 
      {
        public:
        // Type definition of the software probe's metadata.
        typedef ::OASIS::System::Network::NetworkProbe_Metadata METADATA_TYPE;

        /// The metadata for the software probe.
        static const METADATA_TYPE __metadata__;

        /// Default constructor
        NetworkProbe (void);

        /// Destructor
        virtual ~NetworkProbe (void);

        /// Getter for the probe's metadata
        virtual const METADATA_TYPE & metadata (void) const;

        public:
        /// Recall the software probe's data.
        virtual int recall (const char * data, size_t length, int byte_order);

        protected:
        /// Helper method for recalling the data.
        int recall (ACE_InputCDR & input);

        public:
        /// Stub_Dump the software probe's data.
        virtual void dump (std::ostream & output);


        public:
        // Getter method for nic
        const ACE_CString & nic (void) const;

        // Getter method for recv_bytes
        ACE_UINT64 recv_bytes (void) const;

        // Getter method for recv_packets
        ACE_UINT64 recv_packets (void) const;

        // Getter method for recv_errors
        ACE_UINT64 recv_errors (void) const;

        // Getter method for recv_drop
        ACE_UINT64 recv_drop (void) const;

        // Getter method for recv_multicast
        ACE_UINT64 recv_multicast (void) const;

        // Getter method for sent_bytes
        ACE_UINT64 sent_bytes (void) const;

        // Getter method for sent_packets
        ACE_UINT64 sent_packets (void) const;

        // Getter method for sent_errors
        ACE_UINT64 sent_errors (void) const;

        // Getter method for sent_drop
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
       * @class LinuxNetworkProbe
       */
      class OASIS_NETWORKPROBE_STUB_Export LinuxNetworkProbe :
        public ::OASIS::System::Network::NetworkProbe 
      {
        public:
        // Type definition of the software probe's metadata.
        typedef ::OASIS::System::Network::LinuxNetworkProbe_Metadata METADATA_TYPE;

        /// The metadata for the software probe.
        static const METADATA_TYPE __metadata__;

        /// Default constructor
        LinuxNetworkProbe (void);

        /// Destructor
        virtual ~LinuxNetworkProbe (void);

        /// Getter for the probe's metadata
        virtual const METADATA_TYPE & metadata (void) const;

        public:
        /// Recall the software probe's data.
        virtual int recall (const char * data, size_t length, int byte_order);

        protected:
        /// Helper method for recalling the data.
        int recall (ACE_InputCDR & input);

        public:
        /// Stub_Dump the software probe's data.
        virtual void dump (std::ostream & output);


        public:
        // Getter method for recv_compressed
        ACE_UINT64 recv_compressed (void) const;

        // Getter method for recv_fifo
        ACE_UINT64 recv_fifo (void) const;

        // Getter method for recv_frames
        ACE_UINT64 recv_frames (void) const;

        // Getter method for sent_compressed
        ACE_UINT64 sent_compressed (void) const;

        // Getter method for sent_fifo
        ACE_UINT64 sent_fifo (void) const;

        // Getter method for sent_collision
        ACE_UINT64 sent_collision (void) const;

        // Getter method for sent_carrier
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
       * @class WindowsNetworkProbe
       */
      class OASIS_NETWORKPROBE_STUB_Export WindowsNetworkProbe :
        public ::OASIS::System::Network::NetworkProbe 
      {
        public:
        // Type definition of the software probe's metadata.
        typedef ::OASIS::System::Network::WindowsNetworkProbe_Metadata METADATA_TYPE;

        /// The metadata for the software probe.
        static const METADATA_TYPE __metadata__;

        /// Default constructor
        WindowsNetworkProbe (void);

        /// Destructor
        virtual ~WindowsNetworkProbe (void);

        /// Getter for the probe's metadata
        virtual const METADATA_TYPE & metadata (void) const;

        public:
        /// Recall the software probe's data.
        virtual int recall (const char * data, size_t length, int byte_order);

        protected:
        /// Helper method for recalling the data.
        int recall (ACE_InputCDR & input);

        public:
        /// Stub_Dump the software probe's data.
        virtual void dump (std::ostream & output);


        public:
        // Getter method for recv_unknown
        ACE_UINT64 recv_unknown (void) const;

        // Getter method for outbound_queue_length
        ACE_UINT64 outbound_queue_length (void) const;

        protected:
        ACE_UINT64 recv_unknown_;

        ACE_UINT64 outbound_queue_length_;
      };
    }
  }
}

#endif  // !defined __NETWORKPROBE_H__

