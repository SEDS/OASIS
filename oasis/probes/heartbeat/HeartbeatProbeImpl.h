// -*- C++ -*-

//============================================================================
/**
 * @file        HeartbeatProbeImpl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _HEARTBEATPROBEIMPL_H_
#define _HEARTBEATPROBEIMPL_H_

#include "oasis/probes/Data_Types.h"
#include "HeartbeatProbe_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

#include "HeartbeatProbe_stub_export.h"

namespace OASIS
{
  /**
   * @class HeartbeatProbeImpl
   */
  class OASIS_HEARTBEATPROBE_STUB_Export HeartbeatProbeImpl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::OASIS::HeartbeatProbe_Metadata __metadata__;

    /// Default constructor
    HeartbeatProbeImpl (void);

    /// Destructor
    virtual ~HeartbeatProbeImpl (void);

    /// Getter for the probe's metadata
    virtual const ::OASIS::HeartbeatProbe_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);
  };
}

#endif  // !defined __HEARTBEATPROBEIMPL_H__

