// -*- C++ -*-

//============================================================================
/**
 * @file        ProcessorProbe.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _PROCESSORPROBE_H_
#define _PROCESSORPROBE_H_

#include "oasis/probes/Data_Types.h"
#include "oasis/probes/Software_Probe.h"
#include "ProcessorProbe_Metadata.h"
#include <iostream>

#include "ProcessorProbe_stub_export.h"

namespace OASIS
{
  namespace System
  {
    namespace Processor
    {
      /**
       * @class ProcessorProbe
       */
      class OASIS_PROCESSORPROBE_STUB_Export ProcessorProbe :
        public virtual ::OASIS::Software_Probe 
      {
        public:
        // Type definition of the software probe's metadata.
        typedef ::OASIS::System::Processor::ProcessorProbe_Metadata METADATA_TYPE;

        /// The metadata for the software probe.
        static const METADATA_TYPE __metadata__;

        /// Default constructor
        ProcessorProbe (void);

        /// Destructor
        virtual ~ProcessorProbe (void);

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
        // Getter method for idle_time
        ACE_UINT64 idle_time (void) const;

        // Getter method for system_time
        ACE_UINT64 system_time (void) const;

        // Getter method for user_time
        ACE_UINT64 user_time (void) const;

        protected:
        ACE_UINT64 idle_time_;

        ACE_UINT64 system_time_;

        ACE_UINT64 user_time_;
      };

      /**
       * @class LinuxProcessorProbe
       */
      class OASIS_PROCESSORPROBE_STUB_Export LinuxProcessorProbe :
        public ::OASIS::System::Processor::ProcessorProbe 
      {
        public:
        // Type definition of the software probe's metadata.
        typedef ::OASIS::System::Processor::LinuxProcessorProbe_Metadata METADATA_TYPE;

        /// The metadata for the software probe.
        static const METADATA_TYPE __metadata__;

        /// Default constructor
        LinuxProcessorProbe (void);

        /// Destructor
        virtual ~LinuxProcessorProbe (void);

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
        // Getter method for nice_time
        ACE_UINT64 nice_time (void) const;

        // Getter method for iowait_time
        ACE_UINT64 iowait_time (void) const;

        // Getter method for irq_time
        ACE_UINT64 irq_time (void) const;

        // Getter method for soft_irq_time
        ACE_UINT64 soft_irq_time (void) const;

        protected:
        ACE_UINT64 nice_time_;

        ACE_UINT64 iowait_time_;

        ACE_UINT64 irq_time_;

        ACE_UINT64 soft_irq_time_;
      };

      /**
       * @class WindowsProcessorProbe
       */
      class OASIS_PROCESSORPROBE_STUB_Export WindowsProcessorProbe :
        public ::OASIS::System::Processor::ProcessorProbe 
      {
        public:
        // Type definition of the software probe's metadata.
        typedef ::OASIS::System::Processor::WindowsProcessorProbe_Metadata METADATA_TYPE;

        /// The metadata for the software probe.
        static const METADATA_TYPE __metadata__;

        /// Default constructor
        WindowsProcessorProbe (void);

        /// Destructor
        virtual ~WindowsProcessorProbe (void);

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
      };
    }
  }
}

#endif  // !defined __PROCESSORPROBE_H__

