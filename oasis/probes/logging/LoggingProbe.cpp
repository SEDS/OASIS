// $Id$

#include "LoggingProbe.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{

  // 
  // LoggingProbe::__metadata__
  // 
  const LoggingProbe::METADATA_TYPE LoggingProbe::__metadata__;

  // 
  // LoggingProbe::metadata
  // 
  const LoggingProbe::METADATA_TYPE & LoggingProbe::metadata (void) const 
  {
    return ::OASIS::LoggingProbe::__metadata__;
  }

  // 
  // LoggingProbe
  // 
  LoggingProbe::LoggingProbe (void) 
  {
  }

  // 
  // ~LoggingProbe
  // 
  LoggingProbe::~LoggingProbe (void) 
  {
  }

  // 
  // recall
  // 
  int LoggingProbe::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::OASIS::LoggingProbe::recall (input);
  }


  // 
  // recall
  // 
  int LoggingProbe::recall (ACE_InputCDR & in) 
  {
    if (0 != ::OASIS::Software_Probe::recall (in))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to recall ")
                         ACE_TEXT ("::OASIS::Software_Probe data\n")),
                        -1);

    if (!(in >> this->severity_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage severity\n")),
                        -1);

    if (!(in >> this->thread_id_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage thread_id\n")),
                        -1);

    if (!(in >> this->message_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage message\n")),
                        -1);

    return in.good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void LoggingProbe::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe::dump (output);
    output << "  severity: " << this->severity_ << std::endl;
    output << "  thread_id: " << this->thread_id_ << std::endl;
    output << "  message: " << this->message_ << std::endl;
  }

  // 
  // severity
  // 
  ACE_INT32 LoggingProbe::severity (void) const
  {
    return this->severity_;
  }

  // 
  // thread_id
  // 
  ACE_INT32 LoggingProbe::thread_id (void) const
  {
    return this->thread_id_;
  }

  // 
  // message
  // 
  const ACE_CString & LoggingProbe::message (void) const
  {
    return this->message_;
  }
}

