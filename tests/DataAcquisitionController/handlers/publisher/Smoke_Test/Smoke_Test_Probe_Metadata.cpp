// $Id$

#include "Smoke_Test_Probe_Metadata.h"

// 
// A_Metadata::__schema__
// 
const char * A_Metadata::__schema__ =
"<?xml version='1.0' encoding='UTF-8' ?>"
"<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
" xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
" xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
" elementFormDefault='qualified'"
" version='1.0'>"
"<xsd:element name='probeMetadata' type='A' />"
"<xsd:complexType name='A'>"
"<xsd:sequence>"
"<xsd:element name='a_value' type='xsd:int'  />"
"</xsd:sequence>"
"</xsd:complexType>"
"</xsd:schema>";

// 
// A_Metadata
// 
A_Metadata::A_Metadata (void)
: ::OASIS::Software_Probe_Metadata (
  "A0F230DF-8CAF-4B72-BE14-FE4BBCAD1ACA",
  "A",
  1,
  0,
  __schema__)
{
}


// 
// A_Metadata
// 
A_Metadata::A_Metadata (const char * uuid,
                        const char * type_info,
                        ACE_UINT8 version_major,
                        ACE_UINT8 version_minor,
                        const char * schema)
: ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
{
}


// 
// ~A_Metadata
// 
A_Metadata::~A_Metadata (void) 
{
}

namespace SmokeTest
{
  // 
  // B_Metadata::__schema__
  // 
  const char * B_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='SmokeTest.B' />"
  "<xsd:complexType name='SmokeTest.B'>"
  "<xsd:complexContent>"
  "<xsd:extension base='A'>"
  "<xsd:sequence>"
  "<xsd:element name='b_value' type='xsd:int'  />"
  "</xsd:sequence>"
  "</xsd:extension>"
  "</xsd:complexContent>"
  "</xsd:complexType>"
  "<xsd:complexType name='A'>"
  "<xsd:sequence>"
  "<xsd:element name='a_value' type='xsd:int'  />"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // B_Metadata
  // 
  B_Metadata::B_Metadata (void)
  : ::A_Metadata (
    "FDFD5CEA-11C8-429C-8D79-68A0930E37B7",
    "SmokeTest.B",
    1,
    0,
    __schema__)
  {
  }


  // 
  // B_Metadata
  // 
  B_Metadata::B_Metadata (const char * uuid,
                          const char * type_info,
                          ACE_UINT8 version_major,
                          ACE_UINT8 version_minor,
                          const char * schema)
  : ::A_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~B_Metadata
  // 
  B_Metadata::~B_Metadata (void) 
  {
  }

  // 
  // C_Metadata::__schema__
  // 
  const char * C_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='SmokeTest.C' />"
  "<xsd:complexType name='SmokeTest.C'>"
  "<xsd:complexContent>"
  "<xsd:extension base='SmokeTest.B'>"
  "<xsd:sequence>"
  "<xsd:element name='c_value' type='xsd:int'  />"
  "</xsd:sequence>"
  "</xsd:extension>"
  "</xsd:complexContent>"
  "</xsd:complexType>"
  "<xsd:complexType name='A'>"
  "<xsd:sequence>"
  "<xsd:element name='a_value' type='xsd:int'  />"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "<xsd:complexType name='SmokeTest.B'>"
  "<xsd:complexContent>"
  "<xsd:extension base='A'>"
  "<xsd:sequence>"
  "<xsd:element name='b_value' type='xsd:int'  />"
  "</xsd:sequence>"
  "</xsd:extension>"
  "</xsd:complexContent>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // C_Metadata
  // 
  C_Metadata::C_Metadata (void)
  : ::SmokeTest::B_Metadata (
    "2634666C-EB69-4A49-B9A6-C1F35CF86BE6",
    "SmokeTest.C",
    1,
    0,
    __schema__)
  {
  }


  // 
  // C_Metadata
  // 
  C_Metadata::C_Metadata (const char * uuid,
                          const char * type_info,
                          ACE_UINT8 version_major,
                          ACE_UINT8 version_minor,
                          const char * schema)
  : ::SmokeTest::B_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~C_Metadata
  // 
  C_Metadata::~C_Metadata (void) 
  {
  }
}

