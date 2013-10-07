// $Id$

#include "TemperatureProbe_Metadata.h"

namespace OASIS
{
  namespace HardwareProbes
  {
    // 
    // TemperatureProbe_Metadata::__schema__
    // 
    const char * TemperatureProbe_Metadata::__schema__ =
    "<?xml version='1.0' encoding='UTF-8' ?>"
    "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
    " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
    " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
    " elementFormDefault='qualified'"
    " version='1.0'>"
    "<xsd:element name='probeMetadata' type='OASIS.HardwareProbes.TemperatureProbe' />"
    "<xsd:complexType name='OASIS.HardwareProbes.TemperatureProbe'>"
    "<xsd:sequence>"
    "<xsd:element name='temperatureCelcius' type='xsd:float'  />"
    "</xsd:sequence>"
    "</xsd:complexType>"
    "</xsd:schema>";

    // 
    // TemperatureProbe_Metadata
    // 
    TemperatureProbe_Metadata::TemperatureProbe_Metadata (void)
    : ::OASIS::Software_Probe_Metadata (
      "80E7579C-4BAB-4BC5-8502-F91FD038E24D",
      "OASIS.HardwareProbes.TemperatureProbe",
      1,
      0,
      __schema__)
    {
    }


    // 
    // TemperatureProbe_Metadata
    // 
    TemperatureProbe_Metadata::TemperatureProbe_Metadata (const char * uuid,
                                                          const char * type_info,
                                                          ACE_UINT8 version_major,
                                                          ACE_UINT8 version_minor,
                                                          const char * schema)
    : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
    {
    }


    // 
    // ~TemperatureProbe_Metadata
    // 
    TemperatureProbe_Metadata::~TemperatureProbe_Metadata (void) 
    {
    }
  }
}

