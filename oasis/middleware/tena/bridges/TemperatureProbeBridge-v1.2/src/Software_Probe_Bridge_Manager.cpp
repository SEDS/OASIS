// $Id: Software_Probe_Bridge_Manager.cpp 2134 2012-02-15 18:32:19Z dfeiock $

#include "Software_Probe_Bridge_Manager.h"

#include "OASIS/HardwareProbes/HardwareProbe_Bridge.h"
#include "OASIS/HardwareProbes/TemperatureProbe_Bridge.h"

namespace TemperatureProbeBridge_v1_2
{
  //
  // Software_Probe_Bridge_Manager
  //
  Software_Probe_Bridge_Manager::Software_Probe_Bridge_Manager (void)
  {

  }

  //
  // ~Software_Probe_Bridge_Manager
  //
  Software_Probe_Bridge_Manager::~Software_Probe_Bridge_Manager (void)
  {

  }

  //
  // register_factories
  //
  int Software_Probe_Bridge_Manager::register_factories (::OASIS::TENA_Bridge::Bridge_Factories & factories)
  {
    factories.bind ("OASIS.HardwareProbes.HardwareProbe", &::OASIS::HardwareProbes::HardwareProbe_Bridge::_create);
    factories.bind ("OASIS.HardwareProbes.TemperatureProbe", &::OASIS::HardwareProbes::TemperatureProbe_Bridge::_create);
    return 0;
  }
}

OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_IMPL (TemperatureProbeBridge_v1_2::Software_Probe_Bridge_Manager);
