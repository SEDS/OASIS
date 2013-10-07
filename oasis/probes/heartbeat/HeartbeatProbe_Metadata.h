// -*- C++ -*-

//============================================================================
/**
 * @file        HeartbeatProbe_Metadata.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _HEARTBEATPROBE_METADATA_H_
#define _HEARTBEATPROBE_METADATA_H_

#include "oasis/probes/Software_Probe_Metadata.h"

#include "HeartbeatProbe_stub_export.h"

namespace OASIS
{
  /**
   * @class HeartbeatProbe_Metadata
   */
  class OASIS_HEARTBEATPROBE_STUB_Export HeartbeatProbe_Metadata :
    public ::OASIS::Software_Probe_Metadata 
  {
    public:
    /// Default constructor
    HeartbeatProbe_Metadata (void);

    /// Destructor
    virtual ~HeartbeatProbe_Metadata (void);

    protected:
    /// Initalizing constructor
    HeartbeatProbe_Metadata (const char * uuid,
                             const char * type_info,
                             ACE_UINT8 version_major,
                             ACE_UINT8 version_minor,
                             const char * schema);

    private:
    /// The metadata's schema
    static const char * __schema__;
  };
}

#endif  // !defined __HEARTBEATPROBE_METADATA_H__

