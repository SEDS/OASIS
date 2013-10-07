// $Id: Software_Probe_Bridge_Manager.cpp 2134 2012-02-15 18:32:19Z dfeiock $

#include "Software_Probe_Bridge_Manager.h"

#include "OASIS/Foo_Bridge.h"

namespace FooBridge_v1_1
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
    factories.bind ("OASIS.Foo", &::OASIS::Foo_Bridge::_create);
    return 0;
  }
}

OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_IMPL (FooBridge_v1_1::Software_Probe_Bridge_Manager);
