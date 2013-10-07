<#ftl attributes=
{
  "phase":1,
  "capability":"GenerateBridge",
  "appliesTo":"ObjectModelNode"
} />
<#assign appName = CG.component.name + "-v" + CG.component.version  />
<#assign namespaceName = appName?replace (".", "_")?replace ("-", "_") />
<#assign exportBuildFlag = namespaceName?upper_case />

<#assign CG_LOCATION = "src" />
<#assign CG_FILENAME =  namespaceName + "_export.h" />
// -*- C++ -*-

#ifndef ${exportBuildFlag}_EXPORT_H
#define ${exportBuildFlag}_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (${exportBuildFlag}_HAS_DLL)
#  define ${exportBuildFlag}_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && ${exportBuildFlag}_HAS_DLL */

#if !defined (${exportBuildFlag}_HAS_DLL)
#  define ${exportBuildFlag}_HAS_DLL 1
#endif /* ! ${exportBuildFlag}_HAS_DLL */

#if defined (${exportBuildFlag}_HAS_DLL) && (${exportBuildFlag}_HAS_DLL == 1)
#  if defined (${exportBuildFlag}_BUILD_DLL)
#    define ${exportBuildFlag}_Export ACE_Proper_Export_Flag
#    define ${exportBuildFlag}_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define ${exportBuildFlag}_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* ${exportBuildFlag}_BUILD_DLL */
#    define ${exportBuildFlag}_Export ACE_Proper_Import_Flag
#    define ${exportBuildFlag}_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define ${exportBuildFlag}_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* ${exportBuildFlag}_BUILD_DLL */
#else /* ${exportBuildFlag}_HAS_DLL == 1 */
#  define ${exportBuildFlag}_Export
#  define ${exportBuildFlag}_SINGLETON_DECLARATION(T)
#  define ${exportBuildFlag}_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* ${exportBuildFlag}_HAS_DLL == 1 */

// Set ${exportBuildFlag}_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (${exportBuildFlag}_NTRACE)
#  if (ACE_NTRACE == 1)
#    define ${exportBuildFlag}_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define ${exportBuildFlag}_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !${exportBuildFlag}_NTRACE */

#if (${exportBuildFlag}_NTRACE == 1)
#  define ${exportBuildFlag}_TRACE(X)
#else /* (${exportBuildFlag}_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define ${exportBuildFlag}_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (${exportBuildFlag}_NTRACE == 1) */

#endif /* ${exportBuildFlag}_EXPORT_H */
