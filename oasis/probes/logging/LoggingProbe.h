// -*- C++ -*-

//============================================================================
/**
 * @file        LoggingProbe.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _LOGGINGPROBE_H_
#define _LOGGINGPROBE_H_

#include "oasis/probes/Data_Types.h"
#include "oasis/probes/Software_Probe.h"
#include "LoggingProbe_Metadata.h"
#include <iostream>

#include "LoggingProbe_stub_export.h"

namespace OASIS
{
  /**
   * @class LoggingProbe
   */
  class OASIS_LOGGINGPROBE_STUB_Export LoggingProbe :
    public virtual ::OASIS::Software_Probe 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::OASIS::LoggingProbe_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    LoggingProbe (void);

    /// Destructor
    virtual ~LoggingProbe (void);

    /// Getter for the probe's metadata
    virtual const METADATA_TYPE & metadata (void) const;

    public:
    /// Recall the software probe's data.
    virtual int recall (const char * data, size_t length, int byte_order);

    protected:
    /// Helper method for recalling the data.
    int recall (ACE_InputCDR & input);

    public:
    /// Stub_Dump the software probe's data.
    virtual void dump (std::ostream & output);


    public:
    // Getter method for severity
    ACE_INT32 severity (void) const;

    // Getter method for thread_id
    ACE_INT32 thread_id (void) const;

    // Getter method for message
    const ACE_CString & message (void) const;

    protected:
    ACE_INT32 severity_;

    ACE_INT32 thread_id_;

    ACE_CString message_;
  };
}

#endif  // !defined __LOGGINGPROBE_H__

