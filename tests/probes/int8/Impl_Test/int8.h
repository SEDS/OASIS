// -*- C++ -*-

//============================================================================
/**
 * @file        int8.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _INT8_H_
#define _INT8_H_

#include "oasis/probes/Data_Types.h"
#include "oasis/probes/Software_Probe.h"
#include "int8_Metadata.h"
#include <iostream>

namespace OASIS
{
  /**
   * @class Int8_SoftwareProbe
   */
  class Int8_SoftwareProbe :
    public virtual ::OASIS::Software_Probe 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::OASIS::Int8_SoftwareProbe_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    Int8_SoftwareProbe (void);

    /// Destructor
    virtual ~Int8_SoftwareProbe (void);

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
    ACE_INT8 value (void) const;

    protected:
    char value_;
  };
}

#endif  // !defined __INT8_H__

