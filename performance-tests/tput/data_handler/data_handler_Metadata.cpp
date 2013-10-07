// $Id$

#include "data_handler_Metadata.h"

namespace Test
{
  // 
  // Byte_0_Metadata::__schema__
  // 
  const char * Byte_0_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='Test.Byte_0' />"
  "<xsd:complexType name='Test.Byte_0'>"
  "<xsd:sequence>"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // Byte_0_Metadata
  // 
  Byte_0_Metadata::Byte_0_Metadata (void)
  : ::OASIS::Software_Probe_Metadata (
    "0D1000D0-0CC4-4EC5-A366-E89C0B5F8ACD",
    "Test.Byte_0",
    1,
    0,
    __schema__)
  {
  }


  // 
  // Byte_0_Metadata
  // 
  Byte_0_Metadata::Byte_0_Metadata (const char * uuid,
                                    const char * type_info,
                                    ACE_UINT8 version_major,
                                    ACE_UINT8 version_minor,
                                    const char * schema)
  : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~Byte_0_Metadata
  // 
  Byte_0_Metadata::~Byte_0_Metadata (void) 
  {
  }

  // 
  // Byte_8_Metadata::__schema__
  // 
  const char * Byte_8_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='Test.Byte_8' />"
  "<xsd:complexType name='Test.Byte_8'>"
  "<xsd:sequence>"
  "<xsd:element name='value' type='xsd:byte'  />"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // Byte_8_Metadata
  // 
  Byte_8_Metadata::Byte_8_Metadata (void)
  : ::OASIS::Software_Probe_Metadata (
    "FD1000D0-0CC4-4EC5-A366-E89C0B5F8ACD",
    "Test.Byte_8",
    1,
    0,
    __schema__)
  {
  }


  // 
  // Byte_8_Metadata
  // 
  Byte_8_Metadata::Byte_8_Metadata (const char * uuid,
                                    const char * type_info,
                                    ACE_UINT8 version_major,
                                    ACE_UINT8 version_minor,
                                    const char * schema)
  : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~Byte_8_Metadata
  // 
  Byte_8_Metadata::~Byte_8_Metadata (void) 
  {
  }

  // 
  // Byte_16_Metadata::__schema__
  // 
  const char * Byte_16_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='Test.Byte_16' />"
  "<xsd:complexType name='Test.Byte_16'>"
  "<xsd:sequence>"
  "<xsd:element name='value' type='xsd:unsignedShort'  />"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // Byte_16_Metadata
  // 
  Byte_16_Metadata::Byte_16_Metadata (void)
  : ::OASIS::Software_Probe_Metadata (
    "0D1520D0-0CC4-4EC5-A366-E89C0B5F8ACD",
    "Test.Byte_16",
    1,
    0,
    __schema__)
  {
  }


  // 
  // Byte_16_Metadata
  // 
  Byte_16_Metadata::Byte_16_Metadata (const char * uuid,
                                      const char * type_info,
                                      ACE_UINT8 version_major,
                                      ACE_UINT8 version_minor,
                                      const char * schema)
  : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~Byte_16_Metadata
  // 
  Byte_16_Metadata::~Byte_16_Metadata (void) 
  {
  }

  // 
  // Byte_32_Metadata::__schema__
  // 
  const char * Byte_32_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='Test.Byte_32' />"
  "<xsd:complexType name='Test.Byte_32'>"
  "<xsd:sequence>"
  "<xsd:element name='value' type='xsd:unsignedInt'  />"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // Byte_32_Metadata
  // 
  Byte_32_Metadata::Byte_32_Metadata (void)
  : ::OASIS::Software_Probe_Metadata (
    "0D1000D0-0CC4-4EC5-A366-E89C0B598ACD",
    "Test.Byte_32",
    1,
    0,
    __schema__)
  {
  }


  // 
  // Byte_32_Metadata
  // 
  Byte_32_Metadata::Byte_32_Metadata (const char * uuid,
                                      const char * type_info,
                                      ACE_UINT8 version_major,
                                      ACE_UINT8 version_minor,
                                      const char * schema)
  : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~Byte_32_Metadata
  // 
  Byte_32_Metadata::~Byte_32_Metadata (void) 
  {
  }

  // 
  // Byte_64_Metadata::__schema__
  // 
  const char * Byte_64_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='Test.Byte_64' />"
  "<xsd:complexType name='Test.Byte_64'>"
  "<xsd:sequence>"
  "<xsd:element name='value' type='xsd:unsignedLong'  />"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // Byte_64_Metadata
  // 
  Byte_64_Metadata::Byte_64_Metadata (void)
  : ::OASIS::Software_Probe_Metadata (
    "0D1000D0-0CC4-4EC5-A366-E89C0B5F8ACD",
    "Test.Byte_64",
    1,
    0,
    __schema__)
  {
  }


  // 
  // Byte_64_Metadata
  // 
  Byte_64_Metadata::Byte_64_Metadata (const char * uuid,
                                      const char * type_info,
                                      ACE_UINT8 version_major,
                                      ACE_UINT8 version_minor,
                                      const char * schema)
  : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~Byte_64_Metadata
  // 
  Byte_64_Metadata::~Byte_64_Metadata (void) 
  {
  }

  // 
  // Byte_128_Metadata::__schema__
  // 
  const char * Byte_128_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='Test.Byte_128' />"
  "<xsd:complexType name='Test.Byte_128'>"
  "<xsd:sequence>"
  "<xsd:element name='value_a' type='xsd:unsignedLong'  />"
  "<xsd:element name='value_b' type='xsd:unsignedLong'  />"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // Byte_128_Metadata
  // 
  Byte_128_Metadata::Byte_128_Metadata (void)
  : ::OASIS::Software_Probe_Metadata (
    "0D9000D0-0CC4-4EC5-A366-E89C0B5F8ACD",
    "Test.Byte_128",
    1,
    0,
    __schema__)
  {
  }


  // 
  // Byte_128_Metadata
  // 
  Byte_128_Metadata::Byte_128_Metadata (const char * uuid,
                                        const char * type_info,
                                        ACE_UINT8 version_major,
                                        ACE_UINT8 version_minor,
                                        const char * schema)
  : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~Byte_128_Metadata
  // 
  Byte_128_Metadata::~Byte_128_Metadata (void) 
  {
  }

  // 
  // Byte_256_Metadata::__schema__
  // 
  const char * Byte_256_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='Test.Byte_256' />"
  "<xsd:complexType name='Test.Byte_256'>"
  "<xsd:sequence>"
  "<xsd:element name='value_a' type='xsd:unsignedLong'  />"
  "<xsd:element name='value_b' type='xsd:unsignedLong'  />"
  "<xsd:element name='value_c' type='xsd:unsignedLong'  />"
  "<xsd:element name='value_d' type='xsd:unsignedLong'  />"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // Byte_256_Metadata
  // 
  Byte_256_Metadata::Byte_256_Metadata (void)
  : ::OASIS::Software_Probe_Metadata (
    "0D1000A0-0CC4-4EC5-A366-E89C0B5F8ACD",
    "Test.Byte_256",
    1,
    0,
    __schema__)
  {
  }


  // 
  // Byte_256_Metadata
  // 
  Byte_256_Metadata::Byte_256_Metadata (const char * uuid,
                                        const char * type_info,
                                        ACE_UINT8 version_major,
                                        ACE_UINT8 version_minor,
                                        const char * schema)
  : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~Byte_256_Metadata
  // 
  Byte_256_Metadata::~Byte_256_Metadata (void) 
  {
  }
}

