// $Id$

#include "HeartbeatProbe.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{

  // 
  // HeartbeatProbe::__metadata__
  // 
  const HeartbeatProbe::METADATA_TYPE HeartbeatProbe::__metadata__;

  // 
  // HeartbeatProbe::metadata
  // 
  const HeartbeatProbe::METADATA_TYPE & HeartbeatProbe::metadata (void) const 
  {
    return ::OASIS::HeartbeatProbe::__metadata__;
  }

  // 
  // HeartbeatProbe
  // 
  HeartbeatProbe::HeartbeatProbe (void) 
  {
  }

  // 
  // ~HeartbeatProbe
  // 
  HeartbeatProbe::~HeartbeatProbe (void) 
  {
  }

  // 
  // recall
  // 
  int HeartbeatProbe::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::OASIS::HeartbeatProbe::recall (input);
  }


  // 
  // recall
  // 
  int HeartbeatProbe::recall (ACE_InputCDR & in) 
  {
    if (0 != ::OASIS::Software_Probe::recall (in))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to recall ")
                         ACE_TEXT ("::OASIS::Software_Probe data\n")),
                        -1);


    return 0;
  }

  // 
  // dump
  // 
  void HeartbeatProbe::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe::dump (output);
  }
}

