// -*- C++ -*-

//============================================================================
/**
 * @file        vector.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "oasis/probes/Data_Types.h"
#include "oasis/probes/Software_Probe.h"
#include "vector_Metadata.h"
#include <iostream>

namespace OASIS
{
  /**
   * @class Int16_Vector_Probe
   */
  class Int16_Vector_Probe :
    public virtual ::OASIS::Software_Probe 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::OASIS::Int16_Vector_Probe_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    Int16_Vector_Probe (void);

    /// Destructor
    virtual ~Int16_Vector_Probe (void);

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
    std::vector < ACE_INT16 > & value (void);
    const std::vector < ACE_INT16 > & value (void) const;

    protected:
    std::vector < ACE_INT16 > value_;
  };
}

#endif  // !defined __VECTOR_H__

