// $Id: Software_Probe_Bridge_Manager.cpp 2134 2012-02-15 18:32:19Z dfeiock $

#include "Software_Probe_Bridge_Manager.h"

#include "OASIS/System/Processor/ProcessorProbe_Bridge.h"
#include "OASIS/System/Processor/LinuxProcessorProbe_Bridge.h"
#include "OASIS/System/Processor/WindowsProcessorProbe_Bridge.h"

namespace ProcessorProbeBridge_v1_0
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
    factories.bind ("OASIS.System.Processor.ProcessorProbe", &::OASIS::System::Processor::ProcessorProbe_Bridge::_create);
    factories.bind ("OASIS.System.Processor.LinuxProcessorProbe", &::OASIS::System::Processor::LinuxProcessorProbe_Bridge::_create);
    factories.bind ("OASIS.System.Processor.WindowsProcessorProbe", &::OASIS::System::Processor::WindowsProcessorProbe_Bridge::_create);
    return 0;
  }
}

OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_IMPL (ProcessorProbeBridge_v1_0::Software_Probe_Bridge_Manager);
