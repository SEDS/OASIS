// $Id: Software_Probe_Bridge_Manager.cpp 2134 2012-02-15 18:32:19Z dfeiock $

#include "Software_Probe_Bridge_Manager.h"

#include "OASIS/System/Memory/MemoryProbe_Bridge.h"
#include "OASIS/System/Memory/LinuxMemoryProbe_Bridge.h"
#include "OASIS/System/Memory/WindowsMemoryProbe_Bridge.h"

namespace MemoryProbeBridge_v1_4
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
    factories.bind ("OASIS.System.Memory.MemoryProbe", &::OASIS::System::Memory::MemoryProbe_Bridge::_create);
    factories.bind ("OASIS.System.Memory.LinuxMemoryProbe", &::OASIS::System::Memory::LinuxMemoryProbe_Bridge::_create);
    factories.bind ("OASIS.System.Memory.WindowsMemoryProbe", &::OASIS::System::Memory::WindowsMemoryProbe_Bridge::_create);
    return 0;
  }
}

OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_IMPL (MemoryProbeBridge_v1_4::Software_Probe_Bridge_Manager);
