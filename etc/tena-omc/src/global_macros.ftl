<#ftl attributes = {"macros",true}
   strip_whitespace=true
   strip_text=true
   />
<#-- Need to set number format since default formats 1000 as "1,000" -->
<#assign number_format="##0" />
<#--########################################################################-->
<#-- The names for the macros are just using the component name
   not the object model name.  The backwards-compatible names
  always include the OM name in the component name, so this is
  redundant -->
<#function macroNameFor(componentName, componentObjectModelName, suffix)>
    <#return CG.macro([componentName, suffix]) />
</#function>
<#--########################################################################-->
<#function macroName(suffix)>
  <#return CG.macro([CG.component.fullName, suffix]) />
</#function>
<#--########################################################################-->
<#function exportNameFn>
   <#local expnam = macroName("EXPORT") />
   <#return expnam />
</#function>
<#--########################################################################-->
<#function exportNameIncludeFile>
   <#return "lib" + CG.component.fullName + "-Export.h" />
</#function>
<#--########################################################################-->
<#macro exportInclude>
#include <${exportNameIncludeFile()}>
</#macro>
<#--########################################################################-->
<#macro header nameSpace fn>
/////////////////////////////////////////////////////////////////// -*- C++ -*-
<#-- fn sometimes has a "Dir/" in front of it.  We want to guess the class
     name from fn so remove any "Dir/" prefix and any .h or .cpp suffix. -->
<#local start=fn?last_index_of("/") + 1 />
<#local   end=fn?last_index_of(".") />
<#if end == -1 >
  <#local end=fn?length />
</#if>
<#local className=fn?substring(start,end) />
/*!
<#if nameSpace.list?size == 0 >
 * \file ${fn}
 <#else>
 * \file ${CG.path(nameSpace)}/${fn}
 </#if>
<#if fn?ends_with(".h")>
 *
 * \brief Contains the declaration of and documentation for
 * ${CG.scope(nameSpace)}::${className}.
 *
 * This file contains the declaration of and documentation for the
 * ${CG.scope(nameSpace)}::${className} class.
</#if>
<#if fn?ends_with(".cpp")>
 *
 * \brief Contains the definition of methods of
 * ${CG.scope(nameSpace)}::${className}.
 *
 * This file contains the definition of the methods of the
 * ${CG.scope(nameSpace)}::${className} class.
</#if>
 */
<#if fn?ends_with(".h") >
<#-- macro globalProtectionMacro is used by the trailer, too -->
<#if nameSpace.list?size == 0 >
<#assign globalProtectionMacro = "__" + CG.macro(nameSpace,fn) />
<#else>
<#assign globalProtectionMacro = CG.macro(nameSpace,fn) />
</#if>

#ifndef ${globalProtectionMacro}
#define ${globalProtectionMacro}
</#if>
</#macro>
<#--########################################################################-->
<#macro trailer nameSpace fn>
<#if fn?ends_with(".h") >
#endif // ifndef ${globalProtectionMacro}
</#if>
</#macro>
<#--########################################################################-->
<#-- Add a space for each tic of indentation -->
<#macro idt><#if 0 < indentation?default(0)><#list 1..indentation as i> </#list></#if></#macro>
<#--########################################################################-->
<#macro indent>
<#assign indentation = indentation?default(0) + 2>
</#macro>
<#--########################################################################-->
<#macro unindent>
<#assign indentation = indentation?default(2) - 2 >
</#macro>

<#--########################################################################-->
<#-- Generate the properly indented namespace opening sequence -->
<#macro openModuleScope scopedName>
<#list scopedName.list as part>
<@idt/>module ${part}
<@idt/>{<@indent/>
</#list>
</#macro>

<#--########################################################################-->
<#macro closeModuleScope scopedName>
<#list scopedName.list?reverse as part><@unindent/><@idt/>}
</#list>
</#macro>

<#--########################################################################-->
<#-- Generate the properly indented namespace opening sequence -->
<#macro openNameSpace scopedName>
<#list scopedName.list as part>
<@idt/>namespace ${part}
<@idt/>{<@indent/>
</#list>
</#macro>

<#--########################################################################-->
<#macro closeNameSpace scopedName><#list scopedName.list?reverse as part><@unindent/><@idt/>}
</#list></#macro>

<#--########################################################################-->
<#-- Generate the properly indented IDL module opening sequence -->
<#macro openIDLnameSpace scopedName>
<#list scopedName.list as part>
<@idt/>module ${part}
<@idt/>{<@indent/>
</#list>
</#macro>
<#--########################################################################-->
<#macro closeIDLnameSpace scopedName><#list scopedName.list as part><@unindent/><@idt/>};
</#list></#macro>
<#--###############################################################-->
<#-- function to find if local methods implementations are imported -->
<#function isImportingLocalMethodImpls >
  <#local importsLocalMethods = false />
  <#list CG.component.used as import >
    <#if import.providesFeature(CG.plugin.capabilityNamespace + ".LocalMethodsImplementation","")>
      <#local importsLocalMethods = true />
      <#break/>
    </#if>
  </#list>
  <#return importsLocalMethods />
</#function>
<#--###############################################################-->
<#-- Function to get all the artifacts needed to generate a build file -->
<#-- On windows, returns a 3 element hash with keys
   libs, includePaths, and libPaths,  whose values are three strings.
   On other platforms, returns hash whose values are three sequences -->
<#function buildDependencies platformKind >
  <#if platformKind == "windows">
    <#assign inclPfx = ";&quot;$(TENA_HOME)\\" />
    <#assign inclSfx = "&quot;" />
    <#assign libsPfx = "" />
    <#assign libsSfx = " " />
    <#assign libPathPfx = "&quot;$(TENA_HOME)\\" />
    <#assign libPathSfx = "&quot;;" />
  <#else>
    <#assign inclPfx = "-I" />
    <#assign inclSfx = " " />
    <#assign libsPfx = "-l" />
    <#assign libsSfx = " " />
    <#assign libPathPfx = "-L" />
    <#assign libPathSfx = " " />
  </#if>
  <#assign libList = [] />
  <#assign inclList = [] />
  <#assign libPathList = [] />
  <#assign libString = "" />
  <#assign inclString = "" />
  <#assign libPathString = "" />
  <#list CG.component.allUsed as dependency >
    <#list dependency.getArtifactsOfKind("library") as library >
      <#assign libName = library.resource />
      <#if !libList?seq_contains(libName) >
        <#assign libList = libList + [libName]/>
  <#if platformKind == "windows">
          <#assign libString = libString + libsPfx +
    CG.buildLibraryName(libName,platformKind) + libsSfx />
        </#if>
       </#if>
    </#list>
    <#list dependency.getArtifactsOfKind("includeDir") as incldir >
      <#assign path = incldir.resource />
      <#if !inclList?seq_contains(path) >
        <#assign inclList = inclList + [path]/>
  <#if platformKind == "windows">
    <#assign path = path?replace("/","\\")/>
    <#assign inclString = inclString + inclPfx + path + inclSfx />
  </#if>
      </#if>
    </#list>
    <#list dependency.getArtifactsOfKind("libDir") as libdir >
      <#assign path = libdir.resource />
      <#if !libPathList?seq_contains(path) >
        <#assign libPathList = libPathList + [path]/>
  <#if platformKind == "windows">
    <#assign path = path?replace("/","\\")/>
    <#assign libPathString = libPathString +
    libPathPfx + path + libPathSfx />
  </#if>
      </#if>
    </#list>
  </#list>

  <#-- returns a 3 element hash with keys libs, includePaths, and libPath -->
  <#if platformKind == "windows">
    <#return {"libs":libString,
            "includePaths":inclString,
            "libPaths":libPathString} />
  </#if>
  <#return  {"libs":libList,
            "includePaths":inclList,
            "libPaths":libPathList} />
</#function>

<#--###############################################################-->
<#-- Macros used by basic impl callbacks to display object state -->
<#-- -------------- MACRO TO DISPLAY A PRIMITIVE ATTR/Operand ----- -->

<#--#################################################################-->
<#-- MACRO TO DISPLAY STATE OF ANY CLASS (SDO, LocalClass, Message) -->
<#--------------------------------------------------------------------->

<#macro displayClass stream, value, name, classType >
<@displayAttributes stream, "pPubState", name, classType />
</#macro>

<#macro displayAttributes stream, value, name, classType >
  <#global column = column?default(0) />
  <#list classType.allAttributes as attr>
    <#if !attr.private >
<#-- output the name of the field to be output - primitives on same line -->
<@idt/>${stream} << std::setw(${column}) << " " << "${name}.${attr.identifier} ";
      <#if attr.optional >
<@idt/>if ( ! ${value}->is_${attr.identifier}_set() )
<@idt/>{
<@idt/>  ${stream} << "<uninitialized>" << ::std::endl;
<@idt/>}
<@idt/>else
<@idt/>{
<@indent/>
      </#if>
      <#if attr.type.isBoolean() >
<@idt/>${stream} << (${value}->${attr.identifier.accessor}() ? "true":"false") << std::endl;
      <#elseif attr.type.isOctet() >
<@idt/>${stream} << "0x" << std::setw(2) << std::setbase(16) << std::setfill('0')
<@idt/>   << static_cast<unsigned>(${value}->${attr.identifier.accessor}())
<@idt/>   << std::setbase(10) << std::setfill(' ') << std::endl;
      <#elseif attr.type.isPrimitive()
            || attr.type.isEnumeration()
            || attr.type.isString()>
<@idt/>${stream} << ${value}->${attr.identifier.accessor}() << std::endl;
      <#elseif attr.type.isPointer()>
        <#local containedName = tempVarName(attr.identifier,
                                            attr.type.pointedTo.name.base,
                                            "Pointer") />
<@idt/>${attr.type.CPP} ${containedName} (
<@idt/>    ${value}->${ attr.identifier.accessor}() );
<@displayPointer stream, containedName />
      <#elseif attr.type.isVector() >
        <#local containedName = tempVarName(attr.identifier, "Vector") />
<@idt/>${attr.type.CPP} const & ${containedName}(
<@idt/>  ${value}->${attr.identifier.accessor}() );
<@idt/>${stream} << std::endl;
        <#global column = column + 4 />
<@displayVector stream, containedName, attr.identifier, attr.type />
        <#global column = column - 4 />
      <#elseif attr.type.isLocalClass() || attr.type.isMessage() >
        <#local pointer = attr.type.message?string("MessagePtr", "LocalClassPtr") />
        <#local containedName = tempVarName(attr.identifier,
                                            attr.type.metatype,
                                            "Ptr") />
        <#local lcAttrs = filterOut(onPrivate, attr.type.allAttributes) />
        <#if lcAttrs?size != 0 >
<@idt/>${CG.scope(attr.type.name)}::Immutable${pointer} ${containedName}(
<@idt/>  ${value}->${attr.identifier.accessor}() );

<@idt/>${stream} << std::endl;
          <#global column = column + 4 />
<@displayAttributes stream, containedName, attr.identifier, attr.type />
          <#global column = column - 4 />
        </#if>
      </#if>
      <#if attr.optional >
<@unindent/>
<@idt/>}
      </#if>
    </#if>
  </#list>
</#macro>
<#-- display an SDO pointer -- sort of -- does not display contents  -->
<#-- called by displayAttributes, not directly -->
<#macro displayPointer stream, value >
<@idt/>// Display the ID of the SDO that is "pointed to".
<@idt/>if ( ${value}.isValid() )
<@idt/>{
<@idt/>   ${stream} << std::setw(${column}) << " " << ${value}->getObjectID() << std::endl;
<@idt/>} else {
<@idt/>   ${stream} << std::setw(${column}) << " " << "null or invalid SDO pointer" << std::endl;
<@idt/>}
</#macro>
<#--#################################################################-->
<#-- -------------- MACRO TO DISPLAY A VECTOR ATTR -------- -->
<#-- called by displayAttributes, not directly -->
<#macro displayVector stream, value, name, type >
<@displayNestedVector 0, stream, value, name, type />
</#macro>
<#macro displayNestedVector nesting, stream, value, name, type >
  <#local containedType = type.getContainedType() />
  <#local elementName = tempVarName(name,"element") />
  <#local vectorLengthName = tempVarName(name,"length") />
  <#local index = tempVarName(name,"index") />
<@idt/>size_t ${vectorLengthName} = ${value}.size();
<@idt/>for (size_t ${index} = 0;
<@idt/>     ${index} < ${vectorLengthName};
<@idt/>     ++${index})
<@idt/>{
<@indent/>
  <#if nesting == 0 >
<@idt/>${stream} << std::setw(${column}) << " " << "${name} [ " << ${index} << " ]";
  <#else>
<@idt/>${stream} << std::setw(${column}) << " " << " [ " << ${index} << " ]";
  </#if>
<#global column = column + 4 />
  <#if containedType.isBoolean() >
<@idt/>${stream} << (${value}[${index}]?"true":"false") << std::endl;
  <#elseif containedType.isPrimitive()
        || containedType.isString()
        || containedType.isEnumeration() >
<@idt/>${stream} << ${value}[${index}] << std::endl;
  <#elseif containedType.isVector() >
<@idt/>${stream} << std::endl;
<@idt/>${containedType.CPP} const & ${elementName}( ${value}[${index}] );
<@displayNestedVector nesting + 1, stream, elementName, elementName, containedType />
  <#elseif containedType.isPointer() >
<@idt/>${stream} << std::endl;
<@idt/>${containedType.CPP} const & ${elementName}( ${value}[${index}] );
<@displayPointer stream, elementName />
  <#elseif containedType.isLocalClass() || containedType.isMessage() >
    <#local pointer = containedType.message?string("MessagePtr",
                                                   "LocalClassPtr") />
    <#local lcAttrs = filterOut(onPrivate, containedType.allAttributes) />
    <#if lcAttrs?size != 0 >
<@idt/>${stream} << std::endl;
<@idt/>${CG.scope(containedType.name)}::Immutable${pointer} const &
<@idt/>    ${elementName}( ${value}[${index}] );
<@displayAttributes  stream, elementName, "", containedType />
    </#if>
  <#else>
<@idt/>TENA_ERROR << "Unexpected type in vector: " << e.what() << std::endl;
  </#if>
<#global column = column - 4 />
<@unindent/>
<@idt/>}
</#macro>
<#macro displayOptionalAttribute stream, object, attribute >
<@idt/>if ( ${object}->is_${attribute}_set() )
<@idt/>{
<@idt/>  ${stream} << ${object}->get${attribute}();
<@idt/>}
<@idt/>else
<@idt/>{
<@idt/>  ${stream} << "<uninitialized>";
<@idt/>}
</#macro>
<#macro displayOptionalTime stream, object, attribute >
<@idt/>if ( ${object}->is_${attribute}_set() )
<@idt/>{
<@idt/>  ${stream} << TENA::Middleware::Utils::toTimestamp( ${object}->get${attribute}() );
<@idt/>}
<@idt/>else
<@idt/>{
<@idt/>  ${stream} << "<uninitialized>";
<@idt/>}
</#macro>
<#--###############################################################-->
<#-- Macros to display Message and SDO metatdata -->
<#macro displayMetadata stream, value, name, classType >
  <#if classType.isClass()>
<#--    <#assign superClasses = classType.allSuperclasses>
    <#list superClasses as superClass> -->
<@idt/>${stream} << "${name}"
<@idt/>   << "\n\tID=`"
<@idt/>   << ${value}->getID()
<@idt/>   << "'\n\tStateVersion="
<@idt/>   << ${value}->getStateVersion()
<@idt/>   << "\n\tReactivationCount="
<@idt/>   << ${value}->getReactivationCount()
<@idt/>   << "\n\tgetPublisherEndpointsString=`"
<@idt/>   << ${value}->getPublisherEndpointsString()
<@idt/>   << "'\n\tPublisherApplicationID="
<@idt/>   << ${value}->getPublisherApplicationID()
<@idt/>   << "\n\tPublisherSessionID="
<@idt/>   << ${value}->getPublisherSessionID()
<@idt/>   << "\n\tFilteringContext="
<@idt/>   << ${value}->getFilteringContext()
<@idt/>   << std::setw(4) << " "
<@idt/>   << "\n\tCommunicationProperties=TENA::Middleware::"
<@idt/>   << ( ${value}->getCommunicationProperties() ==
<@idt/>        TENA::Middleware::Reliable ?
<@idt/>        "Reliable" : "BestEffort" )
<@idt/>   << "\n\tMulticastAddressString=`"
<@idt/>   << ${value}->getMulticastAddressString()
<@idt/>   << "'\n\tisTerminated="
<@idt/>   << ( ${value}->isTerminated() ? "true" : "false" )
<@idt/>   << "\n\tTypeIDpath="
<@idt/>   << ${value}->getTypeIDpath()
<@idt/>   << "\n\tTimeOfCreation ="
<@idt/>   << TENA::Middleware::Utils::toTimestamp( ${value}->getTimeOfCreation() )
<@idt/>   << "\n\tTimeOfDiscovery=";

<@displayOptionalTime stream, value, "TimeOfDiscovery" />

<@idt/>${stream} << "\n\tTimeOfCommit   ="
<@idt/>   << TENA::Middleware::Utils::toTimestamp( ${value}->getTimeOfCommit() )
<@idt/>   << "\n\tTimeOfReceipt  =";

<@displayOptionalTime stream, value, "TimeOfReceipt" />
  <#elseif classType.isMessage()>
<@idt/>${stream} << "${name}"
<@idt/>   << "\n\tID="
<@idt/>   << ${value}->getID()
<@idt/>   << "\n\tSenderID="
<@idt/>   << ${value}->getSenderID()
<@idt/>   << "\n\tMessageCount="
<@idt/>   << ${value}->getMessageCount()
<@idt/>   << "\n\tSenderEndpointsString=`"
<@idt/>   << ${value}->getSenderEndpointsString()
<@idt/>   << "'\n\tSenderApplicationID="
<@idt/>   << ${value}->getSenderApplicationID()
<@idt/>   << "\n\tSenderSessionID="
<@idt/>   << ${value}->getSenderSessionID()
<@idt/>   << "\n\tTimeOfTransmission="
<@idt/>   << TENA::Middleware::Utils::toTimestamp( ${value}->getTimeOfTransmission() )
<@idt/>   << "\n\tTimeOfReceipt     ="
<@idt/>   << TENA::Middleware::Utils::toTimestamp( ${value}->getTimeOfReceipt() )
<@idt/>   << "\n\tCommunicationProperties=TENA::Middleware::"
<@idt/>   << ( ${value}->getCommunicationProperties() ==
<@idt/>        TENA::Middleware::Reliable ?
<@idt/>        "Reliable" : "BestEffort" )
<@idt/>   << "\n\tMulticastAddressString=`"
<@idt/>   << ${value}->getMulticastAddressString()
<@idt/>   << "'\n\tTypeIDpath="
<@idt/>   << ${value}->getTypeIDpath()
<@idt/>   << "\n\tFilteringContext="
<@idt/>   << ${value}->getFilteringContext();
  </#if>
</#macro>
<#macro displayMessageSenderMetadata stream, value, name >
<@idt/>${stream} << "${name}"
<@idt/>   << "\n\tID="
<@idt/>   << ${value}->getID()
<@idt/>   << "\n\tMessageCount="
<@idt/>   << ${value}->getMessageCount()
<@idt/>   << "\n\tEndpointsString=`"
<@idt/>   << ${value}->getEndpointsString()
<@idt/>   << "'\n\tSenderApplicationID="
<@idt/>   << ${value}->getApplicationID()
<@idt/>   << "\n\tSenderSessionID="
<@idt/>   << ${value}->getSessionID()
<@idt/>   << "\n\tTypeIDpath="
<@idt/>   << ${value}->getTypeIDpath()
<@idt/>   << "\n\tCommunicationProperties=TENA::Middleware::"
<@idt/>   << ( ${value}->getCommunicationProperties() ==
<@idt/>        TENA::Middleware::Reliable ?
<@idt/>        "Reliable" : "BestEffort" )
<@idt/>   << "\n\tFilteringContext="
<@idt/>   << ${value}->getFilteringContext();
</#macro>
<#--###############################################################-->
<#-- Macros used by Message and SDO Publishers to update the state -->

<#function ctorParams lctype >
  <#assign result = [] />
  <#if lctype.constructors?size == 0 >
    <#list filterOut([onOptional], lctype.allAttributes) as attr >
      <#assign result = result + [attr] />
    </#list>
  <#else>
    <#list lctype.constructors?first.parameters as param >
      <#assign result = result + [param] />
    </#list>
  </#if>
  <#return result />
</#function>

<#function ctorParamTypes lctype >
  <#assign result = [] />
  <#if lctype.constructors?size == 0 >
    <#list filterOut([onOptional], lctype.allAttributes) as attr >
      <#assign result = result + [attr.type] />
    </#list>
  <#else>
    <#list lctype.constructors?first.parameters as param >
      <#assign result = result + [param.type] />
    </#list>
  </#if>
  <#return result />
</#function>

<#function updateValue type>
  <#if type.boolean>
    <#return "updateCount % 2"/>
  <#elseif type.char>
    <#return "\"TENA\"[ updateCount % 4 ]"/>
  <#elseif type.float>
    <#-- static_cast to avoid truncation warnings with visual studio -->
    <#return "static_cast< ${type.CPP} >( updateCount )"/>
  <#elseif type.enumeration>
    <#return "${CG.scope(type.name.nameSpace)}::${type.tokens?first}"/>
  <#elseif type.primitive>
    <#return "updateCount"/>
  <#elseif type.string>
    <#return "updateLabel"/>
  <#else>
    <#return ""/>
  </#if>
</#function>

<#function arbitraryUpdateValue type>
  <#return "TENA::Middleware::ArbitraryValue< ${type.CPP} >( ${updateValue(type)} )"/>
</#function>

<#--
 # This macros is used solely by createLocalClass and createUpdatedLocalClass
 # and is not intended to be called otherwise.
 #-->
<#macro createLocalClass_recursive lctype, varname, update >
  <#local pointer = lctype.message?string("MessagePtr", "LocalClassPtr") />
  <#list ctorParamTypes(lctype) as paramType >
    <#--
     # Don't want to use filter here because we care about the particular index
     #-->
    <#if paramType.localClass || paramType.message >
<@createLocalClass_recursive paramType, "${varname}_${paramType_index}", update />
    </#if>
  </#list>
<@idt/>${CG.scope(lctype.name)}::${pointer} ${varname}(
<@indent/>
<@idt/>${CG.scope(lctype.name)}::create(<@indent/><#list ctorParams(lctype) as param >
<@idt/>/* ${param.identifier} */ <#if (param.type.localClass || param.type.message) >${varname}_${param_index}<#rt><#else>${update?string(arbitraryUpdateValue(param.type), "TENA::Middleware::ArbitraryValue< ${param.type.CPP} >()")}</#if><#if param_has_next>,<#else> </#if></#list>) );
<@unindent/><@unindent/>
</#macro>

<#--
 # Create a local class or message.
 #-->
<#macro createLocalClass lctype, varname >
<@idt/>/// \todo In a real application, instances of \c ArbitraryValue<T>
<@idt/>///       should be replaced with values that are sensible for the
<@idt/>///       particular application.
<@createLocalClass_recursive lctype, varname, false />
</#macro>

<#--
 # Create a local class or message that is initialized based on the updateCount.
 #-->
<#macro createUpdatedLocalClass lctype, varname>
<@idt/>/// \todo In a real application, instances of \c ArbitraryValue<T>
<@idt/>///       should be replaced with values that are sensible for the
<@idt/>///       particular application.
<@createLocalClass_recursive lctype, varname, true />
</#macro>

<#--
 # Create a local class or message.
 #-->
<#macro callCreateForLocalClass lctype >
${CG.scope(lctype.name)}::create(<@indent/><#list ctorParams(lctype) as param >
<@idt/>/* ${param.identifier} */ <#if (param.type.localClass || param.type.message) ><@callCreateForLocalClass param.type /><#else>${param.type.CPP_INITIALIZER}</#if><#if param_has_next>,<#else> </#if></#list>)<#rt>
<@unindent/>
</#macro>

<#--
 # Initialize class
 #-->
<#macro initializeClass ctype, varfactory, varname >
    std::auto_ptr< ${CG.scope(ctype.name)}::PublicationStateInitializer > ${varname}(
      ${varfactory}->createInitializer() );
<#list filterOut([onOptional, on.ClassNode], ctype.allAttributes) as attr >
  <#if attr.type.localClass || attr.type.message >
<@createLocalClass attr.type, attr.identifier />
    <#assign val = attr.identifier />
  <#else>
    <#assign val = attr.type.CPP_INITIALIZER />
  </#if>
    ${varname}->${attr.identifier.mutator}( ${val} );
</#list>
</#macro>

<#-- ------------------------------------------------------------- -->
<#-- -------------- MACRO TO UPDATE A VECTOR ATTR  --------------- -->
<#macro updateVector value, valueName, identifier, vectorType>
  <#local valueName = CG.macro(valueName) />
  <#local containedType = vectorType.getContainedType() />

  <#if containedType.vector >
  ${containedType.CPP} ${valueName}_element;
  <#elseif containedType.localClass || containedType.message >
<@createLocalClass containedType, "${valueName}_element" />
  <#elseif containedType.pointer >
  ${containedType.CPP} ${valueName}_element;
  <#else>
  ${containedType.CPP} ${valueName}_element =
    ${arbitraryUpdateValue(containedType)};
  </#if>

  ${vectorType.CPP} ${valueName};
  ${valueName}.push_back( ${valueName}_element );

  // Set the new vector back into the state
  ${value}->${identifier.mutator}( ${valueName} );
</#macro>
<#-- #################################################################### -->
<#--  Include the headers to access contained local class and message types-->
<#--  argument 'classes' may be a single class type or a list of class types -->
<#-- #################################################################### -->
<#macro localClassAndMessageIncludes classes >
  <#list filter(on.LocalClassNode, allRelatedTypes(classes)) as type>
    <#if type_index == 0 >

// Include all the files for contained local class types, needed to
// access the state of this SDO
    </#if>
#include <${CG.path(type.name)}.h>
  </#list>
  <#list filter(on.MessageNode, allRelatedTypes(classes)) as type>
    <#if type_index == 0 >

// Include all the files for contained message types, needed to
// access the state of this SDO
    </#if>
#include <${CG.path(type.name)}.h>
  </#list>

</#macro>

<#macro updateLocalAttribute attr, value, name>
  <#if attr.type.isPointer()>
  // This SDO contains an SDO pointer.  Currently we do not code-generate
  // the creation of an SDO pointer.  This application may be manually modified
  // to create an SDO of the "pointed to" type after the SDO servant is
  // created in the main section of the program.  An SDO Pointer can then be
  // obtained and used to update the containing SDO's state.
      <#elseif attr.type.isVector()>
<@updateVector value,
               name + "_" + attr.identifier,
               attr.identifier,
               attr.type />
  <#elseif attr.type.isLocalClass() || attr.type.isMessage() >
    <#local containedName =
                name + "_" + attr.identifier  + "_" + attr.type.metatype />
  // create a ${attr.type.metatype} instance for attribute ${attr.identifier}
<@createLocalClass attr.type, containedName />
<#if (filter(onOptional, attr.type.attributes)?size > 0)>

  //
  // Update the optional attributes for ${name + "_" + attr.identifier}.
  //
</#if>
<@updateLocalAttributes containedName,
                        name + "_" + attr.identifier,
                        attr.type />

  // Change the value of the ${name}'s
  // ${attr.type.metatype} attribute ${attr.identifier}
  ${value}->
    ${attr.identifier.mutator}(
      ${containedName} );
  <#else>
  // Use updateCount as ${attr.type.CPP} to update the value of "${attr.identifier}"
  ${value}->
    ${attr.identifier.mutator}(
      ${arbitraryUpdateValue(attr.type)} );
  </#if>
</#macro>

<#macro updateSdoAttribute attr, value, name>
  <#if attr.type.isClass()>
    <#local containedName = CG.macro("p_${name}${attr.identifier}_Updater") />
  // Update the SDO "${attr.type.name}" contained in
  // "${name}"
  std::auto_ptr< ${CG.scope(attr.type.name)}::PublicationStateUpdater >
    ${containedName}(
      ${value}->
        create_${attr.identifier}_Updater() );
<@updateSdoAttributes containedName,
                   name + "_" + attr.identifier,
                   attr.type />
  // Commit all the updates to the SDO
  // "${name}"
  ${value}->
    commit_${attr.identifier}_Updater(
      ${containedName} );
      <#elseif attr.type.isString()>
  // Change the value of the string attribute "${attr.identifier}"
  ${value}->
    ${attr.identifier.mutator}( updateLabel );
  <#else>
<@updateLocalAttribute attr, value, name/>
  </#if>
</#macro>

<#-- #################################################################### -->
<#-- DEFINE A RECURSIVE MACRO TO UPDATE STATE OF ANY CLASS -->
<#-- (SDO or LocalClass or Message) -->
<#-- #################################################################### -->
<#macro updateSdoAttributes value, name, classType>
  <#list filterOut(onConstAttribute, classType.allAttributes) as attr>
    <#if !(attr.private || attr.readonly)>
<@updateSdoAttribute attr, value, name/>
    </#if>
  </#list>
</#macro>

<#--
 # For local classes and messages, we only want to update the optional
 # attributes.  Assume that nonoptional attributes get updated via the
 # constructor.
 #-->
<#macro updateLocalAttributes value, name, classType>
  <#list filter(onOptional, classType.allAttributes) as attr>
    <#if !(attr.private || attr.readonly)>
<@updateLocalAttribute attr, value, name/>
    </#if>
  </#list>
</#macro>

<#-- #################################################################### -->
<#-- Include all the headers needed to access a type, and any of its      -->
<#--  contained types.                                                    -->
<#-- #################################################################### -->

<#macro allRelatedHeaders type>
  <#local allRelatedTypeList= CG.pointersToTypes(allRelatedTypes( type )) />
  <@includeAccessHeaders allRelatedTypeList />
</#macro>

<#-- #################################################################### -->
<#--  Include the relevant headers to access the types in passed list     -->
<#-- #################################################################### -->
<#macro includeAccessHeaders typeList>
  <#-- If an SDO or SDO pointer, includes to deref pointer and access proxy -->
  <#-- Deal with SDO or SDO pointers the same way -->
  <#list CG.pointersToTypes(typeList) as type>
    <#if type_index == 0 >
// Include headers to allow access to any contained and referenced types

    </#if>
    <#if type.isClass()>
// Include header to access the publication state of ${CG.scope(type.name)}
#include <${CG.path(type.name)}.h>
    <#elseif type.localClass >
// Include header to use ${type.metatype} ${CG.scope(type.name)}
#include <${CG.path(type.name)}.h>
    <#elseif type.message >
// Include header to use ${type.metatype} ${CG.scope(type.name)}
#include <${CG.path(type.name)}.h>
    </#if>
  </#list>
</#macro>

