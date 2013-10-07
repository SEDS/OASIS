// -*- C++ -*-

//============================================================================
/**
 * @file        int64Impl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _INT64IMPL_H_
#define _INT64IMPL_H_

#include "oasis/probes/Data_Types.h"
#include "int64_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

namespace OASIS
{
  /**
   * @class Int64_SoftwareProbeImpl
   */
  class Int64_SoftwareProbeImpl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::OASIS::Int64_SoftwareProbe_Metadata __metadata__;

    /// Default constructor
    Int64_SoftwareProbeImpl (void);

    /// Destructor
    virtual ~Int64_SoftwareProbeImpl (void);

    /// Getter for the probe's metadata
    virtual const ::OASIS::Int64_SoftwareProbe_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);


    public:
    // Setter and getter methods for value
    void value (ACE_INT64 value);
    ACE_INT64 value (void) const;

    protected:
    ACE_INT64 value_;
  };
}

#endif  // !defined __INT64IMPL_H__

