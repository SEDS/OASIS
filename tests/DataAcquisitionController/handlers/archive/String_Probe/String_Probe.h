// -*- C++ -*-

//============================================================================
/**
 * @file        String_Probe.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _STRING_PROBE_H_
#define _STRING_PROBE_H_

#include "oasis/probes/Data_Types.h"
#include "oasis/probes/Software_Probe.h"
#include "String_Probe_Metadata.h"
#include <iostream>

namespace Test
{
  /**
   * @class String_Probe
   */
  class String_Probe :
    public virtual ::OASIS::Software_Probe 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::Test::String_Probe_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    String_Probe (void);

    /// Destructor
    virtual ~String_Probe (void);

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
    // Getter method for str_value
    const ACE_CString & str_value (void) const;

    protected:
    ACE_CString str_value_;
  };
}

#endif  // !defined __STRING_PROBE_H__

