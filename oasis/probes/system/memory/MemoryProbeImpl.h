// -*- C++ -*-

//============================================================================
/**
 * @file        MemoryProbeImpl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _MEMORYPROBEIMPL_H_
#define _MEMORYPROBEIMPL_H_

#include "oasis/probes/Data_Types.h"
#include "MemoryProbe_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

#include "MemoryProbe_stub_export.h"

namespace OASIS
{
  namespace System
  {
    namespace Memory
    {
      /**
       * @class MemoryProbeImpl
       */
      class OASIS_MEMORYPROBE_STUB_Export MemoryProbeImpl :
        public virtual ::OASIS::Software_Probe_Impl
      {
        public:
        /// The metadata for the software probe.
        static const ::OASIS::System::Memory::MemoryProbe_Metadata __metadata__;

        /// Default constructor
        MemoryProbeImpl (void);

        /// Destructor
        virtual ~MemoryProbeImpl (void) = 0;

        /// Getter for the probe's metadata
        virtual const ::OASIS::System::Memory::MemoryProbe_Metadata & metadata (void) const;

        /// Package the software probe's data.
        protected:
        virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


        public:
        /// Impl_Dump the software probe's data.
        virtual void dump (std::ostream & output);


        public:
        // Setter and getter methods for physical_memory_avail
        void physical_memory_avail (ACE_UINT64 physical_memory_avail);
        ACE_UINT64 physical_memory_avail (void) const;

        // Setter and getter methods for physical_memory_total
        void physical_memory_total (ACE_UINT64 physical_memory_total);
        ACE_UINT64 physical_memory_total (void) const;

        // Setter and getter methods for system_cache
        void system_cache (ACE_UINT64 system_cache);
        ACE_UINT64 system_cache (void) const;

        // Setter and getter methods for commit_limit
        void commit_limit (ACE_UINT64 commit_limit);
        ACE_UINT64 commit_limit (void) const;

        // Setter and getter methods for commit_total
        void commit_total (ACE_UINT64 commit_total);
        ACE_UINT64 commit_total (void) const;

        // Setter and getter methods for virtual_total
        void virtual_total (ACE_UINT64 virtual_total);
        ACE_UINT64 virtual_total (void) const;

        // Setter and getter methods for virtual_used
        void virtual_used (ACE_UINT64 virtual_used);
        ACE_UINT64 virtual_used (void) const;

        protected:
        ACE_UINT64 physical_memory_avail_;

        ACE_UINT64 physical_memory_total_;

        ACE_UINT64 system_cache_;

        ACE_UINT64 commit_limit_;

        ACE_UINT64 commit_total_;

        ACE_UINT64 virtual_total_;

        ACE_UINT64 virtual_used_;
      };

      /**
       * @class LinuxMemoryProbeImpl
       */
      class OASIS_MEMORYPROBE_STUB_Export LinuxMemoryProbeImpl :
        public ::OASIS::System::Memory::MemoryProbeImpl
      {
        public:
        /// The metadata for the software probe.
        static const ::OASIS::System::Memory::LinuxMemoryProbe_Metadata __metadata__;

        /// Default constructor
        LinuxMemoryProbeImpl (void);

        /// Destructor
        virtual ~LinuxMemoryProbeImpl (void);

        /// Getter for the probe's metadata
        virtual const ::OASIS::System::Memory::LinuxMemoryProbe_Metadata & metadata (void) const;

        /// Package the software probe's data.
        protected:
        virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


        public:
        /// Impl_Dump the software probe's data.
        virtual void dump (std::ostream & output);


        public:
        // Setter and getter methods for buffers
        void buffers (ACE_UINT64 buffers);
        ACE_UINT64 buffers (void) const;

        // Setter and getter methods for swap_cache
        void swap_cache (ACE_UINT64 swap_cache);
        ACE_UINT64 swap_cache (void) const;

        // Setter and getter methods for inactive
        void inactive (ACE_UINT64 inactive);
        ACE_UINT64 inactive (void) const;

        // Setter and getter methods for active
        void active (ACE_UINT64 active);
        ACE_UINT64 active (void) const;

        // Setter and getter methods for high_total
        void high_total (ACE_UINT64 high_total);
        ACE_UINT64 high_total (void) const;

        // Setter and getter methods for high_free
        void high_free (ACE_UINT64 high_free);
        ACE_UINT64 high_free (void) const;

        // Setter and getter methods for low_total
        void low_total (ACE_UINT64 low_total);
        ACE_UINT64 low_total (void) const;

        // Setter and getter methods for low_free
        void low_free (ACE_UINT64 low_free);
        ACE_UINT64 low_free (void) const;

        // Setter and getter methods for swap_total
        void swap_total (ACE_UINT64 swap_total);
        ACE_UINT64 swap_total (void) const;

        // Setter and getter methods for swap_free
        void swap_free (ACE_UINT64 swap_free);
        ACE_UINT64 swap_free (void) const;

        // Setter and getter methods for dirty
        void dirty (ACE_UINT64 dirty);
        ACE_UINT64 dirty (void) const;

        // Setter and getter methods for write_back
        void write_back (ACE_UINT64 write_back);
        ACE_UINT64 write_back (void) const;

        // Setter and getter methods for virtual_chunk
        void virtual_chunk (ACE_UINT64 virtual_chunk);
        ACE_UINT64 virtual_chunk (void) const;

        protected:
        ACE_UINT64 buffers_;

        ACE_UINT64 swap_cache_;

        ACE_UINT64 inactive_;

        ACE_UINT64 active_;

        ACE_UINT64 high_total_;

        ACE_UINT64 high_free_;

        ACE_UINT64 low_total_;

        ACE_UINT64 low_free_;

        ACE_UINT64 swap_total_;

        ACE_UINT64 swap_free_;

        ACE_UINT64 dirty_;

        ACE_UINT64 write_back_;

        ACE_UINT64 virtual_chunk_;
      };

      /**
       * @class WindowsMemoryProbeImpl
       */
      class OASIS_MEMORYPROBE_STUB_Export WindowsMemoryProbeImpl :
        public ::OASIS::System::Memory::MemoryProbeImpl
      {
        public:
        /// The metadata for the software probe.
        static const ::OASIS::System::Memory::WindowsMemoryProbe_Metadata __metadata__;

        /// Default constructor
        WindowsMemoryProbeImpl (void);

        /// Destructor
        virtual ~WindowsMemoryProbeImpl (void);

        /// Getter for the probe's metadata
        virtual const ::OASIS::System::Memory::WindowsMemoryProbe_Metadata & metadata (void) const;

        /// Package the software probe's data.
        protected:
        virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


        public:
        /// Impl_Dump the software probe's data.
        virtual void dump (std::ostream & output);


        public:
        // Setter and getter methods for page_file_total
        void page_file_total (ACE_UINT64 page_file_total);
        ACE_UINT64 page_file_total (void) const;

        // Setter and getter methods for page_file_avail
        void page_file_avail (ACE_UINT64 page_file_avail);
        ACE_UINT64 page_file_avail (void) const;

        // Setter and getter methods for kernel_total
        void kernel_total (ACE_UINT64 kernel_total);
        ACE_UINT64 kernel_total (void) const;

        // Setter and getter methods for kernel_paged
        void kernel_paged (ACE_UINT64 kernel_paged);
        ACE_UINT64 kernel_paged (void) const;

        // Setter and getter methods for kernel_nonpaged
        void kernel_nonpaged (ACE_UINT64 kernel_nonpaged);
        ACE_UINT64 kernel_nonpaged (void) const;

        // Setter and getter methods for page_size
        void page_size (ACE_UINT64 page_size);
        ACE_UINT64 page_size (void) const;

        // Setter and getter methods for commit_peak
        void commit_peak (ACE_UINT64 commit_peak);
        ACE_UINT64 commit_peak (void) const;

        protected:
        ACE_UINT64 page_file_total_;

        ACE_UINT64 page_file_avail_;

        ACE_UINT64 kernel_total_;

        ACE_UINT64 kernel_paged_;

        ACE_UINT64 kernel_nonpaged_;

        ACE_UINT64 page_size_;

        ACE_UINT64 commit_peak_;
      };
    }
  }
}

#endif  // !defined __MEMORYPROBEIMPL_H__

