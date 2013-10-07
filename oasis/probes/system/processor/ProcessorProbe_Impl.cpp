// $Id: ProcessorProbe_Impl.cpp 1858 2011-08-18 03:13:41Z hillj $

#include "ace/ARGV.h"
#include "ace/CORBA_macros.h"
#include "ace/Get_Opt.h"

#include <sstream>
#include <fstream>

#include "ProcessorProbe_Impl.h"

#if !defined (_WIN32)
#include "Procstat_Parser.h"
#endif

#define MAKE_INT64(hi, lo) ((static_cast <ACE_UINT64> (hi) << 32) | lo);

namespace OASIS
{
namespace System
{
namespace Processor
{

//
// create_ProcessorProbe_Impl_Factory
//
OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_IMPL (create_OASIS_System_Processor_ProcessorProbe_Impl_Factory,
                                          ProcessorProbe_Impl_Factory);

//
// ProcessorProbe_Impl
//
ProcessorProbe_Impl::ProcessorProbe_Impl (void)
#if !defined (_WIN32)
  : parser_ (new Procstat_Parser ())
#endif
{

}

//
// ~ProcessorProbe_Impl
//
ProcessorProbe_Impl::~ProcessorProbe_Impl (void)
{

}

//
// handle_collect_data
//
int ProcessorProbe_Impl::handle_collect_data (void)
{
#if defined (_WIN32)
  FILETIME idle_time, system_time, user_time;

  if (0 == ::GetSystemTimes (&idle_time, &system_time, &user_time))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - GetSystemTimes () failed\n")),
                       -1);

  this->idle_time_ = MAKE_INT64 (idle_time.dwHighDateTime, idle_time.dwLowDateTime);
  this->user_time_ = MAKE_INT64 (user_time.dwHighDateTime, user_time.dwLowDateTime);
  this->system_time_ = MAKE_INT64 (system_time.dwHighDateTime, system_time.dwLowDateTime);
#else
  // Read the contents of /proc/stat.
  if (!this->parser_->read_data (this))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read the contents ")
                       ACE_TEXT ("of /proc/stat\n")),
                      -1);
#endif

  return 0;
}

}
}
}
