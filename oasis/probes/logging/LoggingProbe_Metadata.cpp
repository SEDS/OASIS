// $Id$

#include "LoggingProbe_Metadata.h"

namespace OASIS
{
  // 
  // LoggingProbe_Metadata::__schema__
  // 
  const char * LoggingProbe_Metadata::__schema__ =
  "<?xml version='1.0' encoding='UTF-8' ?>"
  "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
  " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
  " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
  " elementFormDefault='qualified'"
  " version='1.0'>"
  "<xsd:element name='probeMetadata' type='OASIS.LoggingProbe' />"
  "<xsd:complexType name='OASIS.LoggingProbe'>"
  "<xsd:sequence>"
  "<xsd:element name='severity' type='xsd:int'  />"
  "<xsd:element name='thread_id' type='xsd:int'  />"
  "<xsd:element name='message' type='xsd:string'  />"
  "</xsd:sequence>"
  "</xsd:complexType>"
  "</xsd:schema>";

  // 
  // LoggingProbe_Metadata
  // 
  LoggingProbe_Metadata::LoggingProbe_Metadata (void)
  : ::OASIS::Software_Probe_Metadata (
    "B2C387BE-79C3-43B6-8A36-4A852B8ADD1F",
    "OASIS.LoggingProbe",
    1,
    0,
    __schema__)
  {
  }


  // 
  // LoggingProbe_Metadata
  // 
  LoggingProbe_Metadata::LoggingProbe_Metadata (const char * uuid,
                                                const char * type_info,
                                                ACE_UINT8 version_major,
                                                ACE_UINT8 version_minor,
                                                const char * schema)
  : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
  {
  }


  // 
  // ~LoggingProbe_Metadata
  // 
  LoggingProbe_Metadata::~LoggingProbe_Metadata (void) 
  {
  }
}

