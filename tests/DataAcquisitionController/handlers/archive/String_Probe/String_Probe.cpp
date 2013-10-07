// $Id$

#include "String_Probe.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/probes/Data_Streams_T.h"

namespace Test
{

  // 
  // String_Probe::__metadata__
  // 
  const String_Probe::METADATA_TYPE String_Probe::__metadata__;

  // 
  // String_Probe::metadata
  // 
  const String_Probe::METADATA_TYPE & String_Probe::metadata (void) const 
  {
    return ::Test::String_Probe::__metadata__;
  }

  // 
  // String_Probe
  // 
  String_Probe::String_Probe (void) 
  {
  }

  // 
  // ~String_Probe
  // 
  String_Probe::~String_Probe (void) 
  {
  }

  // 
  // recall
  // 
  int String_Probe::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::Test::String_Probe::recall (input);
  }


  // 
  // recall
  // 
  int String_Probe::recall (ACE_InputCDR & in) 
  {
    if (0 != ::OASIS::Software_Probe::recall (in))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to recall ")
                         ACE_TEXT ("::OASIS::Software_Probe data\n")),
                        -1);

    if (!(in >> this->str_value_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage str_value\n")),
                        -1);

    return in.good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void String_Probe::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe::dump (output);
    output << "  str_value: " << this->str_value_ << std::endl;
  }

  // 
  // str_value
  // 
  const ACE_CString & String_Probe::str_value (void) const
  {
    return this->str_value_;
  }
}

