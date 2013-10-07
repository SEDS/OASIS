// $Id$

#include "nodata.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/probes/Data_Streams_T.h"

namespace Test
{

  // 
  // NoDataProbe::__metadata__
  // 
  const NoDataProbe::METADATA_TYPE NoDataProbe::__metadata__;

  // 
  // NoDataProbe::metadata
  // 
  const NoDataProbe::METADATA_TYPE & NoDataProbe::metadata (void) const 
  {
    return ::Test::NoDataProbe::__metadata__;
  }

  // 
  // NoDataProbe
  // 
  NoDataProbe::NoDataProbe (void) 
  {
  }

  // 
  // ~NoDataProbe
  // 
  NoDataProbe::~NoDataProbe (void) 
  {
  }

  // 
  // recall
  // 
  int NoDataProbe::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::Test::NoDataProbe::recall (input);
  }


  // 
  // recall
  // 
  int NoDataProbe::recall (ACE_InputCDR & in) 
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
  void NoDataProbe::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe::dump (output);
  }
}

