// $Id$

#include "LoggingProbeImpl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{

  // 
  // LoggingProbeImpl
  // 
  LoggingProbeImpl::LoggingProbeImpl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // LoggingProbeImpl::__metadata__
  // 
  const ::OASIS::LoggingProbe_Metadata LoggingProbeImpl::__metadata__ =
  ::OASIS::LoggingProbe_Metadata ();


  // 
  // LoggingProbeImpl::metadata
  // 
  const ::OASIS::LoggingProbe_Metadata & LoggingProbeImpl::metadata (void) const 
  {
    return ::OASIS::LoggingProbeImpl::__metadata__;
  }

  // 
  // ~LoggingProbeImpl
  // 
  LoggingProbeImpl::~LoggingProbeImpl (void) 
  {
  }

  // 
  // package_data
  // 
  int LoggingProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
  {
    if (0 != ::OASIS::Software_Probe_Impl::package_data (p))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                        -1);
    if (!(p.data_stream () << this->severity_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package severity\n")),
                        -1);

    if (!(p.data_stream () << this->thread_id_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package thread_id\n")),
                        -1);

    if (!(p.data_stream () << this->message_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package message\n")),
                        -1);

    return p.data_stream ().good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void LoggingProbeImpl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
    output << "  severity: " << this->severity () << std::endl;
    output << "  thread_id: " << this->thread_id () << std::endl;
    output << "  message: " << this->message () << std::endl;
  }

  // 
  // severity
  // 
  void LoggingProbeImpl::severity (ACE_INT32 severity)
  {
    this->severity_ = severity;
  }

  // 
  // severity
  // 
  ACE_INT32 LoggingProbeImpl::severity (void) const
  {
    return this->severity_;
  }

  // 
  // thread_id
  // 
  void LoggingProbeImpl::thread_id (ACE_INT32 thread_id)
  {
    this->thread_id_ = thread_id;
  }

  // 
  // thread_id
  // 
  ACE_INT32 LoggingProbeImpl::thread_id (void) const
  {
    return this->thread_id_;
  }

  // 
  // message
  // 
  void LoggingProbeImpl::message (const ACE_CString & message)
  {
    this->message_ = message;
  }

  // 
  // message
  // 
  const ACE_CString & LoggingProbeImpl::message (void) const
  {
    return this->message_;
  }
}

