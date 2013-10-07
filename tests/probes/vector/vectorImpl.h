// -*- C++ -*-

//============================================================================
/**
 * @file        vectorImpl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _VECTORIMPL_H_
#define _VECTORIMPL_H_

#include "oasis/probes/Data_Types.h"
#include "vector_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

namespace OASIS
{
  /**
   * @class Int16_Vector_ProbeImpl
   */
  class Int16_Vector_ProbeImpl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::OASIS::Int16_Vector_Probe_Metadata __metadata__;

    /// Default constructor
    Int16_Vector_ProbeImpl (void);

    /// Destructor
    virtual ~Int16_Vector_ProbeImpl (void);

    /// Getter for the probe's metadata
    virtual const ::OASIS::Int16_Vector_Probe_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);


    public:
    // Setter and getter methods for value
    void value (const std::vector < ACE_INT16 > & value);
    std::vector < ACE_INT16 > & value (void);
    const std::vector < ACE_INT16 > & value (void) const;

    protected:
    std::vector < ACE_INT16 > value_;
  };
}

#endif  // !defined __VECTORIMPL_H__

