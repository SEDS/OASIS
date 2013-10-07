// $Id$

#include "ProcessorProbe.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{
  namespace System
  {
    namespace Processor
    {

      // 
      // ProcessorProbe::__metadata__
      // 
      const ProcessorProbe::METADATA_TYPE ProcessorProbe::__metadata__;

      // 
      // ProcessorProbe::metadata
      // 
      const ProcessorProbe::METADATA_TYPE & ProcessorProbe::metadata (void) const 
      {
        return ::OASIS::System::Processor::ProcessorProbe::__metadata__;
      }

      // 
      // ProcessorProbe
      // 
      ProcessorProbe::ProcessorProbe (void) 
      {
      }

      // 
      // ~ProcessorProbe
      // 
      ProcessorProbe::~ProcessorProbe (void) 
      {
      }

      // 
      // recall
      // 
      int ProcessorProbe::
      recall (const char * data, size_t length, int byte_order) 
      {
        ::OASIS::Software_Probe_Data_Preparer prep (data, length);
        ACE_InputCDR input (prep.message_block (), byte_order);
        return ::OASIS::System::Processor::ProcessorProbe::recall (input);
      }


      // 
      // recall
      // 
      int ProcessorProbe::recall (ACE_InputCDR & in) 
      {
        if (0 != ::OASIS::Software_Probe::recall (in))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to recall ")
                             ACE_TEXT ("::OASIS::Software_Probe data\n")),
                            -1);

        if (!(in >> this->idle_time_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage idle_time\n")),
                            -1);

        if (!(in >> this->system_time_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage system_time\n")),
                            -1);

        if (!(in >> this->user_time_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage user_time\n")),
                            -1);

        return in.good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void ProcessorProbe::dump (std::ostream & output) 
      {
        ::OASIS::Software_Probe::dump (output);
        output << "  idle_time: " << this->idle_time_ << std::endl;
        output << "  system_time: " << this->system_time_ << std::endl;
        output << "  user_time: " << this->user_time_ << std::endl;
      }

      // 
      // idle_time
      // 
      ACE_UINT64 ProcessorProbe::idle_time (void) const
      {
        return this->idle_time_;
      }

      // 
      // system_time
      // 
      ACE_UINT64 ProcessorProbe::system_time (void) const
      {
        return this->system_time_;
      }

      // 
      // user_time
      // 
      ACE_UINT64 ProcessorProbe::user_time (void) const
      {
        return this->user_time_;
      }


      // 
      // LinuxProcessorProbe::__metadata__
      // 
      const LinuxProcessorProbe::METADATA_TYPE LinuxProcessorProbe::__metadata__;

      // 
      // LinuxProcessorProbe::metadata
      // 
      const LinuxProcessorProbe::METADATA_TYPE & LinuxProcessorProbe::metadata (void) const 
      {
        return ::OASIS::System::Processor::LinuxProcessorProbe::__metadata__;
      }

      // 
      // LinuxProcessorProbe
      // 
      LinuxProcessorProbe::LinuxProcessorProbe (void) 
      {
      }

      // 
      // ~LinuxProcessorProbe
      // 
      LinuxProcessorProbe::~LinuxProcessorProbe (void) 
      {
      }

      // 
      // recall
      // 
      int LinuxProcessorProbe::
      recall (const char * data, size_t length, int byte_order) 
      {
        ::OASIS::Software_Probe_Data_Preparer prep (data, length);
        ACE_InputCDR input (prep.message_block (), byte_order);
        return ::OASIS::System::Processor::LinuxProcessorProbe::recall (input);
      }


      // 
      // recall
      // 
      int LinuxProcessorProbe::recall (ACE_InputCDR & in) 
      {
        if (0 != ::OASIS::System::Processor::ProcessorProbe::recall (in))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to recall ")
                             ACE_TEXT ("::OASIS::System::Processor::ProcessorProbe data\n")),
                            -1);

        if (!(in >> this->nice_time_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage nice_time\n")),
                            -1);

        if (!(in >> this->iowait_time_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage iowait_time\n")),
                            -1);

        if (!(in >> this->irq_time_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage irq_time\n")),
                            -1);

        if (!(in >> this->soft_irq_time_))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to unpackage soft_irq_time\n")),
                            -1);

        return in.good_bit () ? 0 : -1;
      }

      // 
      // dump
      // 
      void LinuxProcessorProbe::dump (std::ostream & output) 
      {
        ::OASIS::System::Processor::ProcessorProbe::dump (output);
        output << "  nice_time: " << this->nice_time_ << std::endl;
        output << "  iowait_time: " << this->iowait_time_ << std::endl;
        output << "  irq_time: " << this->irq_time_ << std::endl;
        output << "  soft_irq_time: " << this->soft_irq_time_ << std::endl;
      }

      // 
      // nice_time
      // 
      ACE_UINT64 LinuxProcessorProbe::nice_time (void) const
      {
        return this->nice_time_;
      }

      // 
      // iowait_time
      // 
      ACE_UINT64 LinuxProcessorProbe::iowait_time (void) const
      {
        return this->iowait_time_;
      }

      // 
      // irq_time
      // 
      ACE_UINT64 LinuxProcessorProbe::irq_time (void) const
      {
        return this->irq_time_;
      }

      // 
      // soft_irq_time
      // 
      ACE_UINT64 LinuxProcessorProbe::soft_irq_time (void) const
      {
        return this->soft_irq_time_;
      }


      // 
      // WindowsProcessorProbe::__metadata__
      // 
      const WindowsProcessorProbe::METADATA_TYPE WindowsProcessorProbe::__metadata__;

      // 
      // WindowsProcessorProbe::metadata
      // 
      const WindowsProcessorProbe::METADATA_TYPE & WindowsProcessorProbe::metadata (void) const 
      {
        return ::OASIS::System::Processor::WindowsProcessorProbe::__metadata__;
      }

      // 
      // WindowsProcessorProbe
      // 
      WindowsProcessorProbe::WindowsProcessorProbe (void) 
      {
      }

      // 
      // ~WindowsProcessorProbe
      // 
      WindowsProcessorProbe::~WindowsProcessorProbe (void) 
      {
      }

      // 
      // recall
      // 
      int WindowsProcessorProbe::
      recall (const char * data, size_t length, int byte_order) 
      {
        ::OASIS::Software_Probe_Data_Preparer prep (data, length);
        ACE_InputCDR input (prep.message_block (), byte_order);
        return ::OASIS::System::Processor::WindowsProcessorProbe::recall (input);
      }


      // 
      // recall
      // 
      int WindowsProcessorProbe::recall (ACE_InputCDR & in) 
      {
        if (0 != ::OASIS::System::Processor::ProcessorProbe::recall (in))
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("%T (%t) - %M - failed to recall ")
                             ACE_TEXT ("::OASIS::System::Processor::ProcessorProbe data\n")),
                            -1);


        return 0;
      }

      // 
      // dump
      // 
      void WindowsProcessorProbe::dump (std::ostream & output) 
      {
        ::OASIS::System::Processor::ProcessorProbe::dump (output);
      }
    }
  }
}

