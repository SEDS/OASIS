// -*- C++ -*-

//============================================================================
/**
 * @file        complex_Metadata.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _COMPLEX_METADATA_H_
#define _COMPLEX_METADATA_H_

#include "oasis/probes/Software_Probe_Metadata.h"

namespace OASIS
{
  /**
   * @class ComplexSoftwareProbe_Metadata
   */
  class ComplexSoftwareProbe_Metadata :
    public ::OASIS::Software_Probe_Metadata 
  {
    public:
    /// Default constructor
    ComplexSoftwareProbe_Metadata (void);

    /// Destructor
    virtual ~ComplexSoftwareProbe_Metadata (void);

    protected:
    /// Initalizing constructor
    ComplexSoftwareProbe_Metadata (const char * uuid,
                                   const char * type_info,
                                   ACE_UINT8 version_major,
                                   ACE_UINT8 version_minor,
                                   const char * schema);

    private:
    /// The metadata's schema
    static const char * __schema__;
  };
}

#endif  // !defined __COMPLEX_METADATA_H__

