// -*- C++ -*-

//============================================================================
/**
 * @file        ProcessorProbe_Impl.h
 *
 * $Id: ProcessorProbe_Impl.h 2211 2012-07-25 12:55:51Z dfeiock $
 *
 * @author      Harold Owens II (owensh at cs dot iupui dot edu)
 *
 */
//============================================================================

#ifndef _PROCESSORPROBE_IMPL_H_
#define _PROCESSORPROBE_IMPL_H_

#include "ProcessorProbeImpl.h"
#include "ProcessorProbe_Impl_Export.h"
#include "oasis/probes/Software_Probe_Factory_T.h"

namespace OASIS
{
namespace System
{
namespace Processor
{
// Forward decl.
class Procstat_Parser;

/**
 * @class ProcessorProbe_Impl
 *
 * Implementation of the processor probe. Depending on the operating
 * system, the probe is implemented differently. For example, the
 * Windows version used Win32 API; whereas, the Linux version collects
 * its information from /proc/stat.
 */
class PROCESSORPROBE_IMPL_Export ProcessorProbe_Impl :
#if defined (_WIN32)
  public ::OASIS::System::Processor::WindowsProcessorProbeImpl
#else
  public ::OASIS::System::Processor::LinuxProcessorProbeImpl
#endif
{
  public:

    /// Default constructor
    ProcessorProbe_Impl (void);

    /// Destructor
    virtual ~ProcessorProbe_Impl (void);

    /// Collect a new set of data.
    virtual int handle_collect_data (void);

private:
#if !defined (_WIN32)
  /// Parser for extracting information from /proc/stat.
  ACE_Auto_Ptr <Procstat_Parser> parser_;
#endif
};

/// Type definition for the software probe's factory
typedef
 ::OASIS::Software_Probe_Factory_T <ProcessorProbe_Impl>
 ProcessorProbe_Impl_Factory;

/// Export the interface for the software probe factory.
OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_DECL (PROCESSORPROBE_IMPL_Export,
                                          create_OASIS_System_Processor_ProcessorProbe_Impl_Factory);

}
}
}

#endif  // !defined _PROCESSORPROBE_IMPL_H_
