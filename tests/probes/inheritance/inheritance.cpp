// $Id$

#include "inheritance.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/probes/Data_Streams_T.h"


// 
// A::__metadata__
// 
const A::METADATA_TYPE A::__metadata__;

// 
// A::metadata
// 
const A::METADATA_TYPE & A::metadata (void) const 
{
  return ::A::__metadata__;
}

// 
// A
// 
A::A (void) 
{
}

// 
// ~A
// 
A::~A (void) 
{
}

// 
// recall
// 
int A::
recall (const char * data, size_t length, int byte_order) 
{
  ::OASIS::Software_Probe_Data_Preparer prep (data, length);
  ACE_InputCDR input (prep.message_block (), byte_order);
  return ::A::recall (input);
}


// 
// recall
// 
int A::recall (ACE_InputCDR & in) 
{
  if (0 != ::OASIS::Software_Probe::recall (in))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to recall ")
                       ACE_TEXT ("::OASIS::Software_Probe data\n")),
                      -1);

  if (!(in >> this->a_value_))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to unpackage a_value\n")),
                      -1);

  return in.good_bit () ? 0 : -1;
}

// 
// dump
// 
void A::dump (std::ostream & output) 
{
  ::OASIS::Software_Probe::dump (output);
  output << "  a_value: " << this->a_value_ << std::endl;
}

// 
// a_value
// 
ACE_INT32 A::a_value (void) const
{
  return this->a_value_;
}

namespace Test
{

  // 
  // B::__metadata__
  // 
  const B::METADATA_TYPE B::__metadata__;

  // 
  // B::metadata
  // 
  const B::METADATA_TYPE & B::metadata (void) const 
  {
    return ::Test::B::__metadata__;
  }

  // 
  // B
  // 
  B::B (void) 
  {
  }

  // 
  // ~B
  // 
  B::~B (void) 
  {
  }

  // 
  // recall
  // 
  int B::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::Test::B::recall (input);
  }


  // 
  // recall
  // 
  int B::recall (ACE_InputCDR & in) 
  {
    if (0 != ::A::recall (in))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to recall ")
                         ACE_TEXT ("::A data\n")),
                        -1);

    if (!(in >> this->b_value_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage b_value\n")),
                        -1);

    return in.good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void B::dump (std::ostream & output) 
  {
    ::A::dump (output);
    output << "  b_value: " << this->b_value_ << std::endl;
  }

  // 
  // b_value
  // 
  ACE_INT32 B::b_value (void) const
  {
    return this->b_value_;
  }


  // 
  // C::__metadata__
  // 
  const C::METADATA_TYPE C::__metadata__;

  // 
  // C::metadata
  // 
  const C::METADATA_TYPE & C::metadata (void) const 
  {
    return ::Test::C::__metadata__;
  }

  // 
  // C
  // 
  C::C (void) 
  {
  }

  // 
  // ~C
  // 
  C::~C (void) 
  {
  }

  // 
  // recall
  // 
  int C::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::Test::C::recall (input);
  }


  // 
  // recall
  // 
  int C::recall (ACE_InputCDR & in) 
  {
    if (0 != ::Test::B::recall (in))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to recall ")
                         ACE_TEXT ("::Test::B data\n")),
                        -1);

    if (!(in >> this->c_value_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage c_value\n")),
                        -1);

    return in.good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void C::dump (std::ostream & output) 
  {
    ::Test::B::dump (output);
    output << "  c_value: " << this->c_value_ << std::endl;
  }

  // 
  // c_value
  // 
  ACE_INT32 C::c_value (void) const
  {
    return this->c_value_;
  }
}

