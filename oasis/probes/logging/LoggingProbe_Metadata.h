// -*- C++ -*-

//============================================================================
/**
 * @file        LoggingProbe_Metadata.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _LOGGINGPROBE_METADATA_H_
#define _LOGGINGPROBE_METADATA_H_

#include "oasis/probes/Software_Probe_Metadata.h"

#include "LoggingProbe_stub_export.h"

namespace OASIS
{
  /**
   * @class LoggingProbe_Metadata
   */
  class OASIS_LOGGINGPROBE_STUB_Export LoggingProbe_Metadata :
    public ::OASIS::Software_Probe_Metadata 
  {
    public:
    /// Default constructor
    LoggingProbe_Metadata (void);

    /// Destructor
    virtual ~LoggingProbe_Metadata (void);

    protected:
    /// Initalizing constructor
    LoggingProbe_Metadata (const char * uuid,
                           const char * type_info,
                           ACE_UINT8 version_major,
                           ACE_UINT8 version_minor,
                           const char * schema);

    private:
    /// The metadata's schema
    static const char * __schema__;
  };
}

#endif  // !defined __LOGGINGPROBE_METADATA_H__

