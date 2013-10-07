// $Id: Software_Probe_Bridge_Manager.cpp 2135 2012-02-16 15:39:18Z dfeiock $

#include "Software_Probe_Bridge_Manager.h"
#include "Software_Probe_Bridge.h"

#include "oasis/probes/Software_Probe.h"

#include "boost/bind.hpp"
#include <algorithm>

namespace OASIS
{

//
// Software_Probe_Bridge_Manager
//
Software_Probe_Bridge_Manager::Software_Probe_Bridge_Manager (void)
{

}

//
// Software_Probe_Bridge_Manager
//
Software_Probe_Bridge_Manager::~Software_Probe_Bridge_Manager (void)
{

}

//
// release
//
void Software_Probe_Bridge_Manager::release (void)
{
  delete this;
}

//
// register_factories
//
int
Software_Probe_Bridge_Manager::
register_factories (::OASIS::TENA_Bridge::Bridge_Factories & factories)
{
  return 0;
}

}
