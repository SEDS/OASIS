// $Id$

#include "NetworkProbe_Metadata.h"

namespace OASIS
{
  namespace System
  {
    namespace Network
    {
      // 
      // NetworkProbe_Metadata::__schema__
      // 
      const char * NetworkProbe_Metadata::__schema__ =
      "<?xml version='1.0' encoding='UTF-8' ?>"
      "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
      " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
      " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
      " elementFormDefault='qualified'"
      " version='1.0'>"
      "<xsd:element name='probeMetadata' type='OASIS.System.Network.NetworkProbe' />"
      "<xsd:complexType name='OASIS.System.Network.NetworkProbe'>"
      "<xsd:sequence>"
      "<xsd:element name='nic' type='xsd:string'  />"
      "<xsd:element name='recv_bytes' type='xsd:unsignedLong'  />"
      "<xsd:element name='recv_packets' type='xsd:unsignedLong'  />"
      "<xsd:element name='recv_errors' type='xsd:unsignedLong'  />"
      "<xsd:element name='recv_drop' type='xsd:unsignedLong'  />"
      "<xsd:element name='recv_multicast' type='xsd:unsignedLong'  />"
      "<xsd:element name='sent_bytes' type='xsd:unsignedLong'  />"
      "<xsd:element name='sent_packets' type='xsd:unsignedLong'  />"
      "<xsd:element name='sent_errors' type='xsd:unsignedLong'  />"
      "<xsd:element name='sent_drop' type='xsd:unsignedLong'  />"
      "</xsd:sequence>"
      "</xsd:complexType>"
      "</xsd:schema>";

      // 
      // NetworkProbe_Metadata
      // 
      NetworkProbe_Metadata::NetworkProbe_Metadata (void)
      : ::OASIS::Software_Probe_Metadata (
        "E4080CC5-C501-4A33-B72C-AD5DBC444FB9",
        "OASIS.System.Network.NetworkProbe",
        1,
        0,
        __schema__)
      {
      }


      // 
      // NetworkProbe_Metadata
      // 
      NetworkProbe_Metadata::NetworkProbe_Metadata (const char * uuid,
                                                    const char * type_info,
                                                    ACE_UINT8 version_major,
                                                    ACE_UINT8 version_minor,
                                                    const char * schema)
      : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
      {
      }


      // 
      // ~NetworkProbe_Metadata
      // 
      NetworkProbe_Metadata::~NetworkProbe_Metadata (void) 
      {
      }

      // 
      // LinuxNetworkProbe_Metadata::__schema__
      // 
      const char * LinuxNetworkProbe_Metadata::__schema__ =
      "<?xml version='1.0' encoding='UTF-8' ?>"
      "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
      " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
      " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
      " elementFormDefault='qualified'"
      " version='1.0'>"
      "<xsd:element name='probeMetadata' type='OASIS.System.Network.LinuxNetworkProbe' />"
      "<xsd:complexType name='OASIS.System.Network.LinuxNetworkProbe'>"
      "<xsd:complexContent>"
      "<xsd:extension base='OASIS.System.Network.NetworkProbe'>"
      "<xsd:sequence>"
      "<xsd:element name='recv_compressed' type='xsd:unsignedLong'  />"
      "<xsd:element name='recv_fifo' type='xsd:unsignedLong'  />"
      "<xsd:element name='recv_frames' type='xsd:unsignedLong'  />"
      "<xsd:element name='sent_compressed' type='xsd:unsignedLong'  />"
      "<xsd:element name='sent_fifo' type='xsd:unsignedLong'  />"
      "<xsd:element name='sent_collision' type='xsd:unsignedLong'  />"
      "<xsd:element name='sent_carrier' type='xsd:unsignedLong'  />"
      "</xsd:sequence>"
      "</xsd:extension>"
      "</xsd:complexContent>"
      "</xsd:complexType>"
      "<xsd:complexType name='OASIS.System.Network.NetworkProbe'>"
      "<xsd:sequence>"
      "<xsd:element name='nic' type='xsd:string'  />"
      "<xsd:element name='recv_bytes' type='xsd:unsignedLong'  />"
      "<xsd:element name='recv_packets' type='xsd:unsignedLong'  />"
      "<xsd:element name='recv_errors' type='xsd:unsignedLong'  />"
      "<xsd:element name='recv_drop' type='xsd:unsignedLong'  />"
      "<xsd:element name='recv_multicast' type='xsd:unsignedLong'  />"
      "<xsd:element name='sent_bytes' type='xsd:unsignedLong'  />"
      "<xsd:element name='sent_packets' type='xsd:unsignedLong'  />"
      "<xsd:element name='sent_errors' type='xsd:unsignedLong'  />"
      "<xsd:element name='sent_drop' type='xsd:unsignedLong'  />"
      "</xsd:sequence>"
      "</xsd:complexType>"
      "</xsd:schema>";

      // 
      // LinuxNetworkProbe_Metadata
      // 
      LinuxNetworkProbe_Metadata::LinuxNetworkProbe_Metadata (void)
      : ::OASIS::System::Network::NetworkProbe_Metadata (
        "942266F1-5301-45BE-B700-2D6E2DADBAB7",
        "OASIS.System.Network.LinuxNetworkProbe",
        1,
        0,
        __schema__)
      {
      }


      // 
      // LinuxNetworkProbe_Metadata
      // 
      LinuxNetworkProbe_Metadata::LinuxNetworkProbe_Metadata (const char * uuid,
                                                              const char * type_info,
                                                              ACE_UINT8 version_major,
                                                              ACE_UINT8 version_minor,
                                                              const char * schema)
      : ::OASIS::System::Network::NetworkProbe_Metadata (uuid, type_info, version_major, version_minor, schema)
      {
      }


      // 
      // ~LinuxNetworkProbe_Metadata
      // 
      LinuxNetworkProbe_Metadata::~LinuxNetworkProbe_Metadata (void) 
      {
      }

      // 
      // WindowsNetworkProbe_Metadata::__schema__
      // 
      const char * WindowsNetworkProbe_Metadata::__schema__ =
      "<?xml version='1.0' encoding='UTF-8' ?>"
      "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
      " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
      " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
      " elementFormDefault='qualified'"
      " version='1.0'>"
      "<xsd:element name='probeMetadata' type='OASIS.System.Network.WindowsNetworkProbe' />"
      "<xsd:complexType name='OASIS.System.Network.WindowsNetworkProbe'>"
      "<xsd:complexContent>"
      "<xsd:extension base='OASIS.System.Network.NetworkProbe'>"
      "<xsd:sequence>"
      "<xsd:element name='recv_unknown' type='xsd:unsignedLong'  />"
      "<xsd:element name='outbound_queue_length' type='xsd:unsignedLong'  />"
      "</xsd:sequence>"
      "</xsd:extension>"
      "</xsd:complexContent>"
      "</xsd:complexType>"
      "<xsd:complexType name='OASIS.System.Network.NetworkProbe'>"
      "<xsd:sequence>"
      "<xsd:element name='nic' type='xsd:string'  />"
      "<xsd:element name='recv_bytes' type='xsd:unsignedLong'  />"
      "<xsd:element name='recv_packets' type='xsd:unsignedLong'  />"
      "<xsd:element name='recv_errors' type='xsd:unsignedLong'  />"
      "<xsd:element name='recv_drop' type='xsd:unsignedLong'  />"
      "<xsd:element name='recv_multicast' type='xsd:unsignedLong'  />"
      "<xsd:element name='sent_bytes' type='xsd:unsignedLong'  />"
      "<xsd:element name='sent_packets' type='xsd:unsignedLong'  />"
      "<xsd:element name='sent_errors' type='xsd:unsignedLong'  />"
      "<xsd:element name='sent_drop' type='xsd:unsignedLong'  />"
      "</xsd:sequence>"
      "</xsd:complexType>"
      "</xsd:schema>";

      // 
      // WindowsNetworkProbe_Metadata
      // 
      WindowsNetworkProbe_Metadata::WindowsNetworkProbe_Metadata (void)
      : ::OASIS::System::Network::NetworkProbe_Metadata (
        "997D59E4-A7A7-473C-8D4F-D55CF9E75206",
        "OASIS.System.Network.WindowsNetworkProbe",
        1,
        0,
        __schema__)
      {
      }


      // 
      // WindowsNetworkProbe_Metadata
      // 
      WindowsNetworkProbe_Metadata::WindowsNetworkProbe_Metadata (const char * uuid,
                                                                  const char * type_info,
                                                                  ACE_UINT8 version_major,
                                                                  ACE_UINT8 version_minor,
                                                                  const char * schema)
      : ::OASIS::System::Network::NetworkProbe_Metadata (uuid, type_info, version_major, version_minor, schema)
      {
      }


      // 
      // ~WindowsNetworkProbe_Metadata
      // 
      WindowsNetworkProbe_Metadata::~WindowsNetworkProbe_Metadata (void) 
      {
      }
    }
  }
}

