// $Id$

#include "String_Probe.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{

  // 
  // String_SoftwareProbe::__metadata__
  // 
  const String_SoftwareProbe::METADATA_TYPE String_SoftwareProbe::__metadata__;

  // 
  // String_SoftwareProbe::metadata
  // 
  const String_SoftwareProbe::METADATA_TYPE & String_SoftwareProbe::metadata (void) const 
  {
    return ::OASIS::String_SoftwareProbe::__metadata__;
  }

  // 
  // String_SoftwareProbe
  // 
  String_SoftwareProbe::String_SoftwareProbe (void) 
  {
  }

  // 
  // ~String_SoftwareProbe
  // 
  String_SoftwareProbe::~String_SoftwareProbe (void) 
  {
  }

  // 
  // recall
  // 
  int String_SoftwareProbe::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::OASIS::String_SoftwareProbe::recall (input);
  }


  // 
  // recall
  // 
  int String_SoftwareProbe::recall (ACE_InputCDR & in) 
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
  void String_SoftwareProbe::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe::dump (output);
    output << "  value: " << this->value_ << std::endl;
  }

  // 
  // value
  // 
  const ACE_CString & String_SoftwareProbe::value (void) const
  {
    return this->value_;
  }
}

