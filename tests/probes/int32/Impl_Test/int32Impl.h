// -*- C++ -*-

//============================================================================
/**
 * @file        int32Impl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _INT32IMPL_H_
#define _INT32IMPL_H_

#include "oasis/probes/Data_Types.h"
#include "int32_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

namespace OASIS
{
  /**
   * @class Int32_SoftwareProbeImpl
   */
  class Int32_SoftwareProbeImpl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::OASIS::Int32_SoftwareProbe_Metadata __metadata__;

    /// Default constructor
    Int32_SoftwareProbeImpl (void);

    /// Destructor
    virtual ~Int32_SoftwareProbeImpl (void);

    /// Getter for the probe's metadata
    virtual const ::OASIS::Int32_SoftwareProbe_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);


    public:
    // Setter and getter methods for value
    void value (ACE_INT32 value);
    ACE_INT32 value (void) const;

    protected:
    ACE_INT32 value_;
  };
}

#endif  // !defined __INT32IMPL_H__

