// $Id: ACE_Logging_Software_Probe.cpp 1892 2011-09-03 07:45:49Z hillj $

#include "ACE_Logging_Software_Probe.h"

#if !defined (__OASIS_INLINE__)
#include "ACE_Logging_Software_Probe.inl"
#endif

#include "ace/Log_Record.h"

namespace OASIS
{

//
// log
//
void ACE_Logging_Software_Probe::log (ACE_Log_Record & log_record)
{
  // Right now this assumes that the msg_data () is NULL terminated. If
  // this is not the case, then we need to NULL terminate the buffer
  // before calling the log () method.
  this->severity_ = log_record.priority ();
  this->thread_id_ = log_record.pid ();
  this->message_ = log_record.msg_data ();

  // Send the data to the EINode.
  this->flush ();
}

}
