// -*- C++ -*-

//=============================================================================
/**
 * @file        Software_Probe_Instance.h
 *
 * $Id: Software_Probe_Instance.h 2235 2013-02-06 20:18:09Z dfeiock $
 *
 * @author      Dennis Feiock
 */
//=============================================================================

#ifndef _OASIS_SOFTWARE_PROBE_INSTANCE_H_
#define _OASIS_SOFTWARE_PROBE_INSTANCE_H_

#include "ace/UUID.h"
#include "SoftwareProbe_Core_export.h"
#include "oasis/config.h"

namespace OASIS
{

/**
 * @struct Software_Probe_Instance
 *
 * The information necessary to uniquely identify a software probe instance.
 */
class OASIS_SOFTWAREPROBE_CORE_Export Software_Probe_Instance
{
public:
  /// Default constructor.
  Software_Probe_Instance (void);

  /// Initializing constructor.
  Software_Probe_Instance (const char * inst_name,
                           const ACE_Utils::UUID & inst_uuid,
                           const char * inst_type_name,
                           const char * einode_name);

  /// Initializing constructor.
  Software_Probe_Instance (const char * inst_name,
                           const char * inst_uuid,
                           const char * inst_type_name,
                           const char * einode_name);

  /// Name of the software probe.
  ACE_CString inst_name_;

  /// Unique id for the software probe.
  ACE_Utils::UUID inst_uuid_;

  /// Unique typename for the software probe.
  ACE_CString inst_type_name_;

  /// Name of the EINode which the software probe is attached to.
  ACE_CString einode_name_;
};

}

#if defined (__OASIS_INLINE__)
#include "Software_Probe_Instance.inl"
#endif

#endif
