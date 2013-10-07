#ifndef OASIS_PINTOOL_SIMPLE_EXAMPLE_EXPORT_H
#define OASIS_PINTOOL_SIMPLE_EXAMPLE_EXPORT_H

#if !defined(OASIS_PINTOOL_SIMPLE_EXAMPLE_HAS_DLL)
# if defined(OASIS_PINTOOL_SIMPLE_EXAMPLE_AS_STATIC_LIBS)
#   define OASIS_PINTOOL_SIMPLE_EXAMPLE_HAS_DLL 0
# else
#   define OASIS_PINTOOL_SIMPLE_EXAMPLE_HAS_DLL 1
# endif
#endif

#if (OASIS_PINTOOL_SIMPLE_EXAMPLE_HAS_DLL == 1)
#  if defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x550)
#    if defined(OASIS_PINTOOL_SIMPLE_EXAMPLE_BUILD_DLL)
#      define OASIS_PINTOOL_SIMPLE_EXAMPLE_Export __symbolic
#    else
#      define OASIS_PINTOOL_SIMPLE_EXAMPLE_Export __global
#    endif
#  elif defined(WIN32) || defined(UNDER_CE) || defined(__CYGWIN__)
#    if defined(OASIS_PINTOOL_SIMPLE_EXAMPLE_BUILD_DLL)
#      define OASIS_PINTOOL_SIMPLE_EXAMPLE_Export __declspec(dllexport)
#    else
#      define OASIS_PINTOOL_SIMPLE_EXAMPLE_Export __declspec(dllimport)
#    endif
#  elif (defined(__GNUC__) && (__GNUC__ >= 4))
#    if defined(OASIS_PINTOOL_SIMPLE_EXAMPLE_BUILD_DLL)
#      define OASIS_PINTOOL_SIMPLE_EXAMPLE_Export __attribute__((visibility("default")))
#    else
#      define OASIS_PINTOOL_SIMPLE_EXAMPLE_Export
#    endif
#  else
#    define OASIS_PINTOOL_SIMPLE_EXAMPLE_Export
#  endif
#else
#  define OASIS_PINTOOL_SIMPLE_EXAMPLE_Export
#endif

#endif
