// -*- C++ -*-

//============================================================================
/**
 * @file        complex.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include "oasis/probes/Data_Types.h"
#include "oasis/probes/Software_Probe.h"
#include "complex_Metadata.h"
#include <iostream>

namespace OASIS
{
  /**
   * @struct Point
   */
  struct Point
  {
    ACE_INT32 x;

    ACE_INT32 y;

    /// Stub_Dump method for for ::OASIS::Point
    void dump (std::ostream & output);
  };

  /// Extraction operator for ::OASIS::Point
  bool operator >> (ACE_InputCDR &, const ::OASIS::Point &);

  /**
   * @class ComplexSoftwareProbe
   */
  class ComplexSoftwareProbe :
    public virtual ::OASIS::Software_Probe 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::OASIS::ComplexSoftwareProbe_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    ComplexSoftwareProbe (void);

    /// Destructor
    virtual ~ComplexSoftwareProbe (void);

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


    public:
    // Getter method for value
    ACE_INT64 value (void) const;

    // Getter method for p
    ::OASIS::Point & p (void);
    const ::OASIS::Point & p (void) const;

    protected:
    ACE_INT64 value_;

    ::OASIS::Point p_;
  };
}

#endif  // !defined __COMPLEX_H__

