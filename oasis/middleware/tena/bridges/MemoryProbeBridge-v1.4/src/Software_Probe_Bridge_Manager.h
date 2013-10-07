// -*- C++ -*-

//=============================================================================
/**
 * @file        Software_Probe_Bridge_Manager.h
 *
 * $Id: Software_Probe_Bridge_Manager.h 2135 2012-02-16 15:39:18Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_MEMORYPROBE_V1_4_SOFTWARE_PROBE_BRIDGE_MANAGER_H_
#define _OASIS_MEMORYPROBE_V1_4_SOFTWARE_PROBE_BRIDGE_MANAGER_H_

#include "oasis/middleware/tena/bridges/Software_Probe_Bridge_Manager.h"
#include "MemoryProbeBridge_v1_4_export.h"

namespace MemoryProbeBridge_v1_4
{
  /**
   * @class Software_Probe_Bridge_Manager
   *
   * Software probe bridge manager that is responsible for loading software
   * probe bridges from the OASIS-MemoryProbe-v1.4
   * object model.
   */
  class Software_Probe_Bridge_Manager :
    public ::OASIS::Software_Probe_Bridge_Manager
  {
  public:
    /// Default constructor.
    Software_Probe_Bridge_Manager (void);

    /// Destructor.
    virtual ~Software_Probe_Bridge_Manager (void);

    /// Register bridge factories to the provided Bridge_Factories
    virtual int register_factories (::OASIS::TENA_Bridge::Bridge_Factories & factories);
  };
}

OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_DECL (MEMORYPROBEBRIDGE_V1_4_Export);

#endif  // !defined _OASIS_MEMORYPROBE_V1_4_SOFTWARE_PROBE_BRIDGE_MANAGER_H_
