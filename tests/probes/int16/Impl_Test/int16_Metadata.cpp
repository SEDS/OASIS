// $Id$

#include "int16_Metadata.h"

namespace OASIS
{
  // 
  // Int16_SoftwareProbe_Metadata::__schema__
  // 
  const char * Int16_SoftwareProbe_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='OASIS.Int16_SoftwareProbe' />"
  "<xsd:complexType name='OASIS.Int16_SoftwareProbe'>"
  "<xsd:sequence>"
  "<xsd:element name='value' type='xsd:short'  />"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // Int16_SoftwareProbe_Metadata
  // 
  Int16_SoftwareProbe_Metadata::Int16_SoftwareProbe_Metadata (void)
  : ::OASIS::Software_Probe_Metadata (
    "8BBA0BD5-877E-4400-B212-420566DEE715",
    "OASIS.Int16_SoftwareProbe",
    1,
    0,
    __schema__)
  {
  }


  // 
  // Int16_SoftwareProbe_Metadata
  // 
  Int16_SoftwareProbe_Metadata::Int16_SoftwareProbe_Metadata (const char * uuid,
                                                              const char * type_info,
                                                              ACE_UINT8 version_major,
                                                              ACE_UINT8 version_minor,
                                                              const char * schema)
  : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~Int16_SoftwareProbe_Metadata
  // 
  Int16_SoftwareProbe_Metadata::~Int16_SoftwareProbe_Metadata (void) 
  {
  }
}

