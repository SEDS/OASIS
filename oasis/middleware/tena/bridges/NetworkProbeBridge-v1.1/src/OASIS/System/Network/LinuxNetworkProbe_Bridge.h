// -*- C++ -*-

//=============================================================================
/**
 * @file        LinuxNetworkProbe_Bridge.h
 *
 * $Id: LinuxNetworkProbe_Bridge.h 2135 2012-02-16 15:39:18Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_SYSTEM_NETWORK_LINUXNETWORKPROBE_LINUXNETWORKPROBE_BRIDGE_H_
#define _OASIS_SYSTEM_NETWORK_LINUXNETWORKPROBE_LINUXNETWORKPROBE_BRIDGE_H_

#include "OASIS/System/Network/LinuxNetworkProbe.h"
#include "oasis/middleware/tena/bridges/Software_Probe_Bridge_T.h"

namespace OASIS
{
  namespace System
  {
    namespace Network
    {

      /**
       * @class LinuxNetworkProbe_Bridge
       *
       * Software probe bridge for OASIS::System::Network::LinuxNetworkProbe.
       */
      class LinuxNetworkProbe_Bridge :
        public ::OASIS::Software_Probe_Bridge_T < ::OASIS::System::Network::LinuxNetworkProbe_SDO >
      {
      public:
        /// Type definition of the base type.
        typedef ::OASIS::Software_Probe_Bridge_T < ::OASIS::System::Network::LinuxNetworkProbe_SDO > base_type;

        /// Static factory method.
        static ::OASIS::Software_Probe_Bridge * _create (void);

        /// Default constructor.
        LinuxNetworkProbe_Bridge (void);

        /// Destructor.
        virtual ~LinuxNetworkProbe_Bridge (void);

        /**
         * Create a new servant for the specified software probe instance.
         *
         * @param[in]        einode            Parent EI node
         * @param[in]        inst              Software probe instance
         */
        virtual int create_servant (const ACE_Utils::UUID & einode,
                                    const ::OASIS::DAC::Software_Probe_Instance &);

        /**
         * Publish a new data packet. This will convert the OASIS data packet
         * to an TENA object, then publish it via the TENA middleware.
         *
         * @param[in]         packet           Data packet to publish
         */
        virtual int publish (const ::OASIS::DAC::Data_Packet & packet);

        /// Type definition of the SDO publication state updater.
        typedef ::OASIS::System::Network::LinuxNetworkProbe::PublicationStateUpdater PublicationStateUpdater;

        /**
         * Utility method that extract values from the provided input
         * stream and set its corresponding value on the updater.
         *
         * @param[in]        updater           Target updater
         * @param[in]        input             Source input stream
         */
        static int update (PublicationStateUpdater & updater, ACE_InputCDR & input);
      };

    }
  }
}

#endif  // !defined _OASIS_SYSTEM_NETWORK_LINUXNETWORKPROBE_LINUXNETWORKPROBE_BRIDGE_H_
