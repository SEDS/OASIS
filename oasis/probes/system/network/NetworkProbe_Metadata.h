// -*- C++ -*-

//============================================================================
/**
 * @file        NetworkProbe_Metadata.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _NETWORKPROBE_METADATA_H_
#define _NETWORKPROBE_METADATA_H_

#include "oasis/probes/Software_Probe_Metadata.h"

#include "NetworkProbe_stub_export.h"

namespace OASIS
{
  namespace System
  {
    namespace Network
    {
      /**
       * @class NetworkProbe_Metadata
       */
      class OASIS_NETWORKPROBE_STUB_Export NetworkProbe_Metadata :
        public ::OASIS::Software_Probe_Metadata 
      {
        public:
        /// Default constructor
        NetworkProbe_Metadata (void);

        /// Destructor
        virtual ~NetworkProbe_Metadata (void);

        protected:
        /// Initalizing constructor
        NetworkProbe_Metadata (const char * uuid,
                               const char * type_info,
                               ACE_UINT8 version_major,
                               ACE_UINT8 version_minor,
                               const char * schema);

        private:
        /// The metadata's schema
        static const char * __schema__;
      };

      /**
       * @class LinuxNetworkProbe_Metadata
       */
      class OASIS_NETWORKPROBE_STUB_Export LinuxNetworkProbe_Metadata :
        public ::OASIS::System::Network::NetworkProbe_Metadata 
      {
        public:
        /// Default constructor
        LinuxNetworkProbe_Metadata (void);

        /// Destructor
        virtual ~LinuxNetworkProbe_Metadata (void);

        protected:
        /// Initalizing constructor
        LinuxNetworkProbe_Metadata (const char * uuid,
                                    const char * type_info,
                                    ACE_UINT8 version_major,
                                    ACE_UINT8 version_minor,
                                    const char * schema);

        private:
        /// The metadata's schema
        static const char * __schema__;
      };

      /**
       * @class WindowsNetworkProbe_Metadata
       */
      class OASIS_NETWORKPROBE_STUB_Export WindowsNetworkProbe_Metadata :
        public ::OASIS::System::Network::NetworkProbe_Metadata 
      {
        public:
        /// Default constructor
        WindowsNetworkProbe_Metadata (void);

        /// Destructor
        virtual ~WindowsNetworkProbe_Metadata (void);

        protected:
        /// Initalizing constructor
        WindowsNetworkProbe_Metadata (const char * uuid,
                                      const char * type_info,
                                      ACE_UINT8 version_major,
                                      ACE_UINT8 version_minor,
                                      const char * schema);

        private:
        /// The metadata's schema
        static const char * __schema__;
      };
    }
  }
}

#endif  // !defined __NETWORKPROBE_METADATA_H__

