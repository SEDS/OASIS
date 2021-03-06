
// -*- C++ -*-
// $Id: PDL_FE_export.h 1716 2010-11-29 00:53:50Z hillj $
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl OASIS_PDL_FE
// ------------------------------
#ifndef OASIS_PDL_FE_EXPORT_H
#define OASIS_PDL_FE_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (OASIS_PDL_FE_HAS_DLL)
#  define OASIS_PDL_FE_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && OASIS_PDL_FE_HAS_DLL */

#if !defined (OASIS_PDL_FE_HAS_DLL)
#  define OASIS_PDL_FE_HAS_DLL 1
#endif /* ! OASIS_PDL_FE_HAS_DLL */

#if defined (OASIS_PDL_FE_HAS_DLL) && (OASIS_PDL_FE_HAS_DLL == 1)
#  if defined (OASIS_PDL_FE_BUILD_DLL)
#    define OASIS_PDL_FE_Export ACE_Proper_Export_Flag
#    define OASIS_PDL_FE_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define OASIS_PDL_FE_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* OASIS_PDL_FE_BUILD_DLL */
#    define OASIS_PDL_FE_Export ACE_Proper_Import_Flag
#    define OASIS_PDL_FE_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define OASIS_PDL_FE_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* OASIS_PDL_FE_BUILD_DLL */
#else /* OASIS_PDL_FE_HAS_DLL == 1 */
#  define OASIS_PDL_FE_Export
#  define OASIS_PDL_FE_SINGLETON_DECLARATION(T)
#  define OASIS_PDL_FE_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* OASIS_PDL_FE_HAS_DLL == 1 */

// Set OASIS_PDL_FE_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (OASIS_PDL_FE_NTRACE)
#  if (ACE_NTRACE == 1)
#    define OASIS_PDL_FE_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define OASIS_PDL_FE_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !OASIS_PDL_FE_NTRACE */

#if (OASIS_PDL_FE_NTRACE == 1)
#  define OASIS_PDL_FE_TRACE(X)
#else /* (OASIS_PDL_FE_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define OASIS_PDL_FE_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (OASIS_PDL_FE_NTRACE == 1) */

#endif /* OASIS_PDL_FE_EXPORT_H */

// End of auto generated file.
