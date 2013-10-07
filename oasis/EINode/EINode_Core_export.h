
// -*- C++ -*-
// $Id: EINode_Core_export.h 1710 2010-11-20 14:23:03Z hillj $
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl OASIS_EINODE_CORE
// ------------------------------
#ifndef OASIS_EINODE_CORE_EXPORT_H
#define OASIS_EINODE_CORE_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (OASIS_EINODE_CORE_HAS_DLL)
#  define OASIS_EINODE_CORE_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && OASIS_EINODE_CORE_HAS_DLL */

#if !defined (OASIS_EINODE_CORE_HAS_DLL)
#  define OASIS_EINODE_CORE_HAS_DLL 1
#endif /* ! OASIS_EINODE_CORE_HAS_DLL */

#if defined (OASIS_EINODE_CORE_HAS_DLL) && (OASIS_EINODE_CORE_HAS_DLL == 1)
#  if defined (OASIS_EINODE_CORE_BUILD_DLL)
#    define OASIS_EINODE_CORE_Export ACE_Proper_Export_Flag
#    define OASIS_EINODE_CORE_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define OASIS_EINODE_CORE_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* OASIS_EINODE_CORE_BUILD_DLL */
#    define OASIS_EINODE_CORE_Export ACE_Proper_Import_Flag
#    define OASIS_EINODE_CORE_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define OASIS_EINODE_CORE_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* OASIS_EINODE_CORE_BUILD_DLL */
#else /* OASIS_EINODE_CORE_HAS_DLL == 1 */
#  define OASIS_EINODE_CORE_Export
#  define OASIS_EINODE_CORE_SINGLETON_DECLARATION(T)
#  define OASIS_EINODE_CORE_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* OASIS_EINODE_CORE_HAS_DLL == 1 */

// Set OASIS_EINODE_CORE_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (OASIS_EINODE_CORE_NTRACE)
#  if (ACE_NTRACE == 1)
#    define OASIS_EINODE_CORE_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define OASIS_EINODE_CORE_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !OASIS_EINODE_CORE_NTRACE */

#if (OASIS_EINODE_CORE_NTRACE == 1)
#  define OASIS_EINODE_CORE_TRACE(X)
#else /* (OASIS_EINODE_CORE_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define OASIS_EINODE_CORE_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (OASIS_EINODE_CORE_NTRACE == 1) */

#endif /* OASIS_EINODE_CORE_EXPORT_H */

// End of auto generated file.
