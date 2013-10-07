// -*- C++ -*-

//============================================================================
/**
 * @file        ProcessorProbeImpl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _PROCESSORPROBEIMPL_H_
#define _PROCESSORPROBEIMPL_H_

#include "oasis/probes/Data_Types.h"
#include "ProcessorProbe_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

#include "ProcessorProbe_stub_export.h"

namespace OASIS
{
  namespace System
  {
    namespace Processor
    {
      /**
       * @class ProcessorProbeImpl
       */
      class OASIS_PROCESSORPROBE_STUB_Export ProcessorProbeImpl :
        public virtual ::OASIS::Software_Probe_Impl
      {
        public:
        /// The metadata for the software probe.
        static const ::OASIS::System::Processor::ProcessorProbe_Metadata __metadata__;

        /// Default constructor
        ProcessorProbeImpl (void);

        /// Destructor
        virtual ~ProcessorProbeImpl (void) = 0;

        /// Getter for the probe's metadata
        virtual const ::OASIS::System::Processor::ProcessorProbe_Metadata & metadata (void) const;

        /// Package the software probe's data.
        protected:
        virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


        public:
        /// Impl_Dump the software probe's data.
        virtual void dump (std::ostream & output);


        public:
        // Setter and getter methods for idle_time
        void idle_time (ACE_UINT64 idle_time);
        ACE_UINT64 idle_time (void) const;

        // Setter and getter methods for system_time
        void system_time (ACE_UINT64 system_time);
        ACE_UINT64 system_time (void) const;

        // Setter and getter methods for user_time
        void user_time (ACE_UINT64 user_time);
        ACE_UINT64 user_time (void) const;

        protected:
        ACE_UINT64 idle_time_;

        ACE_UINT64 system_time_;

        ACE_UINT64 user_time_;
      };

      /**
       * @class LinuxProcessorProbeImpl
       */
      class OASIS_PROCESSORPROBE_STUB_Export LinuxProcessorProbeImpl :
        public ::OASIS::System::Processor::ProcessorProbeImpl
      {
        public:
        /// The metadata for the software probe.
        static const ::OASIS::System::Processor::LinuxProcessorProbe_Metadata __metadata__;

        /// Default constructor
        LinuxProcessorProbeImpl (void);

        /// Destructor
        virtual ~LinuxProcessorProbeImpl (void);

        /// Getter for the probe's metadata
        virtual const ::OASIS::System::Processor::LinuxProcessorProbe_Metadata & metadata (void) const;

        /// Package the software probe's data.
        protected:
        virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


        public:
        /// Impl_Dump the software probe's data.
        virtual void dump (std::ostream & output);


        public:
        // Setter and getter methods for nice_time
        void nice_time (ACE_UINT64 nice_time);
        ACE_UINT64 nice_time (void) const;

        // Setter and getter methods for iowait_time
        void iowait_time (ACE_UINT64 iowait_time);
        ACE_UINT64 iowait_time (void) const;

        // Setter and getter methods for irq_time
        void irq_time (ACE_UINT64 irq_time);
        ACE_UINT64 irq_time (void) const;

        // Setter and getter methods for soft_irq_time
        void soft_irq_time (ACE_UINT64 soft_irq_time);
        ACE_UINT64 soft_irq_time (void) const;

        protected:
        ACE_UINT64 nice_time_;

        ACE_UINT64 iowait_time_;

        ACE_UINT64 irq_time_;

        ACE_UINT64 soft_irq_time_;
      };

      /**
       * @class WindowsProcessorProbeImpl
       */
      class OASIS_PROCESSORPROBE_STUB_Export WindowsProcessorProbeImpl :
        public ::OASIS::System::Processor::ProcessorProbeImpl
      {
        public:
        /// The metadata for the software probe.
        static const ::OASIS::System::Processor::WindowsProcessorProbe_Metadata __metadata__;

        /// Default constructor
        WindowsProcessorProbeImpl (void);

        /// Destructor
        virtual ~WindowsProcessorProbeImpl (void);

        /// Getter for the probe's metadata
        virtual const ::OASIS::System::Processor::WindowsProcessorProbe_Metadata & metadata (void) const;

        /// Package the software probe's data.
        protected:
        virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


        public:
        /// Impl_Dump the software probe's data.
        virtual void dump (std::ostream & output);
      };
    }
  }
}

#endif  // !defined __PROCESSORPROBEIMPL_H__

