// $Id$

#include "vector.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{

  // 
  // Int16_Vector_Probe::__metadata__
  // 
  const Int16_Vector_Probe::METADATA_TYPE Int16_Vector_Probe::__metadata__;

  // 
  // Int16_Vector_Probe::metadata
  // 
  const Int16_Vector_Probe::METADATA_TYPE & Int16_Vector_Probe::metadata (void) const 
  {
    return ::OASIS::Int16_Vector_Probe::__metadata__;
  }

  // 
  // Int16_Vector_Probe
  // 
  Int16_Vector_Probe::Int16_Vector_Probe (void) 
  {
  }

  // 
  // ~Int16_Vector_Probe
  // 
  Int16_Vector_Probe::~Int16_Vector_Probe (void) 
  {
  }

  // 
  // recall
  // 
  int Int16_Vector_Probe::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::OASIS::Int16_Vector_Probe::recall (input);
  }


  // 
  // recall
  // 
  int Int16_Vector_Probe::recall (ACE_InputCDR & in) 
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
  void Int16_Vector_Probe::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe::dump (output);
  }

  // 
  // value
  // 
  const std::vector < ACE_INT16 > & Int16_Vector_Probe::value (void) const
  {
    return this->value_;
  }

  // 
  // value
  // 
  std::vector < ACE_INT16 > & Int16_Vector_Probe::value (void)
  {
    return this->value_;
  }
}

