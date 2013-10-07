// -*- C++ -*-

//============================================================================
/**
 * @file        FooImpl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _FOOIMPL_H_
#define _FOOIMPL_H_

#include "oasis/probes/Data_Types.h"
#include "Foo_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

namespace OASIS
{
  /**
   * @class FooImpl
   */
  class FooImpl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::OASIS::Foo_Metadata __metadata__;

    /// Default constructor
    FooImpl (void);

    /// Destructor
    virtual ~FooImpl (void);

    /// Getter for the probe's metadata
    virtual const ::OASIS::Foo_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);
  };
}

#endif  // !defined __FOOIMPL_H__

