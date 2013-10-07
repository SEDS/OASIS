// $Id$

#include "String_Probe_Metadata.h"

namespace OASIS
{
  // 
  // String_SoftwareProbe_Metadata::__schema__
  // 
  const char * String_SoftwareProbe_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='OASIS.String_SoftwareProbe' />"
  "<xsd:complexType name='OASIS.String_SoftwareProbe'>"
  "<xsd:sequence>"
  "<xsd:element name='value' type='xsd:string'  />"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // String_SoftwareProbe_Metadata
  // 
  String_SoftwareProbe_Metadata::String_SoftwareProbe_Metadata (void)
  : ::OASIS::Software_Probe_Metadata (
    "6E1F2E3E-C7DF-4EDD-A903-175108F8D554",
    "OASIS.String_SoftwareProbe",
    1,
    0,
    __schema__)
  {
  }


  // 
  // String_SoftwareProbe_Metadata
  // 
  String_SoftwareProbe_Metadata::String_SoftwareProbe_Metadata (const char * uuid,
                                                                const char * type_info,
                                                                ACE_UINT8 version_major,
                                                                ACE_UINT8 version_minor,
                                                                const char * schema)
  : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~String_SoftwareProbe_Metadata
  // 
  String_SoftwareProbe_Metadata::~String_SoftwareProbe_Metadata (void) 
  {
  }
}

