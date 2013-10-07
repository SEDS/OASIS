// $Id$

#include "nodata_Metadata.h"

namespace Test
{
  // 
  // NoDataProbe_Metadata::__schema__
  // 
  const char * NoDataProbe_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='Test.NoDataProbe' />"
  "<xsd:complexType name='Test.NoDataProbe'>"
  "<xsd:sequence>"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // NoDataProbe_Metadata
  // 
  NoDataProbe_Metadata::NoDataProbe_Metadata (void)
  : ::OASIS::Software_Probe_Metadata (
    "0D1000D0-0CC4-4EC5-A366-E89C0B5F8ACD",
    "Test.NoDataProbe",
    1,
    0,
    __schema__)
  {
  }


  // 
  // NoDataProbe_Metadata
  // 
  NoDataProbe_Metadata::NoDataProbe_Metadata (const char * uuid,
                                              const char * type_info,
                                              ACE_UINT8 version_major,
                                              ACE_UINT8 version_minor,
                                              const char * schema)
  : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~NoDataProbe_Metadata
  // 
  NoDataProbe_Metadata::~NoDataProbe_Metadata (void) 
  {
  }
}

