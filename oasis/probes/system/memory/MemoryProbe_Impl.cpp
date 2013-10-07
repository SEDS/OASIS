// $Id: MemoryProbe_Impl.cpp 2154 2012-04-26 16:09:15Z dpuranik $

#include "MemoryProbe_Impl.h"
#include "ace/CORBA_macros.h"

#if defined (_WIN32)
#include <Psapi.h>
#else
#include "Meminfo_Parser.h"
#endif

namespace OASIS
{
namespace System
{
namespace Memory
{

//
// create_MemoryProbe_Impl_Factory
//
OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_IMPL (create_OASIS_System_Memory_MemoryProbe_Impl_Factory,
                                          MemoryProbe_Impl_Factory);

//
// MemoryProbe_Impl
//
MemoryProbe_Impl::MemoryProbe_Impl (void)
#if !defined (_WIN32)
  : parser_ (new Meminfo_Parser ())
#endif
{
}

//
// ~MemoryProbe_Impl
//
MemoryProbe_Impl::~MemoryProbe_Impl (void)
{
}

//
// handle_collect_data
//
int MemoryProbe_Impl::handle_collect_data (void)
{
#if defined (_WIN32)
  // Initialize the data structure.
  MEMORYSTATUSEX statex;
  statex.dwLength = sizeof (statex);

  if (!::GlobalMemoryStatusEx (&statex))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - GlobalMemoryStatusEx () failed\n")),
                       -1);

  // Copy over the values.
  this->physical_memory_avail_ = statex.ullAvailPhys;
  this->physical_memory_total_ = statex.ullTotalPhys;

  this->virtual_total_ = statex.ullTotalVirtual;
  this->virtual_used_ = statex.ullTotalVirtual - statex.ullAvailVirtual;

  // Get the remaining performance information.
  PERFORMANCE_INFORMATION perf_info;
  if (!::GetPerformanceInfo (&perf_info, sizeof (PERFORMANCE_INFORMATION)))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - GetPerformanceInfo () failed\n")),
                       -1);

  // Copy over the values.
  this->commit_total_ = perf_info.CommitTotal;
  this->commit_limit_ = perf_info.CommitLimit;
  this->commit_peak_ = perf_info.CommitPeak;

  this->page_file_total_ = this->commit_limit_ * perf_info.PageSize;
  this->page_file_avail_ = (this->commit_limit_ - this->commit_total_) * perf_info.PageSize;

  this->system_cache_ = perf_info.SystemCache;

  this->kernel_total_ = perf_info.KernelTotal;
  this->kernel_paged_ = perf_info.KernelPaged;
  this->kernel_nonpaged_ = perf_info.KernelNonpaged;

  this->page_size_ = perf_info.PageSize;

#else
  // Read the contents of /proc/meminfo.
  if (!this->parser_->read_data (this))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read the contents ")
                       ACE_TEXT ("of /proc/meminfo\n")),
                      -1);
#endif

  return 0;
}

}
}
}
