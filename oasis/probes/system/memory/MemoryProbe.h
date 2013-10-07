// -*- C++ -*-

//============================================================================
/**
 * @file        MemoryProbe.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _MEMORYPROBE_H_
#define _MEMORYPROBE_H_

#include "oasis/probes/Data_Types.h"
#include "oasis/probes/Software_Probe.h"
#include "MemoryProbe_Metadata.h"
#include <iostream>

#include "MemoryProbe_stub_export.h"

namespace OASIS
{
  namespace System
  {
    namespace Memory
    {
      /**
       * @class MemoryProbe
       */
      class OASIS_MEMORYPROBE_STUB_Export MemoryProbe :
        public virtual ::OASIS::Software_Probe 
      {
        public:
        // Type definition of the software probe's metadata.
        typedef ::OASIS::System::Memory::MemoryProbe_Metadata METADATA_TYPE;

        /// The metadata for the software probe.
        static const METADATA_TYPE __metadata__;

        /// Default constructor
        MemoryProbe (void);

        /// Destructor
        virtual ~MemoryProbe (void);

        /// Getter for the probe's metadata
        virtual const METADATA_TYPE & metadata (void) const;

        public:
        /// Recall the software probe's data.
        virtual int recall (const char * data, size_t length, int byte_order);

        protected:
        /// Helper method for recalling the data.
        int recall (ACE_InputCDR & input);

        public:
        /// Stub_Dump the software probe's data.
        virtual void dump (std::ostream & output);


        public:
        // Getter method for physical_memory_avail
        ACE_UINT64 physical_memory_avail (void) const;

        // Getter method for physical_memory_total
        ACE_UINT64 physical_memory_total (void) const;

        // Getter method for system_cache
        ACE_UINT64 system_cache (void) const;

        // Getter method for commit_limit
        ACE_UINT64 commit_limit (void) const;

        // Getter method for commit_total
        ACE_UINT64 commit_total (void) const;

        // Getter method for virtual_total
        ACE_UINT64 virtual_total (void) const;

        // Getter method for virtual_used
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
       * @class LinuxMemoryProbe
       */
      class OASIS_MEMORYPROBE_STUB_Export LinuxMemoryProbe :
        public ::OASIS::System::Memory::MemoryProbe 
      {
        public:
        // Type definition of the software probe's metadata.
        typedef ::OASIS::System::Memory::LinuxMemoryProbe_Metadata METADATA_TYPE;

        /// The metadata for the software probe.
        static const METADATA_TYPE __metadata__;

        /// Default constructor
        LinuxMemoryProbe (void);

        /// Destructor
        virtual ~LinuxMemoryProbe (void);

        /// Getter for the probe's metadata
        virtual const METADATA_TYPE & metadata (void) const;

        public:
        /// Recall the software probe's data.
        virtual int recall (const char * data, size_t length, int byte_order);

        protected:
        /// Helper method for recalling the data.
        int recall (ACE_InputCDR & input);

        public:
        /// Stub_Dump the software probe's data.
        virtual void dump (std::ostream & output);


        public:
        // Getter method for buffers
        ACE_UINT64 buffers (void) const;

        // Getter method for swap_cache
        ACE_UINT64 swap_cache (void) const;

        // Getter method for inactive
        ACE_UINT64 inactive (void) const;

        // Getter method for active
        ACE_UINT64 active (void) const;

        // Getter method for high_total
        ACE_UINT64 high_total (void) const;

        // Getter method for high_free
        ACE_UINT64 high_free (void) const;

        // Getter method for low_total
        ACE_UINT64 low_total (void) const;

        // Getter method for low_free
        ACE_UINT64 low_free (void) const;

        // Getter method for swap_total
        ACE_UINT64 swap_total (void) const;

        // Getter method for swap_free
        ACE_UINT64 swap_free (void) const;

        // Getter method for dirty
        ACE_UINT64 dirty (void) const;

        // Getter method for write_back
        ACE_UINT64 write_back (void) const;

        // Getter method for virtual_chunk
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
       * @class WindowsMemoryProbe
       */
      class OASIS_MEMORYPROBE_STUB_Export WindowsMemoryProbe :
        public ::OASIS::System::Memory::MemoryProbe 
      {
        public:
        // Type definition of the software probe's metadata.
        typedef ::OASIS::System::Memory::WindowsMemoryProbe_Metadata METADATA_TYPE;

        /// The metadata for the software probe.
        static const METADATA_TYPE __metadata__;

        /// Default constructor
        WindowsMemoryProbe (void);

        /// Destructor
        virtual ~WindowsMemoryProbe (void);

        /// Getter for the probe's metadata
        virtual const METADATA_TYPE & metadata (void) const;

        public:
        /// Recall the software probe's data.
        virtual int recall (const char * data, size_t length, int byte_order);

        protected:
        /// Helper method for recalling the data.
        int recall (ACE_InputCDR & input);

        public:
        /// Stub_Dump the software probe's data.
        virtual void dump (std::ostream & output);


        public:
        // Getter method for page_file_total
        ACE_UINT64 page_file_total (void) const;

        // Getter method for page_file_avail
        ACE_UINT64 page_file_avail (void) const;

        // Getter method for kernel_total
        ACE_UINT64 kernel_total (void) const;

        // Getter method for kernel_paged
        ACE_UINT64 kernel_paged (void) const;

        // Getter method for kernel_nonpaged
        ACE_UINT64 kernel_nonpaged (void) const;

        // Getter method for page_size
        ACE_UINT64 page_size (void) const;

        // Getter method for commit_peak
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

#endif  // !defined __MEMORYPROBE_H__

