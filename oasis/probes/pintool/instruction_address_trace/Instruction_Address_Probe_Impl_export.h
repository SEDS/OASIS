
// -*- C++ -*-
// $Id: Instruction_Address_Probe_Impl_export.h 2239 2013-08-08 15:23:33Z dfeiock $
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl INSTRUCTION_ADDRESS_PROBE_IMPL
// ------------------------------
#ifndef INSTRUCTION_ADDRESS_PROBE_IMPL_EXPORT_H
#define INSTRUCTION_ADDRESS_PROBE_IMPL_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (INSTRUCTION_ADDRESS_PROBE_IMPL_HAS_DLL)
#  define INSTRUCTION_ADDRESS_PROBE_IMPL_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && INSTRUCTION_ADDRESS_PROBE_IMPL_HAS_DLL */

#if !defined (INSTRUCTION_ADDRESS_PROBE_IMPL_HAS_DLL)
#  define INSTRUCTION_ADDRESS_PROBE_IMPL_HAS_DLL 1
#endif /* ! INSTRUCTION_ADDRESS_PROBE_IMPL_HAS_DLL */

#if defined (INSTRUCTION_ADDRESS_PROBE_IMPL_HAS_DLL) && (INSTRUCTION_ADDRESS_PROBE_IMPL_HAS_DLL == 1)
#  if defined (INSTRUCTION_ADDRESS_PROBE_IMPL_BUILD_DLL)
#    define INSTRUCTION_ADDRESS_PROBE_IMPL_Export ACE_Proper_Export_Flag
#    define INSTRUCTION_ADDRESS_PROBE_IMPL_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define INSTRUCTION_ADDRESS_PROBE_IMPL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* INSTRUCTION_ADDRESS_PROBE_IMPL_BUILD_DLL */
#    define INSTRUCTION_ADDRESS_PROBE_IMPL_Export ACE_Proper_Import_Flag
#    define INSTRUCTION_ADDRESS_PROBE_IMPL_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define INSTRUCTION_ADDRESS_PROBE_IMPL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* INSTRUCTION_ADDRESS_PROBE_IMPL_BUILD_DLL */
#else /* INSTRUCTION_ADDRESS_PROBE_IMPL_HAS_DLL == 1 */
#  define INSTRUCTION_ADDRESS_PROBE_IMPL_Export
#  define INSTRUCTION_ADDRESS_PROBE_IMPL_SINGLETON_DECLARATION(T)
#  define INSTRUCTION_ADDRESS_PROBE_IMPL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* INSTRUCTION_ADDRESS_PROBE_IMPL_HAS_DLL == 1 */

// Set INSTRUCTION_ADDRESS_PROBE_IMPL_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (INSTRUCTION_ADDRESS_PROBE_IMPL_NTRACE)
#  if (ACE_NTRACE == 1)
#    define INSTRUCTION_ADDRESS_PROBE_IMPL_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define INSTRUCTION_ADDRESS_PROBE_IMPL_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !INSTRUCTION_ADDRESS_PROBE_IMPL_NTRACE */

#if (INSTRUCTION_ADDRESS_PROBE_IMPL_NTRACE == 1)
#  define INSTRUCTION_ADDRESS_PROBE_IMPL_TRACE(X)
#else /* (INSTRUCTION_ADDRESS_PROBE_IMPL_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define INSTRUCTION_ADDRESS_PROBE_IMPL_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (INSTRUCTION_ADDRESS_PROBE_IMPL_NTRACE == 1) */

#endif /* INSTRUCTION_ADDRESS_PROBE_IMPL_EXPORT_H */

// End of auto generated file.
