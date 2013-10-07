// -*- C++ -*-

//============================================================================
/**
 * @file        String_Probe_Metadata.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _STRING_PROBE_METADATA_H_
#define _STRING_PROBE_METADATA_H_

#include "oasis/probes/Software_Probe_Metadata.h"

namespace Test
{
  /**
   * @class String_Probe_Metadata
   */
  class String_Probe_Metadata :
    public ::OASIS::Software_Probe_Metadata 
  {
    public:
    /// Default constructor
    String_Probe_Metadata (void);

    /// Destructor
    virtual ~String_Probe_Metadata (void);

    protected:
    /// Initalizing constructor
    String_Probe_Metadata (const char * uuid,
                           const char * type_info,
                           ACE_UINT8 version_major,
                           ACE_UINT8 version_minor,
                           const char * schema);

    private:
    /// The metadata's schema
    static const char * __schema__;
  };
}

#endif  // !defined __STRING_PROBE_METADATA_H__

