// -*- C++ -*-

//============================================================================
/**
 * @file        String_ProbeImpl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _STRING_PROBEIMPL_H_
#define _STRING_PROBEIMPL_H_

#include "oasis/probes/Data_Types.h"
#include "String_Probe_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

namespace Test
{
  /**
   * @class String_ProbeImpl
   */
  class String_ProbeImpl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::Test::String_Probe_Metadata __metadata__;

    /// Default constructor
    String_ProbeImpl (void);

    /// Destructor
    virtual ~String_ProbeImpl (void);

    /// Getter for the probe's metadata
    virtual const ::Test::String_Probe_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);


    public:
    // Setter and getter methods for str_value
    void str_value (const ACE_CString & str_value);
    const ACE_CString & str_value (void) const;

    protected:
    ACE_CString str_value_;
  };
}

#endif  // !defined __STRING_PROBEIMPL_H__

