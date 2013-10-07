// $Id$

#include "Foo_Metadata.h"

namespace OASIS
{
  // 
  // Foo_Metadata::__schema__
  // 
  const char * Foo_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='OASIS.Foo' />"
  "<xsd:complexType name='OASIS.Foo'>"
  "<xsd:sequence>"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // Foo_Metadata
  // 
  Foo_Metadata::Foo_Metadata (void)
  : ::OASIS::Software_Probe_Metadata (
    "F45690E5-EDC9-4FAC-8BF2-599ADB790183",
    "OASIS.Foo",
    1,
    0,
    __schema__)
  {
  }


  // 
  // Foo_Metadata
  // 
  Foo_Metadata::Foo_Metadata (const char * uuid,
                              const char * type_info,
                              ACE_UINT8 version_major,
                              ACE_UINT8 version_minor,
                              const char * schema)
  : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~Foo_Metadata
  // 
  Foo_Metadata::~Foo_Metadata (void) 
  {
  }
}

