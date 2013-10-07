<#ftl attributes=
{
  "phase":0,
  "capability":"GenerateBridge",
  "instanceTags":"CPP_FILES",
  "appliesTo":"ClassNode"
} />
<#assign baseName = "${CG.this.name.base}" />
<#assign nameScope = CG.scope(CG.this.name) />
<#assign implName = CG.implNameFor(CG.this.name) />
<#assign implBaseName = "${baseName}_Bridge" />
<#assign implNameScope = CG.scope(implName) />
<#assign implPath = CG.path (CG.this.owner.name) />
<#assign implFile = "${implBaseName}.cpp" />
<#assign hasSuperclass = CG.this.hasSuperclass () />

<#assign CG_LOCATION = "src/" + "${implPath}" />
<#assign CG_FILENAME = "${implFile}" />
// $Id: softwareProbeBridge.cpp.ftl 2211 2012-07-25 12:55:51Z dfeiock $

#include "${implBaseName}.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe.h"
#include "oasis/probes/Software_Probe_Header.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/middleware/tena/bridges/Configuration_Exception.h"

<#if hasSuperclass >
<#assign superClassScopeName = CG.scope (CG.this.superclass.name) />
<#if superClassScopeName != "OASIS::Middleware::SoftwareProbe" >
<#assign superClassPath = CG.path (CG.this.superclass.name) />
#include "${superClassPath}_Bridge.h"
</#if>
</#if>

<@openNameSpace CG.this.owner.name />
<@idt/>//
<@idt/>// _create
<@idt/>//
<@idt/>::OASIS::Software_Probe_Bridge * ${implBaseName}::_create (void)
<@idt/>{
<@idt/>  ::OASIS::Software_Probe_Bridge * bridge = 0;
<@idt/>  ACE_NEW_RETURN (bridge,
<@idt/>                  ${implBaseName} (),
<@idt/>                  0);

<@idt/>  return bridge;
<@idt/>}

<@idt/>//
<@idt/>// ${implBaseName}
<@idt/>//
<@idt/>${implBaseName}::${implBaseName} (void)
<@idt/>{

<@idt/>}

<@idt/>//
<@idt/>// ~${implBaseName}
<@idt/>//
<@idt/>${implBaseName}::~${implBaseName} (void)
<@idt/>{

<@idt/>}

<@idt/>//
<@idt/>// create_servant
<@idt/>//
<@idt/>int ${implBaseName}::
<@idt/>create_servant (const ACE_Utils::UUID & einode,
<@idt/>                const ::OASIS::DAC::Software_Probe_Instance & inst)
<@idt/>{
<@idt/>  // Make sure there is no servant already associated with this // instance.
<@idt/>  if (this->servants_.find (inst.ext_id_.c_str ()) != this->servants_.end ())
<@idt/>    ACE_ERROR_RETURN ((LM_ERROR,
<@idt/>                       ACE_TEXT ("%T (%t) - %M - servant already exist for %s\n"),
<@idt/>                       inst.ext_id_.c_str ()),
<@idt/>                       -1);

<@idt/>  // Create the initializer for the new servant.
<@idt/>  std::auto_ptr < sdo_type::PublicationStateInitializer > initializer (this->factory_->createInitializer ());

<@idt/>  // Initialize the initial value trunk
<@idt/>  OASIS::Configuration_Member_Container * parent = 0;
<@idt/>  try
<@idt/>  {
<@idt/>    parent = &this->group_[inst.ext_id_];
<@idt/>  }
<@idt/>  catch (Invalid_Child & ex)
<@idt/>  {
<@idt/>    parent = 0;
<@idt/>  }

<@idt/>  // Initialize software probe bridge attributes.
<#list CG.this.attributes as attr >
<@idt/>  ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_${attr.identifier}) (*initializer, "${attr.identifier}", parent);
</#list>
<#assign superClasses = CG.this.allSuperclasses />
<#list superClasses as superClass >
  <#assign tempStr = CG.scope (superClass.name) />
  <#if tempStr != "OASIS::Middleware::SoftwareProbe">
    <#list superClass.attributes as attr >
<@idt/>  ::OASIS::initialize (&sdo_type::PublicationStateInitializer::set_${attr.identifier}) (*initializer, "${attr.identifier}", parent);
    </#list>
  </#if>
</#list>
<@idt/>  this->initialize_metadata (*initializer, einode, inst);

<@idt/>  // We are now ready to create the servant.
<@idt/>  this->servants_[inst.ext_id_.c_str ()] =
<@idt/>    this->factory_->createServant (*initializer, ::TENA::Middleware::Reliable);

<@idt/>  return 0;
<@idt/>}

<@idt/>//
<@idt/>// publish
<@idt/>//
<@idt/>int ${implBaseName}::
<@idt/>publish (const ::OASIS::DAC::Data_Packet & packet)
<@idt/>{
<@idt/>  // Extract the base contents of the packet.
<@idt/>  OASIS::Software_Probe_Header probe;
<@idt/>  probe.recall (packet.probe_data (),
<@idt/>                packet.probe_data_length (),
<@idt/>                packet.byte_order ());

<@idt/>  // Locate the servant for this software probe instance.
<@idt/>  ServantPtr_Map::const_iterator iter =
<@idt/>    this->servants_.find (probe.name_);

<@idt/>  if (iter == this->servants_.end ())
<@idt/>    ACE_ERROR_RETURN ((LM_ERROR,
<@idt/>                       ACE_TEXT ("%T (%t) - %M - servant does not exist for %s\n"),
<@idt/>                       probe.name_.c_str ()),
<@idt/>                       -1);

<@idt/>  // Locate the probe in the mapping.
<@idt/>  ::${implNameScope}::ServantPtr servant = iter->second;

<@idt/>  if (!servant.isValid ())
<@idt/>    ACE_ERROR_RETURN ((LM_ERROR,
<@idt/>                       ACE_TEXT ("%T (%t) - %M - invalid servant for %s\n"),
<@idt/>                       probe.name_.c_str ()),
<@idt/>                       -1);

<@idt/>  // Instantiate a new updater.
<@idt/>  std::auto_ptr < ::${implNameScope}::PublicationStateUpdater >
<@idt/>    updater (servant->createUpdater ());

<@idt/>  // Update the servant values.
<@idt/>  Software_Probe_Data_Preparer prep (packet.probe_data (),
<@idt/>                                     packet.probe_data_length ());
<@idt/>  ACE_InputCDR input (prep.message_block (),
<@idt/>                      packet.byte_order ());

<@idt/>  if (0 != this->update (*updater, input))
<@idt/>    return -1;

<@idt/>  // We are now ready to commit the updater.
<@idt/>  servant->commitUpdater (updater);
<@idt/>  return 0;
<@idt/>}

<@idt/>//
<@idt/>// update
<@idt/>//
<@idt/>int ${implBaseName}::
<@idt/>update (PublicationStateUpdater & updater, ACE_InputCDR & input)
<@idt/>{
<#if superClassScopeName == "OASIS::Middleware::SoftwareProbe" >
<@idt/>  // Extract the contents from the base class.
<@idt/>  if (0 != ::OASIS::Software_Probe_Bridge::update (updater, input))
<@idt/>    ACE_ERROR_RETURN ((LM_ERROR,
<@idt/>                       ACE_TEXT ("%T (%t) - %M - failed to update base class\n")),
<@idt/>                       -1);
<#else>
<@idt/>  // Let another bridge does it processing first.
<@idt/>  if (0 != ::${superClassScopeName}_Bridge::update (updater, input))
<@idt/>    ACE_ERROR_RETURN ((LM_ERROR,
<@idt/>                       ACE_TEXT ("%T (%t) - %M - failed to update base class %s\n"),
<@idt/>                       ACE_TEXT ("::${superClassScopeName}")),
<@idt/>                       -1);
</#if>

<#if !CG.this.attributes.empty >
<@idt/>  // Now, we can extract our contents from the packet.
<@idt/>  using namespace ::${implNameScope};
<#assign attribs = filterOut(onConstAttribute, CG.this.attributes) />
<#list attribs as attrib >
  <#assign attribName = attrib.identifier />
<@idt/>  if (0 != ::OASIS::updater (&PublicationStateUpdater::set_${attribName}) (updater, input))
<@idt/>    ACE_ERROR_RETURN ((LM_ERROR,
<@idt/>                       ACE_TEXT ("%T (%t) - %M - failed to unpackage ${attribName}\n")),
<@idt/>                       -1);

</#list>
</#if>
<@idt/>  return 0;
<@idt/>}

<@closeNameSpace CG.this.owner.name />
