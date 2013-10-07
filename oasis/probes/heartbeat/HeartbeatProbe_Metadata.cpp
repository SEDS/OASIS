// $Id$

#include "HeartbeatProbe_Metadata.h"

namespace OASIS
{
  // 
  // HeartbeatProbe_Metadata::__schema__
  // 
  const char * HeartbeatProbe_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='OASIS.HeartbeatProbe' />"
  "<xsd:complexType name='OASIS.HeartbeatProbe'>"
  "<xsd:sequence>"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // HeartbeatProbe_Metadata
  // 
  HeartbeatProbe_Metadata::HeartbeatProbe_Metadata (void)
  : ::OASIS::Software_Probe_Metadata (
    "FF521251-7D7F-49EC-96FF-9A474A8E714E",
    "OASIS.HeartbeatProbe",
    1,
    0,
    __schema__)
  {
  }


  // 
  // HeartbeatProbe_Metadata
  // 
  HeartbeatProbe_Metadata::HeartbeatProbe_Metadata (const char * uuid,
                                                    const char * type_info,
                                                    ACE_UINT8 version_major,
                                                    ACE_UINT8 version_minor,
                                                    const char * schema)
  : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~HeartbeatProbe_Metadata
  // 
  HeartbeatProbe_Metadata::~HeartbeatProbe_Metadata (void) 
  {
  }
}

