// $Id$

#include "MemoryProbe_Metadata.h"

namespace OASIS
{
  namespace System
  {
    namespace Memory
    {
      // 
      // MemoryProbe_Metadata::__schema__
      // 
      const char * MemoryProbe_Metadata::__schema__ =
      "<?xml version='1.0' encoding='UTF-8' ?>"
      "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
      " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
      " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
      " elementFormDefault='qualified'"
      " version='1.0'>"
      "<xsd:element name='probeMetadata' type='OASIS.System.Memory.MemoryProbe' />"
      "<xsd:complexType name='OASIS.System.Memory.MemoryProbe'>"
      "<xsd:sequence>"
      "<xsd:element name='physical_memory_avail' type='xsd:unsignedLong'  />"
      "<xsd:element name='physical_memory_total' type='xsd:unsignedLong'  />"
      "<xsd:element name='system_cache' type='xsd:unsignedLong'  />"
      "<xsd:element name='commit_limit' type='xsd:unsignedLong'  />"
      "<xsd:element name='commit_total' type='xsd:unsignedLong'  />"
      "<xsd:element name='virtual_total' type='xsd:unsignedLong'  />"
      "<xsd:element name='virtual_used' type='xsd:unsignedLong'  />"
      "</xsd:sequence>"
      "</xsd:complexType>"
      "</xsd:schema>";

      // 
      // MemoryProbe_Metadata
      // 
      MemoryProbe_Metadata::MemoryProbe_Metadata (void)
      : ::OASIS::Software_Probe_Metadata (
        "ED970279-247D-42CA-AEAA-BEF0239CA3B3",
        "OASIS.System.Memory.MemoryProbe",
        1,
        1,
        __schema__)
      {
      }


      // 
      // MemoryProbe_Metadata
      // 
      MemoryProbe_Metadata::MemoryProbe_Metadata (const char * uuid,
                                                  const char * type_info,
                                                  ACE_UINT8 version_major,
                                                  ACE_UINT8 version_minor,
                                                  const char * schema)
      : ::OASIS::Software_Probe_Metadata (uuid, type_info, version_major, version_minor, schema)
      {
      }


      // 
      // ~MemoryProbe_Metadata
      // 
      MemoryProbe_Metadata::~MemoryProbe_Metadata (void) 
      {
      }

      // 
      // LinuxMemoryProbe_Metadata::__schema__
      // 
      const char * LinuxMemoryProbe_Metadata::__schema__ =
      "<?xml version='1.0' encoding='UTF-8' ?>"
      "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
      " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
      " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
      " elementFormDefault='qualified'"
      " version='1.0'>"
      "<xsd:element name='probeMetadata' type='OASIS.System.Memory.LinuxMemoryProbe' />"
      "<xsd:complexType name='OASIS.System.Memory.LinuxMemoryProbe'>"
      "<xsd:complexContent>"
      "<xsd:extension base='OASIS.System.Memory.MemoryProbe'>"
      "<xsd:sequence>"
      "<xsd:element name='buffers' type='xsd:unsignedLong'  />"
      "<xsd:element name='swap_cache' type='xsd:unsignedLong'  />"
      "<xsd:element name='inactive' type='xsd:unsignedLong'  />"
      "<xsd:element name='active' type='xsd:unsignedLong'  />"
      "<xsd:element name='high_total' type='xsd:unsignedLong'  />"
      "<xsd:element name='high_free' type='xsd:unsignedLong'  />"
      "<xsd:element name='low_total' type='xsd:unsignedLong'  />"
      "<xsd:element name='low_free' type='xsd:unsignedLong'  />"
      "<xsd:element name='swap_total' type='xsd:unsignedLong'  />"
      "<xsd:element name='swap_free' type='xsd:unsignedLong'  />"
      "<xsd:element name='dirty' type='xsd:unsignedLong'  />"
      "<xsd:element name='write_back' type='xsd:unsignedLong'  />"
      "<xsd:element name='virtual_chunk' type='xsd:unsignedLong'  />"
      "</xsd:sequence>"
      "</xsd:extension>"
      "</xsd:complexContent>"
      "</xsd:complexType>"
      "<xsd:complexType name='OASIS.System.Memory.MemoryProbe'>"
      "<xsd:sequence>"
      "<xsd:element name='physical_memory_avail' type='xsd:unsignedLong'  />"
      "<xsd:element name='physical_memory_total' type='xsd:unsignedLong'  />"
      "<xsd:element name='system_cache' type='xsd:unsignedLong'  />"
      "<xsd:element name='commit_limit' type='xsd:unsignedLong'  />"
      "<xsd:element name='commit_total' type='xsd:unsignedLong'  />"
      "<xsd:element name='virtual_total' type='xsd:unsignedLong'  />"
      "<xsd:element name='virtual_used' type='xsd:unsignedLong'  />"
      "</xsd:sequence>"
      "</xsd:complexType>"
      "</xsd:schema>";

      // 
      // LinuxMemoryProbe_Metadata
      // 
      LinuxMemoryProbe_Metadata::LinuxMemoryProbe_Metadata (void)
      : ::OASIS::System::Memory::MemoryProbe_Metadata (
        "81DA0F4B-2712-4A7A-ABE4-F74C80A5C069",
        "OASIS.System.Memory.LinuxMemoryProbe",
        1,
        1,
        __schema__)
      {
      }


      // 
      // LinuxMemoryProbe_Metadata
      // 
      LinuxMemoryProbe_Metadata::LinuxMemoryProbe_Metadata (const char * uuid,
                                                            const char * type_info,
                                                            ACE_UINT8 version_major,
                                                            ACE_UINT8 version_minor,
                                                            const char * schema)
      : ::OASIS::System::Memory::MemoryProbe_Metadata (uuid, type_info, version_major, version_minor, schema)
      {
      }


      // 
      // ~LinuxMemoryProbe_Metadata
      // 
      LinuxMemoryProbe_Metadata::~LinuxMemoryProbe_Metadata (void) 
      {
      }

      // 
      // WindowsMemoryProbe_Metadata::__schema__
      // 
      const char * WindowsMemoryProbe_Metadata::__schema__ =
      "<?xml version='1.0' encoding='UTF-8' ?>"
      "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'"
      " xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'"
      " xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'"
      " elementFormDefault='qualified'"
      " version='1.0'>"
      "<xsd:element name='probeMetadata' type='OASIS.System.Memory.WindowsMemoryProbe' />"
      "<xsd:complexType name='OASIS.System.Memory.WindowsMemoryProbe'>"
      "<xsd:complexContent>"
      "<xsd:extension base='OASIS.System.Memory.MemoryProbe'>"
      "<xsd:sequence>"
      "<xsd:element name='page_file_total' type='xsd:unsignedLong'  />"
      "<xsd:element name='page_file_avail' type='xsd:unsignedLong'  />"
      "<xsd:element name='kernel_total' type='xsd:unsignedLong'  />"
      "<xsd:element name='kernel_paged' type='xsd:unsignedLong'  />"
      "<xsd:element name='kernel_nonpaged' type='xsd:unsignedLong'  />"
      "<xsd:element name='page_size' type='xsd:unsignedLong'  />"
      "<xsd:element name='commit_peak' type='xsd:unsignedLong'  />"
      "</xsd:sequence>"
      "</xsd:extension>"
      "</xsd:complexContent>"
      "</xsd:complexType>"
      "<xsd:complexType name='OASIS.System.Memory.MemoryProbe'>"
      "<xsd:sequence>"
      "<xsd:element name='physical_memory_avail' type='xsd:unsignedLong'  />"
      "<xsd:element name='physical_memory_total' type='xsd:unsignedLong'  />"
      "<xsd:element name='system_cache' type='xsd:unsignedLong'  />"
      "<xsd:element name='commit_limit' type='xsd:unsignedLong'  />"
      "<xsd:element name='commit_total' type='xsd:unsignedLong'  />"
      "<xsd:element name='virtual_total' type='xsd:unsignedLong'  />"
      "<xsd:element name='virtual_used' type='xsd:unsignedLong'  />"
      "</xsd:sequence>"
      "</xsd:complexType>"
      "</xsd:schema>";

      // 
      // WindowsMemoryProbe_Metadata
      // 
      WindowsMemoryProbe_Metadata::WindowsMemoryProbe_Metadata (void)
      : ::OASIS::System::Memory::MemoryProbe_Metadata (
        "C78815F8-4A43-43BE-9E58-FE875E961B7D",
        "OASIS.System.Memory.WindowsMemoryProbe",
        1,
        1,
        __schema__)
      {
      }


      // 
      // WindowsMemoryProbe_Metadata
      // 
      WindowsMemoryProbe_Metadata::WindowsMemoryProbe_Metadata (const char * uuid,
                                                                const char * type_info,
                                                                ACE_UINT8 version_major,
                                                                ACE_UINT8 version_minor,
                                                                const char * schema)
      : ::OASIS::System::Memory::MemoryProbe_Metadata (uuid, type_info, version_major, version_minor, schema)
      {
      }


      // 
      // ~WindowsMemoryProbe_Metadata
      // 
      WindowsMemoryProbe_Metadata::~WindowsMemoryProbe_Metadata (void) 
      {
      }
    }
  }
}

