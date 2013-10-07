<#ftl attributes=
{
  "phase":1,
  "capability":"GenerateBridge",
  "instanceTags":"H_FILES",
  "appliesTo":"ObjectModelNode"
} />
<#assign CG_LOCATION = "src" />
<#assign CG_FILENAME = "Software_Probe_Bridge_Manager.h" />

<#assign appName = CG.component.name + "-v" + CG.component.version  />
<#assign namespaceName = appName?replace (".", "_")?replace ("-", "_") />
<#assign exportMacro = namespaceName?upper_case + "_Export" />

<#assign globalProtectionMacro = "_" + CG.this.objectModelFullName + "_" + CG_FILENAME + "_" />
<#assign globalProtectionMacro = globalProtectionMacro?upper_case?replace (".", "_")?replace ("-", "_") />
// -*- C++ -*-

//=============================================================================
/**
 * @file        Software_Probe_Bridge_Manager.h
 *
 * $Id: softwareProbeBridgeManager.h.ftl 2135 2012-02-16 15:39:18Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef ${globalProtectionMacro}
#define ${globalProtectionMacro}

#include "oasis/middleware/tena/bridges/Software_Probe_Bridge_Manager.h"
#include "${namespaceName}_export.h"

namespace ${namespaceName}
{
  /**
   * @class Software_Probe_Bridge_Manager
   *
   * Software probe bridge manager that is responsible for loading software
   * probe bridges from the ${CG.this.objectModelFullName}
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

OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_DECL (${exportMacro});

#endif  // !defined ${globalProtectionMacro}
