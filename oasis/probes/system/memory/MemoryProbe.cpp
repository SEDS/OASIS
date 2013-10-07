// $Id$

#include "MemoryProbe.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{
  namespace System
  {
    namespace Memory
    {

      // 
      // MemoryProbe::__metadata__
      // 
      const MemoryProbe::METADATA_TYPE MemoryProbe::__metadata__;

      // 
      // MemoryProbe::metadata
      // 
      const MemoryProbe::METADATA_TYPE & MemoryProbe::metadata (void) const 
      {
        return ::OASIS::System::Memory::MemoryProbe::__metadata__;
      }

      // 
      // MemoryProbe
      // 
      MemoryProbe::MemoryProbe (void) 
      {
      }

      // 
      // ~MemoryProbe
      // 
      MemoryProbe::~MemoryProbe (void) 
      {
      }

      // 
      // recall
      // 
      int MemoryProbe::
      recall (const char * data, size_t length, int byte_order) 
      {
        ::OASIS::Software_Probe_Data_Preparer prep (data, length);
        ACE_InputCDR input (prep.message_block (), byte_order);
        return ::OASIS::System::Memory::MemoryProbe::recall (input);
      }


      // 
      // recall
      // 
      int MemoryProbe::recall (ACE_InputCDR & in) 
      {
        if (0 != ::OASIS::Software_Probe::recall (in))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to recall ")
                             ACE_TEXT ("::OASIS::Software_Probe data\n")),
                            -1);

        if (!(in >> this->physical_memory_avail_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage physical_memory_avail\n")),
                            -1);

        if (!(in >> this->physical_memory_total_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage physical_memory_total\n")),
                            -1);

        if (!(in >> this->system_cache_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage system_cache\n")),
                            -1);

        if (!(in >> this->commit_limit_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage commit_limit\n")),
                            -1);

        if (!(in >> this->commit_total_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage commit_total\n")),
                            -1);

        if (!(in >> this->virtual_total_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage virtual_total\n")),
                            -1);

        if (!(in >> this->virtual_used_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage virtual_used\n")),
                            -1);

        return in.good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void MemoryProbe::dump (std::ostream & output) 
      {
        ::OASIS::Software_Probe::dump (output);
        output << "  physical_memory_avail: " << this->physical_memory_avail_ << std::endl;
        output << "  physical_memory_total: " << this->physical_memory_total_ << std::endl;
        output << "  system_cache: " << this->system_cache_ << std::endl;
        output << "  commit_limit: " << this->commit_limit_ << std::endl;
        output << "  commit_total: " << this->commit_total_ << std::endl;
        output << "  virtual_total: " << this->virtual_total_ << std::endl;
        output << "  virtual_used: " << this->virtual_used_ << std::endl;
      }

      // 
      // physical_memory_avail
      // 
      ACE_UINT64 MemoryProbe::physical_memory_avail (void) const
      {
        return this->physical_memory_avail_;
      }

      // 
      // physical_memory_total
      // 
      ACE_UINT64 MemoryProbe::physical_memory_total (void) const
      {
        return this->physical_memory_total_;
      }

      // 
      // system_cache
      // 
      ACE_UINT64 MemoryProbe::system_cache (void) const
      {
        return this->system_cache_;
      }

      // 
      // commit_limit
      // 
      ACE_UINT64 MemoryProbe::commit_limit (void) const
      {
        return this->commit_limit_;
      }

      // 
      // commit_total
      // 
      ACE_UINT64 MemoryProbe::commit_total (void) const
      {
        return this->commit_total_;
      }

      // 
      // virtual_total
      // 
      ACE_UINT64 MemoryProbe::virtual_total (void) const
      {
        return this->virtual_total_;
      }

      // 
      // virtual_used
      // 
      ACE_UINT64 MemoryProbe::virtual_used (void) const
      {
        return this->virtual_used_;
      }


      // 
      // LinuxMemoryProbe::__metadata__
      // 
      const LinuxMemoryProbe::METADATA_TYPE LinuxMemoryProbe::__metadata__;

      // 
      // LinuxMemoryProbe::metadata
      // 
      const LinuxMemoryProbe::METADATA_TYPE & LinuxMemoryProbe::metadata (void) const 
      {
        return ::OASIS::System::Memory::LinuxMemoryProbe::__metadata__;
      }

      // 
      // LinuxMemoryProbe
      // 
      LinuxMemoryProbe::LinuxMemoryProbe (void) 
      {
      }

      // 
      // ~LinuxMemoryProbe
      // 
      LinuxMemoryProbe::~LinuxMemoryProbe (void) 
      {
      }

      // 
      // recall
      // 
      int LinuxMemoryProbe::
      recall (const char * data, size_t length, int byte_order) 
      {
        ::OASIS::Software_Probe_Data_Preparer prep (data, length);
        ACE_InputCDR input (prep.message_block (), byte_order);
        return ::OASIS::System::Memory::LinuxMemoryProbe::recall (input);
      }


      // 
      // recall
      // 
      int LinuxMemoryProbe::recall (ACE_InputCDR & in) 
      {
        if (0 != ::OASIS::System::Memory::MemoryProbe::recall (in))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to recall ")
                             ACE_TEXT ("::OASIS::System::Memory::MemoryProbe data\n")),
                            -1);

        if (!(in >> this->buffers_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage buffers\n")),
                            -1);

        if (!(in >> this->swap_cache_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage swap_cache\n")),
                            -1);

        if (!(in >> this->inactive_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage inactive\n")),
                            -1);

        if (!(in >> this->active_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage active\n")),
                            -1);

        if (!(in >> this->high_total_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage high_total\n")),
                            -1);

        if (!(in >> this->high_free_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage high_free\n")),
                            -1);

        if (!(in >> this->low_total_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage low_total\n")),
                            -1);

        if (!(in >> this->low_free_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage low_free\n")),
                            -1);

        if (!(in >> this->swap_total_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage swap_total\n")),
                            -1);

        if (!(in >> this->swap_free_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage swap_free\n")),
                            -1);

        if (!(in >> this->dirty_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage dirty\n")),
                            -1);

        if (!(in >> this->write_back_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage write_back\n")),
                            -1);

        if (!(in >> this->virtual_chunk_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage virtual_chunk\n")),
                            -1);

        return in.good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void LinuxMemoryProbe::dump (std::ostream & output) 
      {
        ::OASIS::System::Memory::MemoryProbe::dump (output);
        output << "  buffers: " << this->buffers_ << std::endl;
        output << "  swap_cache: " << this->swap_cache_ << std::endl;
        output << "  inactive: " << this->inactive_ << std::endl;
        output << "  active: " << this->active_ << std::endl;
        output << "  high_total: " << this->high_total_ << std::endl;
        output << "  high_free: " << this->high_free_ << std::endl;
        output << "  low_total: " << this->low_total_ << std::endl;
        output << "  low_free: " << this->low_free_ << std::endl;
        output << "  swap_total: " << this->swap_total_ << std::endl;
        output << "  swap_free: " << this->swap_free_ << std::endl;
        output << "  dirty: " << this->dirty_ << std::endl;
        output << "  write_back: " << this->write_back_ << std::endl;
        output << "  virtual_chunk: " << this->virtual_chunk_ << std::endl;
      }

      // 
      // buffers
      // 
      ACE_UINT64 LinuxMemoryProbe::buffers (void) const
      {
        return this->buffers_;
      }

      // 
      // swap_cache
      // 
      ACE_UINT64 LinuxMemoryProbe::swap_cache (void) const
      {
        return this->swap_cache_;
      }

      // 
      // inactive
      // 
      ACE_UINT64 LinuxMemoryProbe::inactive (void) const
      {
        return this->inactive_;
      }

      // 
      // active
      // 
      ACE_UINT64 LinuxMemoryProbe::active (void) const
      {
        return this->active_;
      }

      // 
      // high_total
      // 
      ACE_UINT64 LinuxMemoryProbe::high_total (void) const
      {
        return this->high_total_;
      }

      // 
      // high_free
      // 
      ACE_UINT64 LinuxMemoryProbe::high_free (void) const
      {
        return this->high_free_;
      }

      // 
      // low_total
      // 
      ACE_UINT64 LinuxMemoryProbe::low_total (void) const
      {
        return this->low_total_;
      }

      // 
      // low_free
      // 
      ACE_UINT64 LinuxMemoryProbe::low_free (void) const
      {
        return this->low_free_;
      }

      // 
      // swap_total
      // 
      ACE_UINT64 LinuxMemoryProbe::swap_total (void) const
      {
        return this->swap_total_;
      }

      // 
      // swap_free
      // 
      ACE_UINT64 LinuxMemoryProbe::swap_free (void) const
      {
        return this->swap_free_;
      }

      // 
      // dirty
      // 
      ACE_UINT64 LinuxMemoryProbe::dirty (void) const
      {
        return this->dirty_;
      }

      // 
      // write_back
      // 
      ACE_UINT64 LinuxMemoryProbe::write_back (void) const
      {
        return this->write_back_;
      }

      // 
      // virtual_chunk
      // 
      ACE_UINT64 LinuxMemoryProbe::virtual_chunk (void) const
      {
        return this->virtual_chunk_;
      }


      // 
      // WindowsMemoryProbe::__metadata__
      // 
      const WindowsMemoryProbe::METADATA_TYPE WindowsMemoryProbe::__metadata__;

      // 
      // WindowsMemoryProbe::metadata
      // 
      const WindowsMemoryProbe::METADATA_TYPE & WindowsMemoryProbe::metadata (void) const 
      {
        return ::OASIS::System::Memory::WindowsMemoryProbe::__metadata__;
      }

      // 
      // WindowsMemoryProbe
      // 
      WindowsMemoryProbe::WindowsMemoryProbe (void) 
      {
      }

      // 
      // ~WindowsMemoryProbe
      // 
      WindowsMemoryProbe::~WindowsMemoryProbe (void) 
      {
      }

      // 
      // recall
      // 
      int WindowsMemoryProbe::
      recall (const char * data, size_t length, int byte_order) 
      {
        ::OASIS::Software_Probe_Data_Preparer prep (data, length);
        ACE_InputCDR input (prep.message_block (), byte_order);
        return ::OASIS::System::Memory::WindowsMemoryProbe::recall (input);
      }


      // 
      // recall
      // 
      int WindowsMemoryProbe::recall (ACE_InputCDR & in) 
      {
        if (0 != ::OASIS::System::Memory::MemoryProbe::recall (in))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to recall ")
                             ACE_TEXT ("::OASIS::System::Memory::MemoryProbe data\n")),
                            -1);

        if (!(in >> this->page_file_total_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage page_file_total\n")),
                            -1);

        if (!(in >> this->page_file_avail_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage page_file_avail\n")),
                            -1);

        if (!(in >> this->kernel_total_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage kernel_total\n")),
                            -1);

        if (!(in >> this->kernel_paged_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage kernel_paged\n")),
                            -1);

        if (!(in >> this->kernel_nonpaged_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage kernel_nonpaged\n")),
                            -1);

        if (!(in >> this->page_size_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage page_size\n")),
                            -1);

        if (!(in >> this->commit_peak_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage commit_peak\n")),
                            -1);

        return in.good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void WindowsMemoryProbe::dump (std::ostream & output) 
      {
        ::OASIS::System::Memory::MemoryProbe::dump (output);
        output << "  page_file_total: " << this->page_file_total_ << std::endl;
        output << "  page_file_avail: " << this->page_file_avail_ << std::endl;
        output << "  kernel_total: " << this->kernel_total_ << std::endl;
        output << "  kernel_paged: " << this->kernel_paged_ << std::endl;
        output << "  kernel_nonpaged: " << this->kernel_nonpaged_ << std::endl;
        output << "  page_size: " << this->page_size_ << std::endl;
        output << "  commit_peak: " << this->commit_peak_ << std::endl;
      }

      // 
      // page_file_total
      // 
      ACE_UINT64 WindowsMemoryProbe::page_file_total (void) const
      {
        return this->page_file_total_;
      }

      // 
      // page_file_avail
      // 
      ACE_UINT64 WindowsMemoryProbe::page_file_avail (void) const
      {
        return this->page_file_avail_;
      }

      // 
      // kernel_total
      // 
      ACE_UINT64 WindowsMemoryProbe::kernel_total (void) const
      {
        return this->kernel_total_;
      }

      // 
      // kernel_paged
      // 
      ACE_UINT64 WindowsMemoryProbe::kernel_paged (void) const
      {
        return this->kernel_paged_;
      }

      // 
      // kernel_nonpaged
      // 
      ACE_UINT64 WindowsMemoryProbe::kernel_nonpaged (void) const
      {
        return this->kernel_nonpaged_;
      }

      // 
      // page_size
      // 
      ACE_UINT64 WindowsMemoryProbe::page_size (void) const
      {
        return this->page_size_;
      }

      // 
      // commit_peak
      // 
      ACE_UINT64 WindowsMemoryProbe::commit_peak (void) const
      {
        return this->commit_peak_;
      }
    }
  }
}

