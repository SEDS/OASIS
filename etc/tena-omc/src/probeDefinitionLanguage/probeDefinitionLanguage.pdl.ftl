<#ftl attributes={
  "phase":0,
  "capability":"GeneratePDL",
  "instanceTags":"PDL_FILES",
  "appliesTo":"ObjectModelNode"
} />
<#assign appName = CG.this.objectModelFullName />
<#assign pdlFile = "${appName}.pdl" />
<#assign CG_LOCATION = "." />
<#assign CG_FILENAME = "${pdlFile}" />
<#assign imports = CG.this.imports />
<#list imports as import >
#include "${import}.pdl"
</#list>

<#assign nodes = CG.this.containedNodes />
<#list filter([on.ClassNode], nodes) as node >
<#assign superClasses = node.allSuperclasses />
<#if node.isLocalClass () >
<@openModuleScope node.owner.name />
<@idt/>struct ${node.name.base}
<@generateAttributes node />
<@closeModuleScope node.owner.name />
<#elseif node.isClass () >
  <#if node.hasSuperclass () >
<@openModuleScope node.owner.name />
<@idt/>[uuid(${CG.uuid ()})]
  <#assign superClass = node.superclass />
  <#assign superClassScopedName = CG.scope (superClass.name) />
    <#if superClassScopedName != "OASIS::Middleware::SoftwareProbe" >
<@idt/>probe ${node.name.base} : ::${superClassScopedName}
    <#else>
<@idt/>probe ${node.name.base}
    </#if>
<@generateAttributes node />
<@closeModuleScope node.owner.name />
  </#if>
</#if>
</#list>

<#macro generateAttributes node>
<@idt/>{
<#assign attribs = filterOut(onConstAttribute, node.attributes) />
<#list attribs as attrib >
<@generateAttributeNode attrib />
</#list>
<@idt/>};
</#macro>

<#macro generateAttributeNode attrib>
<#if attrib.type.isString () >
<@idt/>  string ${attrib.ID};
<#elseif attrib.type.isBoolean ()>
<@idt/>  boolean ${attrib.ID}
<#elseif attrib.type.isChar ()>
<@idt/>  int8 ${attrib.ID};
<#elseif attrib.type.isOctet ()>
<@idt/>  uint8 ${attrib.ID};
<#elseif attrib.type.isShort ()>
  <#if attrib.type.isUnsigned ()>
<@idt/>  int16 ${attrib.ID};
  <#else>
<@idt/>  uint16 ${attrib.ID};
  </#if>
<#elseif attrib.type.isLong ()>
  <#if attrib.type.isUnsigned ()>
<@idt/>  int32 ${attrib.ID};
  <#else>
<@idt/>  uint32 ${attrib.ID};
  </#if>
<#elseif attrib.type.isLongLong ()>
  <#if attrib.type.isUnsigned ()>
<@idt/>  int64 ${attrib.ID};
  <#else>
<@idt/>  uint64 ${attrib.ID};
  </#if>
<#elseif attrib.type.isFloat ()>
<@idt/>  real32 ${attrib.ID};
<#elseif attrib.type.isDouble ()>
<@idt/>  real64 ${attrib.ID};
<#else>
<@idt/>  ${attrib.type} ${attrib.ID};
</#if>
</#macro>
