// $Id$

#include "MemoryProbeImpl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{
  namespace System
  {
    namespace Memory
    {

      // 
      // MemoryProbeImpl
      // 
      MemoryProbeImpl::MemoryProbeImpl (void) 
      {
         this->uuid_ = this->metadata ().uuid_;
      }

      // 
      // MemoryProbeImpl::__metadata__
      // 
      const ::OASIS::System::Memory::MemoryProbe_Metadata MemoryProbeImpl::__metadata__ =
      ::OASIS::System::Memory::MemoryProbe_Metadata ();


      // 
      // MemoryProbeImpl::metadata
      // 
      const ::OASIS::System::Memory::MemoryProbe_Metadata & MemoryProbeImpl::metadata (void) const 
      {
        return ::OASIS::System::Memory::MemoryProbeImpl::__metadata__;
      }

      // 
      // ~MemoryProbeImpl
      // 
      MemoryProbeImpl::~MemoryProbeImpl (void) 
      {
      }

      // 
      // package_data
      // 
      int MemoryProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
      {
        if (0 != ::OASIS::Software_Probe_Impl::package_data (p))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                            -1);
        if (!(p.data_stream () << this->physical_memory_avail_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package physical_memory_avail\n")),
                            -1);

        if (!(p.data_stream () << this->physical_memory_total_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package physical_memory_total\n")),
                            -1);

        if (!(p.data_stream () << this->system_cache_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package system_cache\n")),
                            -1);

        if (!(p.data_stream () << this->commit_limit_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package commit_limit\n")),
                            -1);

        if (!(p.data_stream () << this->commit_total_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package commit_total\n")),
                            -1);

        if (!(p.data_stream () << this->virtual_total_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package virtual_total\n")),
                            -1);

        if (!(p.data_stream () << this->virtual_used_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package virtual_used\n")),
                            -1);

        return p.data_stream ().good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void MemoryProbeImpl::dump (std::ostream & output) 
      {
        ::OASIS::Software_Probe_Impl::dump (output);
        output << "  physical_memory_avail: " << this->physical_memory_avail () << std::endl;
        output << "  physical_memory_total: " << this->physical_memory_total () << std::endl;
        output << "  system_cache: " << this->system_cache () << std::endl;
        output << "  commit_limit: " << this->commit_limit () << std::endl;
        output << "  commit_total: " << this->commit_total () << std::endl;
        output << "  virtual_total: " << this->virtual_total () << std::endl;
        output << "  virtual_used: " << this->virtual_used () << std::endl;
      }

      // 
      // physical_memory_avail
      // 
      void MemoryProbeImpl::physical_memory_avail (ACE_UINT64 physical_memory_avail)
      {
        this->physical_memory_avail_ = physical_memory_avail;
      }

      // 
      // physical_memory_avail
      // 
      ACE_UINT64 MemoryProbeImpl::physical_memory_avail (void) const
      {
        return this->physical_memory_avail_;
      }

      // 
      // physical_memory_total
      // 
      void MemoryProbeImpl::physical_memory_total (ACE_UINT64 physical_memory_total)
      {
        this->physical_memory_total_ = physical_memory_total;
      }

      // 
      // physical_memory_total
      // 
      ACE_UINT64 MemoryProbeImpl::physical_memory_total (void) const
      {
        return this->physical_memory_total_;
      }

      // 
      // system_cache
      // 
      void MemoryProbeImpl::system_cache (ACE_UINT64 system_cache)
      {
        this->system_cache_ = system_cache;
      }

      // 
      // system_cache
      // 
      ACE_UINT64 MemoryProbeImpl::system_cache (void) const
      {
        return this->system_cache_;
      }

      // 
      // commit_limit
      // 
      void MemoryProbeImpl::commit_limit (ACE_UINT64 commit_limit)
      {
        this->commit_limit_ = commit_limit;
      }

      // 
      // commit_limit
      // 
      ACE_UINT64 MemoryProbeImpl::commit_limit (void) const
      {
        return this->commit_limit_;
      }

      // 
      // commit_total
      // 
      void MemoryProbeImpl::commit_total (ACE_UINT64 commit_total)
      {
        this->commit_total_ = commit_total;
      }

      // 
      // commit_total
      // 
      ACE_UINT64 MemoryProbeImpl::commit_total (void) const
      {
        return this->commit_total_;
      }

      // 
      // virtual_total
      // 
      void MemoryProbeImpl::virtual_total (ACE_UINT64 virtual_total)
      {
        this->virtual_total_ = virtual_total;
      }

      // 
      // virtual_total
      // 
      ACE_UINT64 MemoryProbeImpl::virtual_total (void) const
      {
        return this->virtual_total_;
      }

      // 
      // virtual_used
      // 
      void MemoryProbeImpl::virtual_used (ACE_UINT64 virtual_used)
      {
        this->virtual_used_ = virtual_used;
      }

      // 
      // virtual_used
      // 
      ACE_UINT64 MemoryProbeImpl::virtual_used (void) const
      {
        return this->virtual_used_;
      }


      // 
      // LinuxMemoryProbeImpl
      // 
      LinuxMemoryProbeImpl::LinuxMemoryProbeImpl (void) 
      {
         this->uuid_ = this->metadata ().uuid_;
      }

      // 
      // LinuxMemoryProbeImpl::__metadata__
      // 
      const ::OASIS::System::Memory::LinuxMemoryProbe_Metadata LinuxMemoryProbeImpl::__metadata__ =
      ::OASIS::System::Memory::LinuxMemoryProbe_Metadata ();


      // 
      // LinuxMemoryProbeImpl::metadata
      // 
      const ::OASIS::System::Memory::LinuxMemoryProbe_Metadata & LinuxMemoryProbeImpl::metadata (void) const 
      {
        return ::OASIS::System::Memory::LinuxMemoryProbeImpl::__metadata__;
      }

      // 
      // ~LinuxMemoryProbeImpl
      // 
      LinuxMemoryProbeImpl::~LinuxMemoryProbeImpl (void) 
      {
      }

      // 
      // package_data
      // 
      int LinuxMemoryProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
      {
        if (0 != ::OASIS::System::Memory::MemoryProbeImpl::package_data (p))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                            -1);
        if (!(p.data_stream () << this->buffers_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package buffers\n")),
                            -1);

        if (!(p.data_stream () << this->swap_cache_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package swap_cache\n")),
                            -1);

        if (!(p.data_stream () << this->inactive_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package inactive\n")),
                            -1);

        if (!(p.data_stream () << this->active_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package active\n")),
                            -1);

        if (!(p.data_stream () << this->high_total_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package high_total\n")),
                            -1);

        if (!(p.data_stream () << this->high_free_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package high_free\n")),
                            -1);

        if (!(p.data_stream () << this->low_total_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package low_total\n")),
                            -1);

        if (!(p.data_stream () << this->low_free_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package low_free\n")),
                            -1);

        if (!(p.data_stream () << this->swap_total_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package swap_total\n")),
                            -1);

        if (!(p.data_stream () << this->swap_free_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package swap_free\n")),
                            -1);

        if (!(p.data_stream () << this->dirty_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package dirty\n")),
                            -1);

        if (!(p.data_stream () << this->write_back_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package write_back\n")),
                            -1);

        if (!(p.data_stream () << this->virtual_chunk_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package virtual_chunk\n")),
                            -1);

        return p.data_stream ().good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void LinuxMemoryProbeImpl::dump (std::ostream & output) 
      {
        ::OASIS::System::Memory::MemoryProbeImpl::dump (output);
        output << "  buffers: " << this->buffers () << std::endl;
        output << "  swap_cache: " << this->swap_cache () << std::endl;
        output << "  inactive: " << this->inactive () << std::endl;
        output << "  active: " << this->active () << std::endl;
        output << "  high_total: " << this->high_total () << std::endl;
        output << "  high_free: " << this->high_free () << std::endl;
        output << "  low_total: " << this->low_total () << std::endl;
        output << "  low_free: " << this->low_free () << std::endl;
        output << "  swap_total: " << this->swap_total () << std::endl;
        output << "  swap_free: " << this->swap_free () << std::endl;
        output << "  dirty: " << this->dirty () << std::endl;
        output << "  write_back: " << this->write_back () << std::endl;
        output << "  virtual_chunk: " << this->virtual_chunk () << std::endl;
      }

      // 
      // buffers
      // 
      void LinuxMemoryProbeImpl::buffers (ACE_UINT64 buffers)
      {
        this->buffers_ = buffers;
      }

      // 
      // buffers
      // 
      ACE_UINT64 LinuxMemoryProbeImpl::buffers (void) const
      {
        return this->buffers_;
      }

      // 
      // swap_cache
      // 
      void LinuxMemoryProbeImpl::swap_cache (ACE_UINT64 swap_cache)
      {
        this->swap_cache_ = swap_cache;
      }

      // 
      // swap_cache
      // 
      ACE_UINT64 LinuxMemoryProbeImpl::swap_cache (void) const
      {
        return this->swap_cache_;
      }

      // 
      // inactive
      // 
      void LinuxMemoryProbeImpl::inactive (ACE_UINT64 inactive)
      {
        this->inactive_ = inactive;
      }

      // 
      // inactive
      // 
      ACE_UINT64 LinuxMemoryProbeImpl::inactive (void) const
      {
        return this->inactive_;
      }

      // 
      // active
      // 
      void LinuxMemoryProbeImpl::active (ACE_UINT64 active)
      {
        this->active_ = active;
      }

      // 
      // active
      // 
      ACE_UINT64 LinuxMemoryProbeImpl::active (void) const
      {
        return this->active_;
      }

      // 
      // high_total
      // 
      void LinuxMemoryProbeImpl::high_total (ACE_UINT64 high_total)
      {
        this->high_total_ = high_total;
      }

      // 
      // high_total
      // 
      ACE_UINT64 LinuxMemoryProbeImpl::high_total (void) const
      {
        return this->high_total_;
      }

      // 
      // high_free
      // 
      void LinuxMemoryProbeImpl::high_free (ACE_UINT64 high_free)
      {
        this->high_free_ = high_free;
      }

      // 
      // high_free
      // 
      ACE_UINT64 LinuxMemoryProbeImpl::high_free (void) const
      {
        return this->high_free_;
      }

      // 
      // low_total
      // 
      void LinuxMemoryProbeImpl::low_total (ACE_UINT64 low_total)
      {
        this->low_total_ = low_total;
      }

      // 
      // low_total
      // 
      ACE_UINT64 LinuxMemoryProbeImpl::low_total (void) const
      {
        return this->low_total_;
      }

      // 
      // low_free
      // 
      void LinuxMemoryProbeImpl::low_free (ACE_UINT64 low_free)
      {
        this->low_free_ = low_free;
      }

      // 
      // low_free
      // 
      ACE_UINT64 LinuxMemoryProbeImpl::low_free (void) const
      {
        return this->low_free_;
      }

      // 
      // swap_total
      // 
      void LinuxMemoryProbeImpl::swap_total (ACE_UINT64 swap_total)
      {
        this->swap_total_ = swap_total;
      }

      // 
      // swap_total
      // 
      ACE_UINT64 LinuxMemoryProbeImpl::swap_total (void) const
      {
        return this->swap_total_;
      }

      // 
      // swap_free
      // 
      void LinuxMemoryProbeImpl::swap_free (ACE_UINT64 swap_free)
      {
        this->swap_free_ = swap_free;
      }

      // 
      // swap_free
      // 
      ACE_UINT64 LinuxMemoryProbeImpl::swap_free (void) const
      {
        return this->swap_free_;
      }

      // 
      // dirty
      // 
      void LinuxMemoryProbeImpl::dirty (ACE_UINT64 dirty)
      {
        this->dirty_ = dirty;
      }

      // 
      // dirty
      // 
      ACE_UINT64 LinuxMemoryProbeImpl::dirty (void) const
      {
        return this->dirty_;
      }

      // 
      // write_back
      // 
      void LinuxMemoryProbeImpl::write_back (ACE_UINT64 write_back)
      {
        this->write_back_ = write_back;
      }

      // 
      // write_back
      // 
      ACE_UINT64 LinuxMemoryProbeImpl::write_back (void) const
      {
        return this->write_back_;
      }

      // 
      // virtual_chunk
      // 
      void LinuxMemoryProbeImpl::virtual_chunk (ACE_UINT64 virtual_chunk)
      {
        this->virtual_chunk_ = virtual_chunk;
      }

      // 
      // virtual_chunk
      // 
      ACE_UINT64 LinuxMemoryProbeImpl::virtual_chunk (void) const
      {
        return this->virtual_chunk_;
      }


      // 
      // WindowsMemoryProbeImpl
      // 
      WindowsMemoryProbeImpl::WindowsMemoryProbeImpl (void) 
      {
         this->uuid_ = this->metadata ().uuid_;
      }

      // 
      // WindowsMemoryProbeImpl::__metadata__
      // 
      const ::OASIS::System::Memory::WindowsMemoryProbe_Metadata WindowsMemoryProbeImpl::__metadata__ =
      ::OASIS::System::Memory::WindowsMemoryProbe_Metadata ();


      // 
      // WindowsMemoryProbeImpl::metadata
      // 
      const ::OASIS::System::Memory::WindowsMemoryProbe_Metadata & WindowsMemoryProbeImpl::metadata (void) const 
      {
        return ::OASIS::System::Memory::WindowsMemoryProbeImpl::__metadata__;
      }

      // 
      // ~WindowsMemoryProbeImpl
      // 
      WindowsMemoryProbeImpl::~WindowsMemoryProbeImpl (void) 
      {
      }

      // 
      // package_data
      // 
      int WindowsMemoryProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
      {
        if (0 != ::OASIS::System::Memory::MemoryProbeImpl::package_data (p))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                            -1);
        if (!(p.data_stream () << this->page_file_total_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package page_file_total\n")),
                            -1);

        if (!(p.data_stream () << this->page_file_avail_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package page_file_avail\n")),
                            -1);

        if (!(p.data_stream () << this->kernel_total_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package kernel_total\n")),
                            -1);

        if (!(p.data_stream () << this->kernel_paged_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package kernel_paged\n")),
                            -1);

        if (!(p.data_stream () << this->kernel_nonpaged_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package kernel_nonpaged\n")),
                            -1);

        if (!(p.data_stream () << this->page_size_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package page_size\n")),
                            -1);

        if (!(p.data_stream () << this->commit_peak_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package commit_peak\n")),
                            -1);

        return p.data_stream ().good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void WindowsMemoryProbeImpl::dump (std::ostream & output) 
      {
        ::OASIS::System::Memory::MemoryProbeImpl::dump (output);
        output << "  page_file_total: " << this->page_file_total () << std::endl;
        output << "  page_file_avail: " << this->page_file_avail () << std::endl;
        output << "  kernel_total: " << this->kernel_total () << std::endl;
        output << "  kernel_paged: " << this->kernel_paged () << std::endl;
        output << "  kernel_nonpaged: " << this->kernel_nonpaged () << std::endl;
        output << "  page_size: " << this->page_size () << std::endl;
        output << "  commit_peak: " << this->commit_peak () << std::endl;
      }

      // 
      // page_file_total
      // 
      void WindowsMemoryProbeImpl::page_file_total (ACE_UINT64 page_file_total)
      {
        this->page_file_total_ = page_file_total;
      }

      // 
      // page_file_total
      // 
      ACE_UINT64 WindowsMemoryProbeImpl::page_file_total (void) const
      {
        return this->page_file_total_;
      }

      // 
      // page_file_avail
      // 
      void WindowsMemoryProbeImpl::page_file_avail (ACE_UINT64 page_file_avail)
      {
        this->page_file_avail_ = page_file_avail;
      }

      // 
      // page_file_avail
      // 
      ACE_UINT64 WindowsMemoryProbeImpl::page_file_avail (void) const
      {
        return this->page_file_avail_;
      }

      // 
      // kernel_total
      // 
      void WindowsMemoryProbeImpl::kernel_total (ACE_UINT64 kernel_total)
      {
        this->kernel_total_ = kernel_total;
      }

      // 
      // kernel_total
      // 
      ACE_UINT64 WindowsMemoryProbeImpl::kernel_total (void) const
      {
        return this->kernel_total_;
      }

      // 
      // kernel_paged
      // 
      void WindowsMemoryProbeImpl::kernel_paged (ACE_UINT64 kernel_paged)
      {
        this->kernel_paged_ = kernel_paged;
      }

      // 
      // kernel_paged
      // 
      ACE_UINT64 WindowsMemoryProbeImpl::kernel_paged (void) const
      {
        return this->kernel_paged_;
      }

      // 
      // kernel_nonpaged
      // 
      void WindowsMemoryProbeImpl::kernel_nonpaged (ACE_UINT64 kernel_nonpaged)
      {
        this->kernel_nonpaged_ = kernel_nonpaged;
      }

      // 
      // kernel_nonpaged
      // 
      ACE_UINT64 WindowsMemoryProbeImpl::kernel_nonpaged (void) const
      {
        return this->kernel_nonpaged_;
      }

      // 
      // page_size
      // 
      void WindowsMemoryProbeImpl::page_size (ACE_UINT64 page_size)
      {
        this->page_size_ = page_size;
      }

      // 
      // page_size
      // 
      ACE_UINT64 WindowsMemoryProbeImpl::page_size (void) const
      {
        return this->page_size_;
      }

      // 
      // commit_peak
      // 
      void WindowsMemoryProbeImpl::commit_peak (ACE_UINT64 commit_peak)
      {
        this->commit_peak_ = commit_peak;
      }

      // 
      // commit_peak
      // 
      ACE_UINT64 WindowsMemoryProbeImpl::commit_peak (void) const
      {
        return this->commit_peak_;
      }
    }
  }
}

