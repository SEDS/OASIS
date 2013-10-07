// -*- C++ -*-

//============================================================================
/**
 * @file        nodataImpl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _NODATAIMPL_H_
#define _NODATAIMPL_H_

#include "oasis/probes/Data_Types.h"
#include "nodata_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

namespace Test
{
  /**
   * @class NoDataProbeImpl
   */
  class NoDataProbeImpl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::Test::NoDataProbe_Metadata __metadata__;

    /// Default constructor
    NoDataProbeImpl (void);

    /// Destructor
    virtual ~NoDataProbeImpl (void);

    /// Getter for the probe's metadata
    virtual const ::Test::NoDataProbe_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);
  };
}

#endif  // !defined __NODATAIMPL_H__

