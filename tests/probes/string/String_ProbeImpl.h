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

namespace OASIS
{
  /**
   * @class String_SoftwareProbeImpl
   */
  class String_SoftwareProbeImpl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::OASIS::String_SoftwareProbe_Metadata __metadata__;

    /// Default constructor
    String_SoftwareProbeImpl (void);

    /// Destructor
    virtual ~String_SoftwareProbeImpl (void);

    /// Getter for the probe's metadata
    virtual const ::OASIS::String_SoftwareProbe_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);


    public:
    // Setter and getter methods for value
    void value (const ACE_CString & value);
    const ACE_CString & value (void) const;

    protected:
    ACE_CString value_;
  };
}

#endif  // !defined __STRING_PROBEIMPL_H__

