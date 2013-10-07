// $Id$

#include "data_handler.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/probes/Data_Streams_T.h"

namespace Test
{

  // 
  // Byte_0::__metadata__
  // 
  const Byte_0::METADATA_TYPE Byte_0::__metadata__;

  // 
  // Byte_0::metadata
  // 
  const Byte_0::METADATA_TYPE & Byte_0::metadata (void) const 
  {
    return ::Test::Byte_0::__metadata__;
  }

  // 
  // Byte_0
  // 
  Byte_0::Byte_0 (void) 
  {
  }

  // 
  // ~Byte_0
  // 
  Byte_0::~Byte_0 (void) 
  {
  }

  // 
  // recall
  // 
  int Byte_0::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::Test::Byte_0::recall (input);
  }


  // 
  // recall
  // 
  int Byte_0::recall (ACE_InputCDR & in) 
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
  void Byte_0::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe::dump (output);
  }


  // 
  // Byte_8::__metadata__
  // 
  const Byte_8::METADATA_TYPE Byte_8::__metadata__;

  // 
  // Byte_8::metadata
  // 
  const Byte_8::METADATA_TYPE & Byte_8::metadata (void) const 
  {
    return ::Test::Byte_8::__metadata__;
  }

  // 
  // Byte_8
  // 
  Byte_8::Byte_8 (void) 
  {
  }

  // 
  // ~Byte_8
  // 
  Byte_8::~Byte_8 (void) 
  {
  }

  // 
  // recall
  // 
  int Byte_8::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::Test::Byte_8::recall (input);
  }


  // 
  // recall
  // 
  int Byte_8::recall (ACE_InputCDR & in) 
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
  void Byte_8::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe::dump (output);
    output << "  value: " << this->value_ << std::endl;
  }

  // 
  // value
  // 
  ACE_INT8 Byte_8::value (void) const
  {
    return this->value_;
  }


  // 
  // Byte_16::__metadata__
  // 
  const Byte_16::METADATA_TYPE Byte_16::__metadata__;

  // 
  // Byte_16::metadata
  // 
  const Byte_16::METADATA_TYPE & Byte_16::metadata (void) const 
  {
    return ::Test::Byte_16::__metadata__;
  }

  // 
  // Byte_16
  // 
  Byte_16::Byte_16 (void) 
  {
  }

  // 
  // ~Byte_16
  // 
  Byte_16::~Byte_16 (void) 
  {
  }

  // 
  // recall
  // 
  int Byte_16::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::Test::Byte_16::recall (input);
  }


  // 
  // recall
  // 
  int Byte_16::recall (ACE_InputCDR & in) 
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
  void Byte_16::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe::dump (output);
    output << "  value: " << this->value_ << std::endl;
  }

  // 
  // value
  // 
  ACE_UINT16 Byte_16::value (void) const
  {
    return this->value_;
  }


  // 
  // Byte_32::__metadata__
  // 
  const Byte_32::METADATA_TYPE Byte_32::__metadata__;

  // 
  // Byte_32::metadata
  // 
  const Byte_32::METADATA_TYPE & Byte_32::metadata (void) const 
  {
    return ::Test::Byte_32::__metadata__;
  }

  // 
  // Byte_32
  // 
  Byte_32::Byte_32 (void) 
  {
  }

  // 
  // ~Byte_32
  // 
  Byte_32::~Byte_32 (void) 
  {
  }

  // 
  // recall
  // 
  int Byte_32::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::Test::Byte_32::recall (input);
  }


  // 
  // recall
  // 
  int Byte_32::recall (ACE_InputCDR & in) 
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
  void Byte_32::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe::dump (output);
    output << "  value: " << this->value_ << std::endl;
  }

  // 
  // value
  // 
  ACE_UINT32 Byte_32::value (void) const
  {
    return this->value_;
  }


  // 
  // Byte_64::__metadata__
  // 
  const Byte_64::METADATA_TYPE Byte_64::__metadata__;

  // 
  // Byte_64::metadata
  // 
  const Byte_64::METADATA_TYPE & Byte_64::metadata (void) const 
  {
    return ::Test::Byte_64::__metadata__;
  }

  // 
  // Byte_64
  // 
  Byte_64::Byte_64 (void) 
  {
  }

  // 
  // ~Byte_64
  // 
  Byte_64::~Byte_64 (void) 
  {
  }

  // 
  // recall
  // 
  int Byte_64::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::Test::Byte_64::recall (input);
  }


  // 
  // recall
  // 
  int Byte_64::recall (ACE_InputCDR & in) 
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
  void Byte_64::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe::dump (output);
    output << "  value: " << this->value_ << std::endl;
  }

  // 
  // value
  // 
  ACE_UINT64 Byte_64::value (void) const
  {
    return this->value_;
  }


  // 
  // Byte_128::__metadata__
  // 
  const Byte_128::METADATA_TYPE Byte_128::__metadata__;

  // 
  // Byte_128::metadata
  // 
  const Byte_128::METADATA_TYPE & Byte_128::metadata (void) const 
  {
    return ::Test::Byte_128::__metadata__;
  }

  // 
  // Byte_128
  // 
  Byte_128::Byte_128 (void) 
  {
  }

  // 
  // ~Byte_128
  // 
  Byte_128::~Byte_128 (void) 
  {
  }

  // 
  // recall
  // 
  int Byte_128::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::Test::Byte_128::recall (input);
  }


  // 
  // recall
  // 
  int Byte_128::recall (ACE_InputCDR & in) 
  {
    if (0 != ::OASIS::Software_Probe::recall (in))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to recall ")
                         ACE_TEXT ("::OASIS::Software_Probe data\n")),
                        -1);

    if (!(in >> this->value_a_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage value_a\n")),
                        -1);

    if (!(in >> this->value_b_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage value_b\n")),
                        -1);

    return in.good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void Byte_128::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe::dump (output);
    output << "  value_a: " << this->value_a_ << std::endl;
    output << "  value_b: " << this->value_b_ << std::endl;
  }

  // 
  // value_a
  // 
  ACE_UINT64 Byte_128::value_a (void) const
  {
    return this->value_a_;
  }

  // 
  // value_b
  // 
  ACE_UINT64 Byte_128::value_b (void) const
  {
    return this->value_b_;
  }


  // 
  // Byte_256::__metadata__
  // 
  const Byte_256::METADATA_TYPE Byte_256::__metadata__;

  // 
  // Byte_256::metadata
  // 
  const Byte_256::METADATA_TYPE & Byte_256::metadata (void) const 
  {
    return ::Test::Byte_256::__metadata__;
  }

  // 
  // Byte_256
  // 
  Byte_256::Byte_256 (void) 
  {
  }

  // 
  // ~Byte_256
  // 
  Byte_256::~Byte_256 (void) 
  {
  }

  // 
  // recall
  // 
  int Byte_256::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::Test::Byte_256::recall (input);
  }


  // 
  // recall
  // 
  int Byte_256::recall (ACE_InputCDR & in) 
  {
    if (0 != ::OASIS::Software_Probe::recall (in))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to recall ")
                         ACE_TEXT ("::OASIS::Software_Probe data\n")),
                        -1);

    if (!(in >> this->value_a_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage value_a\n")),
                        -1);

    if (!(in >> this->value_b_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage value_b\n")),
                        -1);

    if (!(in >> this->value_c_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage value_c\n")),
                        -1);

    if (!(in >> this->value_d_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to unpackage value_d\n")),
                        -1);

    return in.good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void Byte_256::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe::dump (output);
    output << "  value_a: " << this->value_a_ << std::endl;
    output << "  value_b: " << this->value_b_ << std::endl;
    output << "  value_c: " << this->value_c_ << std::endl;
    output << "  value_d: " << this->value_d_ << std::endl;
  }

  // 
  // value_a
  // 
  ACE_UINT64 Byte_256::value_a (void) const
  {
    return this->value_a_;
  }

  // 
  // value_b
  // 
  ACE_UINT64 Byte_256::value_b (void) const
  {
    return this->value_b_;
  }

  // 
  // value_c
  // 
  ACE_UINT64 Byte_256::value_c (void) const
  {
    return this->value_c_;
  }

  // 
  // value_d
  // 
  ACE_UINT64 Byte_256::value_d (void) const
  {
    return this->value_d_;
  }
}

