// -*- C++ -*-

//============================================================================
/**
 * @file        int8Impl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _INT8IMPL_H_
#define _INT8IMPL_H_

#include "oasis/probes/Data_Types.h"
#include "int8_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

namespace OASIS
{
  /**
   * @class Int8_SoftwareProbeImpl
   */
  class Int8_SoftwareProbeImpl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::OASIS::Int8_SoftwareProbe_Metadata __metadata__;

    /// Default constructor
    Int8_SoftwareProbeImpl (void);

    /// Destructor
    virtual ~Int8_SoftwareProbeImpl (void);

    /// Getter for the probe's metadata
    virtual const ::OASIS::Int8_SoftwareProbe_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);


    public:
    // Setter and getter methods for value
    void value (ACE_INT8 value);
    ACE_INT8 value (void) const;

    protected:
    char value_;
  };
}

#endif  // !defined __INT8IMPL_H__

