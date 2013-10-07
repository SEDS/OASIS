// -*- C++ -*-

//============================================================================
/**
 * @file        nodata_Metadata.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _NODATA_METADATA_H_
#define _NODATA_METADATA_H_

#include "oasis/probes/Software_Probe_Metadata.h"

namespace Test
{
  /**
   * @class NoDataProbe_Metadata
   */
  class NoDataProbe_Metadata :
    public ::OASIS::Software_Probe_Metadata 
  {
    public:
    /// Default constructor
    NoDataProbe_Metadata (void);

    /// Destructor
    virtual ~NoDataProbe_Metadata (void);

    protected:
    /// Initalizing constructor
    NoDataProbe_Metadata (const char * uuid,
                          const char * type_info,
                          ACE_UINT8 version_major,
                          ACE_UINT8 version_minor,
                          const char * schema);

    private:
    /// The metadata's schema
    static const char * __schema__;
  };
}

#endif  // !defined __NODATA_METADATA_H__

