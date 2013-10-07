// -*- C++ -*-

//============================================================================
/**
 * @file        int32.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _INT32_H_
#define _INT32_H_

#include "oasis/probes/Data_Types.h"
#include "oasis/probes/Software_Probe.h"
#include "int32_Metadata.h"
#include <iostream>

namespace OASIS
{
  /**
   * @class Int32_SoftwareProbe
   */
  class Int32_SoftwareProbe :
    public virtual ::OASIS::Software_Probe 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::OASIS::Int32_SoftwareProbe_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    Int32_SoftwareProbe (void);

    /// Destructor
    virtual ~Int32_SoftwareProbe (void);

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
    ACE_INT32 value (void) const;

    protected:
    ACE_INT32 value_;
  };
}

#endif  // !defined __INT32_H__

