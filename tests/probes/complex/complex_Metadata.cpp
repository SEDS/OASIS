// $Id$

#include "complex_Metadata.h"

namespace OASIS
{
  // 
  // ComplexSoftwareProbe_Metadata::__schema__
  // 
  const char * ComplexSoftwareProbe_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='OASIS.ComplexSoftwareProbe' />"
  "<xsd:complexType name='OASIS.ComplexSoftwareProbe'>"
  "<xsd:sequence>"
  "<xsd:element name='value' type='xsd:long'  />"
  "<xsd:element name='p' type='OASIS.Point'  />"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "<xsd:complexType name='OASIS.Point'>"
  "<xsd:sequence>"
  "<xsd:element name='x' type='xsd:int'  />"
  "<xsd:element name='y' type='xsd:int'  />"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // ComplexSoftwareProbe_Metadata
  // 
  ComplexSoftwareProbe_Metadata::ComplexSoftwareProbe_Metadata (void)
  : ::OASIS::Software_Probe_Metadata (
    "7B186D20-87D9-4D7E-95C2-139CC51D63CE",
    "OASIS.ComplexSoftwareProbe",
    1,
    0,
    __schema__)
  {
  }


  // 
  // ComplexSoftwareProbe_Metadata
  // 
  ComplexSoftwareProbe_Metadata::ComplexSoftwareProbe_Metadata (const char * uuid,
                                                                const char * type_info,
                                                                ACE_UINT8 version_major,
                                                                ACE_UINT8 version_minor,
                                                                const char * schema)
  : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~ComplexSoftwareProbe_Metadata
  // 
  ComplexSoftwareProbe_Metadata::~ComplexSoftwareProbe_Metadata (void) 
  {
  }
}

