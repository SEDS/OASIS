// -*- C++ -*-

//============================================================================
/**
 * @file        HeartbeatProbe_Impl.h
 *
 * $Id: HeartbeatProbe_Impl.h 2211 2012-07-25 12:55:51Z dfeiock $
 *
 * @author      James H. Hill
 *
 */
//============================================================================

#ifndef _OASIS_HEARTBEART_PROBE_IMPL_H_
#define _OASIS_HEARTBEART_PROBE_IMPL_H_

#include "HeartbeatProbeImpl.h"
#include "HeartbeatProbe_Impl_export.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include "oasis/probes/Software_Probe_Factory_T.h"

namespace OASIS
{

/// Type definition for the software probe's factory
typedef ::OASIS::Software_Probe_Factory_T <
  HeartbeatProbeImpl>
  HeartbeatProbe_Impl_Factory;

}

OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_DECL (HEARTBEATPROBE_IMPL_Export,
                                          create_OASIS_HeartbeatProbe_Impl_Factory);

#endif  // !defined _OASIS_HEARTBEART_PROBE_IMPL_H_
