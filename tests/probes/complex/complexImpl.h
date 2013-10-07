// -*- C++ -*-

//============================================================================
/**
 * @file        complexImpl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _COMPLEXIMPL_H_
#define _COMPLEXIMPL_H_

#include "oasis/probes/Data_Types.h"
#include "complex_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

namespace OASIS
{
  /**
   * @struct PointImpl
   */
  struct PointImpl
  {
    ACE_INT32 x;

    ACE_INT32 y;

    /// Impl_Dump method for for ::OASIS::PointImpl
    void dump (std::ostream & output);
  };

  /// Insertion operator for ::OASIS::PointImpl
  bool operator << (ACE_OutputCDR & out, const ::OASIS::PointImpl &);

  /**
   * @class ComplexSoftwareProbeImpl
   */
  class ComplexSoftwareProbeImpl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::OASIS::ComplexSoftwareProbe_Metadata __metadata__;

    /// Default constructor
    ComplexSoftwareProbeImpl (void);

    /// Destructor
    virtual ~ComplexSoftwareProbeImpl (void);

    /// Getter for the probe's metadata
    virtual const ::OASIS::ComplexSoftwareProbe_Metadata & metadata (void) const;

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

    // Setter and getter methods for p
    void p (const ::OASIS::PointImpl & p);
    ::OASIS::PointImpl & p (void);
    const ::OASIS::PointImpl & p (void) const;

    protected:
    ACE_INT64 value_;

    ::OASIS::PointImpl p_;
  };
}

#endif  // !defined __COMPLEXIMPL_H__

