// -*- C++ -*-

//============================================================================
/**
 * @file        Foo_Metadata.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _FOO_METADATA_H_
#define _FOO_METADATA_H_

#include "oasis/probes/Software_Probe_Metadata.h"

namespace OASIS
{
  /**
   * @class Foo_Metadata
   */
  class Foo_Metadata :
    public ::OASIS::Software_Probe_Metadata 
  {
    public:
    /// Default constructor
    Foo_Metadata (void);

    /// Destructor
    virtual ~Foo_Metadata (void);

    protected:
    /// Initalizing constructor
    Foo_Metadata (const char * uuid,
                  const char * type_info,
                  ACE_UINT8 version_major,
                  ACE_UINT8 version_minor,
                  const char * schema);

    private:
    /// The metadata's schema
    static const char * __schema__;
  };
}

#endif  // !defined __FOO_METADATA_H__

