// -*- C++ -*-

//============================================================================
/**
 * @file        vector_Metadata.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _VECTOR_METADATA_H_
#define _VECTOR_METADATA_H_

#include "oasis/probes/Software_Probe_Metadata.h"

namespace OASIS
{
  /**
   * @class Int16_Vector_Probe_Metadata
   */
  class Int16_Vector_Probe_Metadata :
    public ::OASIS::Software_Probe_Metadata 
  {
    public:
    /// Default constructor
    Int16_Vector_Probe_Metadata (void);

    /// Destructor
    virtual ~Int16_Vector_Probe_Metadata (void);

    protected:
    /// Initalizing constructor
    Int16_Vector_Probe_Metadata (const char * uuid,
                                 const char * type_info,
                                 ACE_UINT8 version_major,
                                 ACE_UINT8 version_minor,
                                 const char * schema);

    private:
    /// The metadata's schema
    static const char * __schema__;
  };
}

#endif  // !defined __VECTOR_METADATA_H__

