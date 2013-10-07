// $Id$

#include "ProcessorProbe_Metadata.h"

namespace OASIS
{
  namespace System
  {
    namespace Processor
    {
      // 
      // ProcessorProbe_Metadata::__schema__
      // 
      const char * ProcessorProbe_Metadata::__schema__ =
      "<?xml version='1.0' encoding='UTF-8' ?>"
      "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
      " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
      " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
      " elementFormDefault='qualified'"
      " version='1.0'>"
      "<xsd:element name='probeMetadata' type='OASIS.System.Processor.ProcessorProbe' />"
      "<xsd:complexType name='OASIS.System.Processor.ProcessorProbe'>"
      "<xsd:sequence>"
      "<xsd:element name='idle_time' type='xsd:unsignedLong'  />"
      "<xsd:element name='system_time' type='xsd:unsignedLong'  />"
      "<xsd:element name='user_time' type='xsd:unsignedLong'  />"
      "</xsd:sequence>"
      "</xsd:complexType>"
      "</xsd:schema>";

      // 
      // ProcessorProbe_Metadata
      // 
      ProcessorProbe_Metadata::ProcessorProbe_Metadata (void)
      : ::OASIS::Software_Probe_Metadata (
        "7C3944F1-2176-4EAA-911C-EF5423A7E02D",
        "OASIS.System.Processor.ProcessorProbe",
        1,
        0,
        __schema__)
      {
      }


      // 
      // ProcessorProbe_Metadata
      // 
      ProcessorProbe_Metadata::ProcessorProbe_Metadata (const char * uuid,
                                                        const char * type_info,
                                                        ACE_UINT8 version_major,
                                                        ACE_UINT8 version_minor,
                                                        const char * schema)
      : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
      {
      }


      // 
      // ~ProcessorProbe_Metadata
      // 
      ProcessorProbe_Metadata::~ProcessorProbe_Metadata (void) 
      {
      }

      // 
      // LinuxProcessorProbe_Metadata::__schema__
      // 
      const char * LinuxProcessorProbe_Metadata::__schema__ =
      "<?xml version='1.0' encoding='UTF-8' ?>"
      "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
      " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
      " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
      " elementFormDefault='qualified'"
      " version='1.0'>"
      "<xsd:element name='probeMetadata' type='OASIS.System.Processor.LinuxProcessorProbe' />"
      "<xsd:complexType name='OASIS.System.Processor.LinuxProcessorProbe'>"
      "<xsd:complexContent>"
      "<xsd:extension base='OASIS.System.Processor.ProcessorProbe'>"
      "<xsd:sequence>"
      "<xsd:element name='nice_time' type='xsd:unsignedLong'  />"
      "<xsd:element name='iowait_time' type='xsd:unsignedLong'  />"
      "<xsd:element name='irq_time' type='xsd:unsignedLong'  />"
      "<xsd:element name='soft_irq_time' type='xsd:unsignedLong'  />"
      "</xsd:sequence>"
      "</xsd:extension>"
      "</xsd:complexContent>"
      "</xsd:complexType>"
      "<xsd:complexType name='OASIS.System.Processor.ProcessorProbe'>"
      "<xsd:sequence>"
      "<xsd:element name='idle_time' type='xsd:unsignedLong'  />"
      "<xsd:element name='system_time' type='xsd:unsignedLong'  />"
      "<xsd:element name='user_time' type='xsd:unsignedLong'  />"
      "</xsd:sequence>"
      "</xsd:complexType>"
      "</xsd:schema>";

      // 
      // LinuxProcessorProbe_Metadata
      // 
      LinuxProcessorProbe_Metadata::LinuxProcessorProbe_Metadata (void)
      : ::OASIS::System::Processor::ProcessorProbe_Metadata (
        "B049990B-17AA-4CA2-8806-E89329963788",
        "OASIS.System.Processor.LinuxProcessorProbe",
        1,
        0,
        __schema__)
      {
      }


      // 
      // LinuxProcessorProbe_Metadata
      // 
      LinuxProcessorProbe_Metadata::LinuxProcessorProbe_Metadata (const char * uuid,
                                                                  const char * type_info,
                                                                  ACE_UINT8 version_major,
                                                                  ACE_UINT8 version_minor,
                                                                  const char * schema)
      : ::OASIS::System::Processor::ProcessorProbe_Metadata (uuid, type_info, version_major, version_minor, schema)
      {
      }


      // 
      // ~LinuxProcessorProbe_Metadata
      // 
      LinuxProcessorProbe_Metadata::~LinuxProcessorProbe_Metadata (void) 
      {
      }

      // 
      // WindowsProcessorProbe_Metadata::__schema__
      // 
      const char * WindowsProcessorProbe_Metadata::__schema__ =
      "<?xml version='1.0' encoding='UTF-8' ?>"
      "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
      " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
      " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
      " elementFormDefault='qualified'"
      " version='1.0'>"
      "<xsd:element name='probeMetadata' type='OASIS.System.Processor.WindowsProcessorProbe' />"
      "<xsd:complexType name='OASIS.System.Processor.WindowsProcessorProbe'>"
      "<xsd:complexContent>"
      "<xsd:extension base='OASIS.System.Processor.ProcessorProbe'>"
      "<xsd:sequence>"
      "</xsd:sequence>"
      "</xsd:extension>"
      "</xsd:complexContent>"
      "</xsd:complexType>"
      "<xsd:complexType name='OASIS.System.Processor.ProcessorProbe'>"
      "<xsd:sequence>"
      "<xsd:element name='idle_time' type='xsd:unsignedLong'  />"
      "<xsd:element name='system_time' type='xsd:unsignedLong'  />"
      "<xsd:element name='user_time' type='xsd:unsignedLong'  />"
      "</xsd:sequence>"
      "</xsd:complexType>"
      "</xsd:schema>";

      // 
      // WindowsProcessorProbe_Metadata
      // 
      WindowsProcessorProbe_Metadata::WindowsProcessorProbe_Metadata (void)
      : ::OASIS::System::Processor::ProcessorProbe_Metadata (
        "5F0B088C-5C87-4BE3-B3A4-0177AD169DD5",
        "OASIS.System.Processor.WindowsProcessorProbe",
        1,
        0,
        __schema__)
      {
      }


      // 
      // WindowsProcessorProbe_Metadata
      // 
      WindowsProcessorProbe_Metadata::WindowsProcessorProbe_Metadata (const char * uuid,
                                                                      const char * type_info,
                                                                      ACE_UINT8 version_major,
                                                                      ACE_UINT8 version_minor,
                                                                      const char * schema)
      : ::OASIS::System::Processor::ProcessorProbe_Metadata (uuid, type_info, version_major, version_minor, schema)
      {
      }


      // 
      // ~WindowsProcessorProbe_Metadata
      // 
      WindowsProcessorProbe_Metadata::~WindowsProcessorProbe_Metadata (void) 
      {
      }
    }
  }
}

