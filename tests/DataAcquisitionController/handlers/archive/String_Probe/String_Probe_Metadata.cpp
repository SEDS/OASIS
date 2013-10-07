// $Id$

#include "String_Probe_Metadata.h"

namespace Test
{
  // 
  // String_Probe_Metadata::__schema__
  // 
  const char * String_Probe_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='Test.String_Probe' />"
  "<xsd:complexType name='Test.String_Probe'>"
  "<xsd:sequence>"
  "<xsd:element name='str_value' type='xsd:string'  />"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // String_Probe_Metadata
  // 
  String_Probe_Metadata::String_Probe_Metadata (void)
  : ::OASIS::Software_Probe_Metadata (
    "4F4BF6A7-5B50-4358-A9D6-6D840C436FB7",
    "Test.String_Probe",
    1,
    0,
    __schema__)
  {
  }


  // 
  // String_Probe_Metadata
  // 
  String_Probe_Metadata::String_Probe_Metadata (const char * uuid,
                                                const char * type_info,
                                                ACE_UINT8 version_major,
                                                ACE_UINT8 version_minor,
                                                const char * schema)
  : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~String_Probe_Metadata
  // 
  String_Probe_Metadata::~String_Probe_Metadata (void) 
  {
  }
}

