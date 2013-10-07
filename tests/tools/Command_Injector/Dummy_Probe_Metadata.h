// -*- C++ -*-

//============================================================================
/**
 * @file        Dummy_Probe_Metadata.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _DUMMY_PROBE_METADATA_H_
#define _DUMMY_PROBE_METADATA_H_

#include "oasis/probes/Software_Probe_Metadata.h"

/**
 * @class Dummy_Probe_Metadata
 */
class Dummy_Probe_Metadata :
  public ::OASIS::Software_Probe_Metadata 
{
  public:
  /// Default constructor
  Dummy_Probe_Metadata (void);

  /// Destructor
  virtual ~Dummy_Probe_Metadata (void);

  protected:
  /// Initalizing constructor
  Dummy_Probe_Metadata (const char * uuid,
                        const char * type_info,
                        ACE_UINT8 version_major,
                        ACE_UINT8 version_minor,
                        const char * schema);

  private:
  /// The metadata's schema
  static const char * __schema__;
};

#endif  // !defined __DUMMY_PROBE_METADATA_H__

