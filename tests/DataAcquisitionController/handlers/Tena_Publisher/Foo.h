// -*- C++ -*-

//============================================================================
/**
 * @file        Foo.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _FOO_H_
#define _FOO_H_

#include "oasis/probes/Data_Types.h"
#include "oasis/probes/Software_Probe.h"
#include "Foo_Metadata.h"
#include <iostream>

namespace OASIS
{
  /**
   * @class Foo
   */
  class Foo :
    public virtual ::OASIS::Software_Probe 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::OASIS::Foo_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    Foo (void);

    /// Destructor
    virtual ~Foo (void);

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
  };
}

#endif  // !defined __FOO_H__

