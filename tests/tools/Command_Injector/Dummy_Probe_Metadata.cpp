// $Id$

#include "Dummy_Probe_Metadata.h"

// 
// Dummy_Probe_Metadata::__schema__
// 
const char * Dummy_Probe_Metadata::__schema__ =
"<?xml version='1.0' encoding='UTF-8' ?>"
"<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
" xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
" xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
" elementFormDefault='qualified'"
" version='1.0'>"
"<xsd:element name='probeMetadata' type='Dummy_Probe' />"
"<xsd:complexType name='Dummy_Probe'>"
"<xsd:sequence>"
"</xsd:sequence>"
"</xsd:complexType>"
"</xsd:schema>";

// 
// Dummy_Probe_Metadata
// 
Dummy_Probe_Metadata::Dummy_Probe_Metadata (void)
: ::OASIS::Software_Probe_Metadata (
  "82E730A5-2027-4538-98EB-CC9A4DA8AC67",
  "Dummy_Probe",
  1,
  0,
  __schema__)
{
}


// 
// Dummy_Probe_Metadata
// 
Dummy_Probe_Metadata::Dummy_Probe_Metadata (const char * uuid,
                                            const char * type_info,
                                            ACE_UINT8 version_major,
                                            ACE_UINT8 version_minor,
                                            const char * schema)
: ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
{
}


// 
// ~Dummy_Probe_Metadata
// 
Dummy_Probe_Metadata::~Dummy_Probe_Metadata (void) 
{
}

