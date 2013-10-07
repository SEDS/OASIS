<#ftl attributes=
{
  "phase":2,
  "capability":"GenerateBridge",
  "instanceTags":"MWC_FILES",
  "appliesTo":"ObjectModelNode"
} />
<#assign appName = CG.component.name + "-v" + CG.component.version?replace (".", "_")  />
<#assign mwcFile = "${appName}.mwc" />

<#assign CG_LOCATION = "." />
<#assign CG_FILENAME = "${mwcFile}" />
// -*- MPC -*-
// $Id: softwareProbeBridge.mwc.ftl 1994 2011-10-10 06:10:26Z hillj $

workspace (${appName}) {
  cmdline += -include $OASIS_ROOT/MPC/config

  ${appName}.mpc
}
