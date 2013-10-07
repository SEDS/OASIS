// $Id$

#include "ProcessorProbeImpl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{
  namespace System
  {
    namespace Processor
    {

      // 
      // ProcessorProbeImpl
      // 
      ProcessorProbeImpl::ProcessorProbeImpl (void) 
      {
         this->uuid_ = this->metadata ().uuid_;
      }

      // 
      // ProcessorProbeImpl::__metadata__
      // 
      const ::OASIS::System::Processor::ProcessorProbe_Metadata ProcessorProbeImpl::__metadata__ =
      ::OASIS::System::Processor::ProcessorProbe_Metadata ();


      // 
      // ProcessorProbeImpl::metadata
      // 
      const ::OASIS::System::Processor::ProcessorProbe_Metadata & ProcessorProbeImpl::metadata (void) const 
      {
        return ::OASIS::System::Processor::ProcessorProbeImpl::__metadata__;
      }

      // 
      // ~ProcessorProbeImpl
      // 
      ProcessorProbeImpl::~ProcessorProbeImpl (void) 
      {
      }

      // 
      // package_data
      // 
      int ProcessorProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
      {
        if (0 != ::OASIS::Software_Probe_Impl::package_data (p))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                            -1);
        if (!(p.data_stream () << this->idle_time_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package idle_time\n")),
                            -1);

        if (!(p.data_stream () << this->system_time_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package system_time\n")),
                            -1);

        if (!(p.data_stream () << this->user_time_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package user_time\n")),
                            -1);

        return p.data_stream ().good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void ProcessorProbeImpl::dump (std::ostream & output) 
      {
        ::OASIS::Software_Probe_Impl::dump (output);
        output << "  idle_time: " << this->idle_time () << std::endl;
        output << "  system_time: " << this->system_time () << std::endl;
        output << "  user_time: " << this->user_time () << std::endl;
      }

      // 
      // idle_time
      // 
      void ProcessorProbeImpl::idle_time (ACE_UINT64 idle_time)
      {
        this->idle_time_ = idle_time;
      }

      // 
      // idle_time
      // 
      ACE_UINT64 ProcessorProbeImpl::idle_time (void) const
      {
        return this->idle_time_;
      }

      // 
      // system_time
      // 
      void ProcessorProbeImpl::system_time (ACE_UINT64 system_time)
      {
        this->system_time_ = system_time;
      }

      // 
      // system_time
      // 
      ACE_UINT64 ProcessorProbeImpl::system_time (void) const
      {
        return this->system_time_;
      }

      // 
      // user_time
      // 
      void ProcessorProbeImpl::user_time (ACE_UINT64 user_time)
      {
        this->user_time_ = user_time;
      }

      // 
      // user_time
      // 
      ACE_UINT64 ProcessorProbeImpl::user_time (void) const
      {
        return this->user_time_;
      }


      // 
      // LinuxProcessorProbeImpl
      // 
      LinuxProcessorProbeImpl::LinuxProcessorProbeImpl (void) 
      {
         this->uuid_ = this->metadata ().uuid_;
      }

      // 
      // LinuxProcessorProbeImpl::__metadata__
      // 
      const ::OASIS::System::Processor::LinuxProcessorProbe_Metadata LinuxProcessorProbeImpl::__metadata__ =
      ::OASIS::System::Processor::LinuxProcessorProbe_Metadata ();


      // 
      // LinuxProcessorProbeImpl::metadata
      // 
      const ::OASIS::System::Processor::LinuxProcessorProbe_Metadata & LinuxProcessorProbeImpl::metadata (void) const 
      {
        return ::OASIS::System::Processor::LinuxProcessorProbeImpl::__metadata__;
      }

      // 
      // ~LinuxProcessorProbeImpl
      // 
      LinuxProcessorProbeImpl::~LinuxProcessorProbeImpl (void) 
      {
      }

      // 
      // package_data
      // 
      int LinuxProcessorProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
      {
        if (0 != ::OASIS::System::Processor::ProcessorProbeImpl::package_data (p))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                            -1);
        if (!(p.data_stream () << this->nice_time_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package nice_time\n")),
                            -1);

        if (!(p.data_stream () << this->iowait_time_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package iowait_time\n")),
                            -1);

        if (!(p.data_stream () << this->irq_time_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package irq_time\n")),
                            -1);

        if (!(p.data_stream () << this->soft_irq_time_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package soft_irq_time\n")),
                            -1);

        return p.data_stream ().good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void LinuxProcessorProbeImpl::dump (std::ostream & output) 
      {
        ::OASIS::System::Processor::ProcessorProbeImpl::dump (output);
        output << "  nice_time: " << this->nice_time () << std::endl;
        output << "  iowait_time: " << this->iowait_time () << std::endl;
        output << "  irq_time: " << this->irq_time () << std::endl;
        output << "  soft_irq_time: " << this->soft_irq_time () << std::endl;
      }

      // 
      // nice_time
      // 
      void LinuxProcessorProbeImpl::nice_time (ACE_UINT64 nice_time)
      {
        this->nice_time_ = nice_time;
      }

      // 
      // nice_time
      // 
      ACE_UINT64 LinuxProcessorProbeImpl::nice_time (void) const
      {
        return this->nice_time_;
      }

      // 
      // iowait_time
      // 
      void LinuxProcessorProbeImpl::iowait_time (ACE_UINT64 iowait_time)
      {
        this->iowait_time_ = iowait_time;
      }

      // 
      // iowait_time
      // 
      ACE_UINT64 LinuxProcessorProbeImpl::iowait_time (void) const
      {
        return this->iowait_time_;
      }

      // 
      // irq_time
      // 
      void LinuxProcessorProbeImpl::irq_time (ACE_UINT64 irq_time)
      {
        this->irq_time_ = irq_time;
      }

      // 
      // irq_time
      // 
      ACE_UINT64 LinuxProcessorProbeImpl::irq_time (void) const
      {
        return this->irq_time_;
      }

      // 
      // soft_irq_time
      // 
      void LinuxProcessorProbeImpl::soft_irq_time (ACE_UINT64 soft_irq_time)
      {
        this->soft_irq_time_ = soft_irq_time;
      }

      // 
      // soft_irq_time
      // 
      ACE_UINT64 LinuxProcessorProbeImpl::soft_irq_time (void) const
      {
        return this->soft_irq_time_;
      }


      // 
      // WindowsProcessorProbeImpl
      // 
      WindowsProcessorProbeImpl::WindowsProcessorProbeImpl (void) 
      {
         this->uuid_ = this->metadata ().uuid_;
      }

      // 
      // WindowsProcessorProbeImpl::__metadata__
      // 
      const ::OASIS::System::Processor::WindowsProcessorProbe_Metadata WindowsProcessorProbeImpl::__metadata__ =
      ::OASIS::System::Processor::WindowsProcessorProbe_Metadata ();


      // 
      // WindowsProcessorProbeImpl::metadata
      // 
      const ::OASIS::System::Processor::WindowsProcessorProbe_Metadata & WindowsProcessorProbeImpl::metadata (void) const 
      {
        return ::OASIS::System::Processor::WindowsProcessorProbeImpl::__metadata__;
      }

      // 
      // ~WindowsProcessorProbeImpl
      // 
      WindowsProcessorProbeImpl::~WindowsProcessorProbeImpl (void) 
      {
      }

      // 
      // package_data
      // 
      int WindowsProcessorProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
      {
        if (0 != ::OASIS::System::Processor::ProcessorProbeImpl::package_data (p))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                            -1);
        return p.data_stream ().good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void WindowsProcessorProbeImpl::dump (std::ostream & output) 
      {
        ::OASIS::System::Processor::ProcessorProbeImpl::dump (output);
      }
    }
  }
}

