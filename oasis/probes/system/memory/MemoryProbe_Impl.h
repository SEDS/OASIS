// -*- C++ -*-

//============================================================================
/**
 * @file        MemoryProbe_Impl.h
 *
 * $Id: MemoryProbe_Impl.h 2211 2012-07-25 12:55:51Z dfeiock $
 *
 * @author      Harold Owens II (owensh at cs dot iupui dot edu)
 *
 */
//============================================================================

#ifndef _MEMORYPROBE_IMPL_
#define _MEMORYPROBE_IMPL_

#include "MemoryProbeImpl.h"
#include "MemoryProbe_Impl_export.h"
#include "oasis/probes/Software_Probe_Factory_T.h"

namespace OASIS
{
namespace System
{
namespace Memory
{

  // Forward decl.
  class Meminfo_Parser;

/**
 * @class MemoryProbe_Impl
 *
 * Implementation of the memory probe. Depending on the operating
 * system, the probe is implemented differently. For example, the
 * Windows version used Win32 API; whereas, the Linux version collects
 * its information from /proc/meminfo.
 */
class MEMORYPROBE_IMPL_Export MemoryProbe_Impl :
#if defined (_WIN32)
  public ::OASIS::System::Memory::WindowsMemoryProbeImpl
#else
  public ::OASIS::System::Memory::LinuxMemoryProbeImpl
#endif
{
public:
  /// Default constructor
  MemoryProbe_Impl (void);

  /// Destructor
  virtual ~MemoryProbe_Impl (void);

  /// Collect a new set of data.
  virtual int handle_collect_data (void);

#if !defined (_WIN32)
private:
  /// Parser for extracting information from /proc/meminfo.
  ACE_Auto_Ptr <Meminfo_Parser> parser_;
#endif
};

/// Type definition for the software probe's factory
typedef
 ::OASIS::Software_Probe_Factory_T <MemoryProbe_Impl>
 MemoryProbe_Impl_Factory;

/// Export the interface for the software probe factory.
OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_DECL (MEMORYPROBE_IMPL_Export,
                                          create_OASIS_System_Memory_MemoryProbe_Impl_Factory);
}
}
}
#endif  // !defined _MEMORYPROBE_IMPL_
