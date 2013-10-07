// -*- C++ -*-

//============================================================================
/**
 * @file        HeartbeatProbe.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _HEARTBEATPROBE_H_
#define _HEARTBEATPROBE_H_

#include "oasis/probes/Data_Types.h"
#include "oasis/probes/Software_Probe.h"
#include "HeartbeatProbe_Metadata.h"
#include <iostream>

#include "HeartbeatProbe_stub_export.h"

namespace OASIS
{
  /**
   * @class HeartbeatProbe
   */
  class OASIS_HEARTBEATPROBE_STUB_Export HeartbeatProbe :
    public virtual ::OASIS::Software_Probe 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::OASIS::HeartbeatProbe_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    HeartbeatProbe (void);

    /// Destructor
    virtual ~HeartbeatProbe (void);

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
  };
}

#endif  // !defined __HEARTBEATPROBE_H__

