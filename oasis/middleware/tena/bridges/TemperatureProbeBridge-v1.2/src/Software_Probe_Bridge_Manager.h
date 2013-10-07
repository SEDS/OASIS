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

#ifndef _OASIS_TEMPERATUREPROBE_V1_2_SOFTWARE_PROBE_BRIDGE_MANAGER_H_
#define _OASIS_TEMPERATUREPROBE_V1_2_SOFTWARE_PROBE_BRIDGE_MANAGER_H_

#include "oasis/middleware/tena/bridges/Software_Probe_Bridge_Manager.h"
#include "TemperatureProbeBridge_v1_2_export.h"

namespace TemperatureProbeBridge_v1_2
{
  /**
   * @class Software_Probe_Bridge_Manager
   *
   * Software probe bridge manager that is responsible for loading software
   * probe bridges from the OASIS-TemperatureProbe-v1.2
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

OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_DECL (TEMPERATUREPROBEBRIDGE_V1_2_Export);

#endif  // !defined _OASIS_TEMPERATUREPROBE_V1_2_SOFTWARE_PROBE_BRIDGE_MANAGER_H_
