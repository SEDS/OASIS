// -*- C++ -*-

//============================================================================
/**
 * @file        ProcessorProbe_Metadata.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _PROCESSORPROBE_METADATA_H_
#define _PROCESSORPROBE_METADATA_H_

#include "oasis/probes/Software_Probe_Metadata.h"

#include "ProcessorProbe_stub_export.h"

namespace OASIS
{
  namespace System
  {
    namespace Processor
    {
      /**
       * @class ProcessorProbe_Metadata
       */
      class OASIS_PROCESSORPROBE_STUB_Export ProcessorProbe_Metadata :
        public ::OASIS::Software_Probe_Metadata 
      {
        public:
        /// Default constructor
        ProcessorProbe_Metadata (void);

        /// Destructor
        virtual ~ProcessorProbe_Metadata (void);

        protected:
        /// Initalizing constructor
        ProcessorProbe_Metadata (const char * uuid,
                                 const char * type_info,
                                 ACE_UINT8 version_major,
                                 ACE_UINT8 version_minor,
                                 const char * schema);

        private:
        /// The metadata's schema
        static const char * __schema__;
      };

      /**
       * @class LinuxProcessorProbe_Metadata
       */
      class OASIS_PROCESSORPROBE_STUB_Export LinuxProcessorProbe_Metadata :
        public ::OASIS::System::Processor::ProcessorProbe_Metadata 
      {
        public:
        /// Default constructor
        LinuxProcessorProbe_Metadata (void);

        /// Destructor
        virtual ~LinuxProcessorProbe_Metadata (void);

        protected:
        /// Initalizing constructor
        LinuxProcessorProbe_Metadata (const char * uuid,
                                      const char * type_info,
                                      ACE_UINT8 version_major,
                                      ACE_UINT8 version_minor,
                                      const char * schema);

        private:
        /// The metadata's schema
        static const char * __schema__;
      };

      /**
       * @class WindowsProcessorProbe_Metadata
       */
      class OASIS_PROCESSORPROBE_STUB_Export WindowsProcessorProbe_Metadata :
        public ::OASIS::System::Processor::ProcessorProbe_Metadata 
      {
        public:
        /// Default constructor
        WindowsProcessorProbe_Metadata (void);

        /// Destructor
        virtual ~WindowsProcessorProbe_Metadata (void);

        protected:
        /// Initalizing constructor
        WindowsProcessorProbe_Metadata (const char * uuid,
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

#endif  // !defined __PROCESSORPROBE_METADATA_H__

