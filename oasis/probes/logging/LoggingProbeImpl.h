// -*- C++ -*-

//============================================================================
/**
 * @file        LoggingProbeImpl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _LOGGINGPROBEIMPL_H_
#define _LOGGINGPROBEIMPL_H_

#include "oasis/probes/Data_Types.h"
#include "LoggingProbe_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

#include "LoggingProbe_stub_export.h"

namespace OASIS
{
  /**
   * @class LoggingProbeImpl
   */
  class OASIS_LOGGINGPROBE_STUB_Export LoggingProbeImpl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::OASIS::LoggingProbe_Metadata __metadata__;

    /// Default constructor
    LoggingProbeImpl (void);

    /// Destructor
    virtual ~LoggingProbeImpl (void);

    /// Getter for the probe's metadata
    virtual const ::OASIS::LoggingProbe_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);


    public:
    // Setter and getter methods for severity
    void severity (ACE_INT32 severity);
    ACE_INT32 severity (void) const;

    // Setter and getter methods for thread_id
    void thread_id (ACE_INT32 thread_id);
    ACE_INT32 thread_id (void) const;

    // Setter and getter methods for message
    void message (const ACE_CString & message);
    const ACE_CString & message (void) const;

    protected:
    ACE_INT32 severity_;

    ACE_INT32 thread_id_;

    ACE_CString message_;
  };
}

#endif  // !defined __LOGGINGPROBEIMPL_H__

