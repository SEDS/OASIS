// -*- C++ -*-

//============================================================================
/**
 * @file        MemoryProbe_Metadata.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _MEMORYPROBE_METADATA_H_
#define _MEMORYPROBE_METADATA_H_

#include "oasis/probes/Software_Probe_Metadata.h"

#include "MemoryProbe_stub_export.h"

namespace OASIS
{
  namespace System
  {
    namespace Memory
    {
      /**
       * @class MemoryProbe_Metadata
       */
      class OASIS_MEMORYPROBE_STUB_Export MemoryProbe_Metadata :
        public ::OASIS::Software_Probe_Metadata 
      {
        public:
        /// Default constructor
        MemoryProbe_Metadata (void);

        /// Destructor
        virtual ~MemoryProbe_Metadata (void);

        protected:
        /// Initalizing constructor
        MemoryProbe_Metadata (const char * uuid,
                              const char * type_info,
                              ACE_UINT8 version_major,
                              ACE_UINT8 version_minor,
                              const char * schema);

        private:
        /// The metadata's schema
        static const char * __schema__;
      };

      /**
       * @class LinuxMemoryProbe_Metadata
       */
      class OASIS_MEMORYPROBE_STUB_Export LinuxMemoryProbe_Metadata :
        public ::OASIS::System::Memory::MemoryProbe_Metadata 
      {
        public:
        /// Default constructor
        LinuxMemoryProbe_Metadata (void);

        /// Destructor
        virtual ~LinuxMemoryProbe_Metadata (void);

        protected:
        /// Initalizing constructor
        LinuxMemoryProbe_Metadata (const char * uuid,
                                   const char * type_info,
                                   ACE_UINT8 version_major,
                                   ACE_UINT8 version_minor,
                                   const char * schema);

        private:
        /// The metadata's schema
        static const char * __schema__;
      };

      /**
       * @class WindowsMemoryProbe_Metadata
       */
      class OASIS_MEMORYPROBE_STUB_Export WindowsMemoryProbe_Metadata :
        public ::OASIS::System::Memory::MemoryProbe_Metadata 
      {
        public:
        /// Default constructor
        WindowsMemoryProbe_Metadata (void);

        /// Destructor
        virtual ~WindowsMemoryProbe_Metadata (void);

        protected:
        /// Initalizing constructor
        WindowsMemoryProbe_Metadata (const char * uuid,
                                     const char * type_info,
                                     ACE_UINT8 version_major,
                                     ACE_UINT8 version_minor,
                                     const char * schema);

        private:
        /// The metadata's schema
        static const char * __schema__;
      };
    }
  }
}

#endif  // !defined __MEMORYPROBE_METADATA_H__

