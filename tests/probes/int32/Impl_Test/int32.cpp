// $Id$

#include "int32.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{

  // 
  // Int32_SoftwareProbe::__metadata__
  // 
  const Int32_SoftwareProbe::METADATA_TYPE Int32_SoftwareProbe::__metadata__;

  // 
  // Int32_SoftwareProbe::metadata
  // 
  const Int32_SoftwareProbe::METADATA_TYPE & Int32_SoftwareProbe::metadata (void) const 
  {
    return ::OASIS::Int32_SoftwareProbe::__metadata__;
  }

  // 
  // Int32_SoftwareProbe
  // 
  Int32_SoftwareProbe::Int32_SoftwareProbe (void) 
  {
  }

  // 
  // ~Int32_SoftwareProbe
  // 
  Int32_SoftwareProbe::~Int32_SoftwareProbe (void) 
  {
  }

  // 
  // recall
  // 
  int Int32_SoftwareProbe::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::OASIS::Int32_SoftwareProbe::recall (input);
  }


  // 
  // recall
  // 
  int Int32_SoftwareProbe::recall (ACE_InputCDR & in) 
  {
    if (0 != ::OASIS::Software_Probe::recall (in))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to recall ")
                         ACE_TEXT ("::OASIS::Software_Probe data\n")),
                        -1);

    if (!(in >> this->value_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage value\n")),
                        -1);

    return in.good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void Int32_SoftwareProbe::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe::dump (output);
    output << "  value: " << this->value_ << std::endl;
  }

  // 
  // value
  // 
  ACE_INT32 Int32_SoftwareProbe::value (void) const
  {
    return this->value_;
  }
}

