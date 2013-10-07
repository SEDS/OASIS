<#ftl attributes=
{
  "phase":0,
  "capability":"GenerateBridge",
  "instanceTags":"H_FILES",
  "appliesTo":"ClassNode"
} />
<#assign baseName = "${CG.this.name.base}" />
<#assign nameScope = CG.scope(CG.this.name) />
<#assign implName = CG.implNameFor(CG.this.name) />
<#assign implBaseName = "${baseName}_Bridge" />
<#assign implNameScope = CG.scope(implName) />
<#assign implPath = CG.path (CG.this.owner.name) />
<#assign implFile = "${implBaseName}.h" />
<#assign sdoPath = CG.path (CG.this.name) />
<#assign CG_LOCATION = "src/" + "${implPath}" />
<#assign CG_FILENAME = "${implFile}" />

<#assign globalProtectionMacro = CG.macro(implName, CG_FILENAME)?upper_case />
// -*- C++ -*-

//=============================================================================
/**
 * @file        ${implFile}
 *
 * $Id: softwareProbeBridge.h.ftl 2135 2012-02-16 15:39:18Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _${globalProtectionMacro}_
#define _${globalProtectionMacro}_

#include "${sdoPath}.h"
#include "oasis/middleware/tena/bridges/Software_Probe_Bridge_T.h"

<@openNameSpace CG.this.owner.name />

<@idt/>/**
<@idt/> * @class ${implBaseName}
<@idt/> *
<@idt/> * Software probe bridge for ${nameScope}.
<@idt/> */
<@idt/>class ${implBaseName} :
<@idt/>  public ::OASIS::Software_Probe_Bridge_T < ::${nameScope}_SDO >
<@idt/>{
<@idt/>public:
<@idt/>  /// Type definition of the base type.
<@idt/>  typedef ::OASIS::Software_Probe_Bridge_T < ::${nameScope}_SDO > base_type;

<@idt/>  /// Static factory method.
<@idt/>  static ::OASIS::Software_Probe_Bridge * _create (void);

<@idt/>  /// Default constructor.
<@idt/>  ${implBaseName} (void);

<@idt/>  /// Destructor.
<@idt/>  virtual ~${implBaseName} (void);

<@idt/>  /**
<@idt/>   * Create a new servant for the specified software probe instance.
<@idt/>   *
<@idt/>   * @param[in]        einode            Parent EI node
<@idt/>   * @param[in]        inst              Software probe instance
<@idt/>   */
<@idt/>  virtual int create_servant (const ACE_Utils::UUID & einode,
<@idt/>                              const ::OASIS::DAC::Software_Probe_Instance &);

<@idt/>  /**
<@idt/>   * Publish a new data packet. This will convert the OASIS data packet
<@idt/>   * to an TENA object, then publish it via the TENA middleware.
<@idt/>   *
<@idt/>   * @param[in]         packet           Data packet to publish
<@idt/>   */
<@idt/>  virtual int publish (const ::OASIS::DAC::Data_Packet & packet);

<@idt/>  /// Type definition of the SDO publication state updater.
<@idt/>  typedef ::${implNameScope}::PublicationStateUpdater PublicationStateUpdater;

<@idt/>  /**
<@idt/>   * Utility method that extract values from the provided input
<@idt/>   * stream and set its corresponding value on the updater.
<@idt/>   *
<@idt/>   * @param[in]        updater           Target updater
<@idt/>   * @param[in]        input             Source input stream
<@idt/>   */
<@idt/>  static int update (PublicationStateUpdater & updater, ACE_InputCDR & input);
<@idt/>};

<@closeNameSpace CG.this.owner.name />

#endif  // !defined _${globalProtectionMacro}_
