<#ftl attributes=
{
  "phase":1,
  "capability":"GenerateBridge",
  "instanceTags":"CPP_FILES",
  "appliesTo":"ObjectModelNode"
} />
<#assign CG_LOCATION = "src" />
<#assign CG_FILENAME = "Software_Probe_Bridge_Manager.cpp" />

<#assign appName = CG.component.name + "-v" + CG.component.version  />
<#assign namespaceName = appName?replace (".", "_")?replace ("-", "_") />
// $Id: softwareProbeBridgeManager.cpp.ftl 2104 2012-01-12 19:14:13Z dfeiock $

#include "Software_Probe_Bridge_Manager.h"

<#assign headerFiles = CG.instances ("H_FILES") />
<#list headerFiles as headerFile >
#include "${headerFile.path?replace ("src/", "")}"
</#list>

namespace ${namespaceName}
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
<#list headerFiles as headerFile >
  <#assign scopedName = headerFile.path?replace ("src/", "")?replace ("/", "::")?replace (".h", "") />
  <#assign fullName = scopedName?replace ("::", ".")?replace ("_Bridge", "") />
    factories.bind ("${fullName}", &::${scopedName}::_create);
</#list>
    return 0;
  }
}

OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_IMPL (${namespaceName}::Software_Probe_Bridge_Manager);
