// $Id: Software_Probe_Bridge_Manager.cpp 2134 2012-02-15 18:32:19Z dfeiock $

#include "Software_Probe_Bridge_Manager.h"

#include "OASIS/System/Network/NetworkProbe_Bridge.h"
#include "OASIS/System/Network/LinuxNetworkProbe_Bridge.h"
#include "OASIS/System/Network/WindowsNetworkProbe_Bridge.h"

namespace NetworkProbeBridge_v1_1
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
    factories.bind ("OASIS.System.Network.NetworkProbe", &::OASIS::System::Network::NetworkProbe_Bridge::_create);
    factories.bind ("OASIS.System.Network.LinuxNetworkProbe", &::OASIS::System::Network::LinuxNetworkProbe_Bridge::_create);
    factories.bind ("OASIS.System.Network.WindowsNetworkProbe", &::OASIS::System::Network::WindowsNetworkProbe_Bridge::_create);
    return 0;
  }
}

OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_IMPL (NetworkProbeBridge_v1_1::Software_Probe_Bridge_Manager);
