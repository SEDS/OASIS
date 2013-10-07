<#ftl attributes=
{
  "phase":2,
  "capability":"GenerateBridge",
  "instanceTags":"MPC_FILES",
  "appliesTo":"ObjectModelNode"
} />
<#assign appName = CG.component.name + "-v" + CG.component.version?replace (".", "_")  />
<#assign mpcFile = "${appName}.mpc" />

<#assign namespaceName = appName?replace ("-", "_") />
<#assign exportBuildFlag = namespaceName?upper_case />

<#assign importedOMs = CG.this.importedObjectModels />
<#assign softwareProbeVersion = "0.1" />

<#list importedOMs as importedOM >
  <#if importedOM.objectModelBaseName == "OASIS-SoftwareProbe" >
    <#assign softwareProbeVersion = importedOM.objectModelVersion />
  </#if>
</#list>

<#assign CG_LOCATION = "." />
<#assign CG_FILENAME = "${mpcFile}" />
// -*- MPC -*-
// $Id: softwareProbeBridge.mpc.ftl 1994 2011-10-10 06:10:26Z hillj $

project (${appName}) : oasis_tena_softwareprobe_bridge, oasis_tena_softwareprobe_v${softwareProbeVersion?replace (".", "_")} {
  sharedname    = ${appName}
  dynamicflags += ${exportBuildFlag}_BUILD_DLL ${exportBuildFlag}_HAS_DLL

  // For some strange reason, this macro keeps creeping into the project build
  // specification -- even when we have disable_versioned_namespace as the 
  // last base project. So, we are just going to manually remove this macro
  // from the build specification!
  macros -= ACE_HAS_VERSIONED_NAMESPACE=1

  includes += ./src \
              $(TENA_HOME)/$(TENA_VERSION)/include/OMs/${CG.objectModelFullName} \
<#list importedOMs as importedOM >
              $(TENA_HOME)/$(TENA_VERSION)/include/OMs/${importedOM.objectModelFullName}<#if importedOM_has_next> \</#if>
</#list>

  specific (prop:windows) {
    lit_libs += lib${CG.objectModelFullName}-$(TENA_PLATFORM)-v$(TENA_VERSION) \
<#list importedOMs as importedOM >
                lib${importedOM.objectModelFullName}-$(TENA_PLATFORM)-v$(TENA_VERSION)<#if importedOM_has_next> \</#if>
</#list>
  } else {
    lit_libs += ${CG.objectModelFullName}-$(TENA_PLATFORM)-v$(TENA_VERSION) \
<#list importedOMs as importedOM >
                ${importedOM.objectModelFullName}-$(TENA_PLATFORM)-v$(TENA_VERSION)<#if importedOM_has_next> \</#if>
</#list>
  }

  Source_Files {
<#assign cppFiles = CG.instances ("CPP_FILES") />
<#list cppFiles as cppFile >
    ${cppFile.path}
</#list>
  }
}
