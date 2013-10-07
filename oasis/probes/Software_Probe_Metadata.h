// -*- C++ -*-

//=============================================================================
/**
 * @file        Software_Probe_Metadata.h
 *
 * $Id: Software_Probe_Metadata.h 2235 2013-02-06 20:18:09Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_SOFTWARE_PROBE_METADATA_H_
#define _OASIS_SOFTWARE_PROBE_METADATA_H_

#include "ace/UUID.h"
#include "SoftwareProbe_Core_export.h"
#include "oasis/config.h"

namespace OASIS
{

/**
 * @struct Software_Probe_Metadata
 *
 * The metadata for a software probe. All the information below
 * is required for each software probe.
 */
class OASIS_SOFTWAREPROBE_CORE_Export Software_Probe_Metadata
{
public:
  /// Initializing constructor.
  Software_Probe_Metadata (const char * uuid,
                           const char * type_info,
                           ACE_UINT8 version_major,
                           ACE_UINT8 version_minor,
                           const char * schema);

  /// Unique id for the software probe.
  ACE_Utils::UUID uuid_;

  /// Unique typename for the software probe.
  ACE_CString type_info_;

  /// Version major number.
  ACE_UINT8 version_major_;

  /// Version minor number.
  ACE_UINT8 version_minor_;

  /// Schema definition for the software probe.
  ACE_CString schema_;
};

}

#if defined (__OASIS_INLINE__)
#include "Software_Probe_Metadata.inl"
#endif

#endif
