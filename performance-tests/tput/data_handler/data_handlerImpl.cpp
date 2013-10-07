// $Id$

#include "data_handlerImpl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"

namespace Test
{

  // 
  // Byte_0Impl
  // 
  Byte_0Impl::Byte_0Impl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // Byte_0Impl::__metadata__
  // 
  const ::Test::Byte_0_Metadata Byte_0Impl::__metadata__ =
  ::Test::Byte_0_Metadata ();


  // 
  // Byte_0Impl::metadata
  // 
  const ::Test::Byte_0_Metadata & Byte_0Impl::metadata (void) const 
  {
    return ::Test::Byte_0Impl::__metadata__;
  }

  // 
  // ~Byte_0Impl
  // 
  Byte_0Impl::~Byte_0Impl (void) 
  {
  }

  // 
  // package_data
  // 
  int Byte_0Impl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
  {
    if (0 != ::OASIS::Software_Probe_Impl::package_data (p))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                        -1);
    return p.data_stream ().good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void Byte_0Impl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
  }


  // 
  // Byte_8Impl
  // 
  Byte_8Impl::Byte_8Impl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // Byte_8Impl::__metadata__
  // 
  const ::Test::Byte_8_Metadata Byte_8Impl::__metadata__ =
  ::Test::Byte_8_Metadata ();


  // 
  // Byte_8Impl::metadata
  // 
  const ::Test::Byte_8_Metadata & Byte_8Impl::metadata (void) const 
  {
    return ::Test::Byte_8Impl::__metadata__;
  }

  // 
  // ~Byte_8Impl
  // 
  Byte_8Impl::~Byte_8Impl (void) 
  {
  }

  // 
  // package_data
  // 
  int Byte_8Impl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
  {
    if (0 != ::OASIS::Software_Probe_Impl::package_data (p))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                        -1);
    if (!(p.data_stream () << this->value_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package value\n")),
                        -1);

    return p.data_stream ().good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void Byte_8Impl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
    output << "  value: " << this->value () << std::endl;
  }

  // 
  // value
  // 
  void Byte_8Impl::value (ACE_INT8 value)
  {
    this->value_ = value;
  }

  // 
  // value
  // 
  ACE_INT8 Byte_8Impl::value (void) const
  {
    return this->value_;
  }


  // 
  // Byte_16Impl
  // 
  Byte_16Impl::Byte_16Impl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // Byte_16Impl::__metadata__
  // 
  const ::Test::Byte_16_Metadata Byte_16Impl::__metadata__ =
  ::Test::Byte_16_Metadata ();


  // 
  // Byte_16Impl::metadata
  // 
  const ::Test::Byte_16_Metadata & Byte_16Impl::metadata (void) const 
  {
    return ::Test::Byte_16Impl::__metadata__;
  }

  // 
  // ~Byte_16Impl
  // 
  Byte_16Impl::~Byte_16Impl (void) 
  {
  }

  // 
  // package_data
  // 
  int Byte_16Impl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
  {
    if (0 != ::OASIS::Software_Probe_Impl::package_data (p))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                        -1);
    if (!(p.data_stream () << this->value_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package value\n")),
                        -1);

    return p.data_stream ().good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void Byte_16Impl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
    output << "  value: " << this->value () << std::endl;
  }

  // 
  // value
  // 
  void Byte_16Impl::value (ACE_UINT16 value)
  {
    this->value_ = value;
  }

  // 
  // value
  // 
  ACE_UINT16 Byte_16Impl::value (void) const
  {
    return this->value_;
  }


  // 
  // Byte_32Impl
  // 
  Byte_32Impl::Byte_32Impl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // Byte_32Impl::__metadata__
  // 
  const ::Test::Byte_32_Metadata Byte_32Impl::__metadata__ =
  ::Test::Byte_32_Metadata ();


  // 
  // Byte_32Impl::metadata
  // 
  const ::Test::Byte_32_Metadata & Byte_32Impl::metadata (void) const 
  {
    return ::Test::Byte_32Impl::__metadata__;
  }

  // 
  // ~Byte_32Impl
  // 
  Byte_32Impl::~Byte_32Impl (void) 
  {
  }

  // 
  // package_data
  // 
  int Byte_32Impl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
  {
    if (0 != ::OASIS::Software_Probe_Impl::package_data (p))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                        -1);
    if (!(p.data_stream () << this->value_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package value\n")),
                        -1);

    return p.data_stream ().good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void Byte_32Impl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
    output << "  value: " << this->value () << std::endl;
  }

  // 
  // value
  // 
  void Byte_32Impl::value (ACE_UINT32 value)
  {
    this->value_ = value;
  }

  // 
  // value
  // 
  ACE_UINT32 Byte_32Impl::value (void) const
  {
    return this->value_;
  }


  // 
  // Byte_64Impl
  // 
  Byte_64Impl::Byte_64Impl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // Byte_64Impl::__metadata__
  // 
  const ::Test::Byte_64_Metadata Byte_64Impl::__metadata__ =
  ::Test::Byte_64_Metadata ();


  // 
  // Byte_64Impl::metadata
  // 
  const ::Test::Byte_64_Metadata & Byte_64Impl::metadata (void) const 
  {
    return ::Test::Byte_64Impl::__metadata__;
  }

  // 
  // ~Byte_64Impl
  // 
  Byte_64Impl::~Byte_64Impl (void) 
  {
  }

  // 
  // package_data
  // 
  int Byte_64Impl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
  {
    if (0 != ::OASIS::Software_Probe_Impl::package_data (p))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                        -1);
    if (!(p.data_stream () << this->value_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package value\n")),
                        -1);

    return p.data_stream ().good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void Byte_64Impl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
    output << "  value: " << this->value () << std::endl;
  }

  // 
  // value
  // 
  void Byte_64Impl::value (ACE_UINT64 value)
  {
    this->value_ = value;
  }

  // 
  // value
  // 
  ACE_UINT64 Byte_64Impl::value (void) const
  {
    return this->value_;
  }


  // 
  // Byte_128Impl
  // 
  Byte_128Impl::Byte_128Impl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // Byte_128Impl::__metadata__
  // 
  const ::Test::Byte_128_Metadata Byte_128Impl::__metadata__ =
  ::Test::Byte_128_Metadata ();


  // 
  // Byte_128Impl::metadata
  // 
  const ::Test::Byte_128_Metadata & Byte_128Impl::metadata (void) const 
  {
    return ::Test::Byte_128Impl::__metadata__;
  }

  // 
  // ~Byte_128Impl
  // 
  Byte_128Impl::~Byte_128Impl (void) 
  {
  }

  // 
  // package_data
  // 
  int Byte_128Impl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
  {
    if (0 != ::OASIS::Software_Probe_Impl::package_data (p))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                        -1);
    if (!(p.data_stream () << this->value_a_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package value_a\n")),
                        -1);

    if (!(p.data_stream () << this->value_b_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package value_b\n")),
                        -1);

    return p.data_stream ().good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void Byte_128Impl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
    output << "  value_a: " << this->value_a () << std::endl;
    output << "  value_b: " << this->value_b () << std::endl;
  }

  // 
  // value_a
  // 
  void Byte_128Impl::value_a (ACE_UINT64 value_a)
  {
    this->value_a_ = value_a;
  }

  // 
  // value_a
  // 
  ACE_UINT64 Byte_128Impl::value_a (void) const
  {
    return this->value_a_;
  }

  // 
  // value_b
  // 
  void Byte_128Impl::value_b (ACE_UINT64 value_b)
  {
    this->value_b_ = value_b;
  }

  // 
  // value_b
  // 
  ACE_UINT64 Byte_128Impl::value_b (void) const
  {
    return this->value_b_;
  }


  // 
  // Byte_256Impl
  // 
  Byte_256Impl::Byte_256Impl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // Byte_256Impl::__metadata__
  // 
  const ::Test::Byte_256_Metadata Byte_256Impl::__metadata__ =
  ::Test::Byte_256_Metadata ();


  // 
  // Byte_256Impl::metadata
  // 
  const ::Test::Byte_256_Metadata & Byte_256Impl::metadata (void) const 
  {
    return ::Test::Byte_256Impl::__metadata__;
  }

  // 
  // ~Byte_256Impl
  // 
  Byte_256Impl::~Byte_256Impl (void) 
  {
  }

  // 
  // package_data
  // 
  int Byte_256Impl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
  {
    if (0 != ::OASIS::Software_Probe_Impl::package_data (p))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                        -1);
    if (!(p.data_stream () << this->value_a_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package value_a\n")),
                        -1);

    if (!(p.data_stream () << this->value_b_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package value_b\n")),
                        -1);

    if (!(p.data_stream () << this->value_c_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package value_c\n")),
                        -1);

    if (!(p.data_stream () << this->value_d_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package value_d\n")),
                        -1);

    return p.data_stream ().good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void Byte_256Impl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
    output << "  value_a: " << this->value_a () << std::endl;
    output << "  value_b: " << this->value_b () << std::endl;
    output << "  value_c: " << this->value_c () << std::endl;
    output << "  value_d: " << this->value_d () << std::endl;
  }

  // 
  // value_a
  // 
  void Byte_256Impl::value_a (ACE_UINT64 value_a)
  {
    this->value_a_ = value_a;
  }

  // 
  // value_a
  // 
  ACE_UINT64 Byte_256Impl::value_a (void) const
  {
    return this->value_a_;
  }

  // 
  // value_b
  // 
  void Byte_256Impl::value_b (ACE_UINT64 value_b)
  {
    this->value_b_ = value_b;
  }

  // 
  // value_b
  // 
  ACE_UINT64 Byte_256Impl::value_b (void) const
  {
    return this->value_b_;
  }

  // 
  // value_c
  // 
  void Byte_256Impl::value_c (ACE_UINT64 value_c)
  {
    this->value_c_ = value_c;
  }

  // 
  // value_c
  // 
  ACE_UINT64 Byte_256Impl::value_c (void) const
  {
    return this->value_c_;
  }

  // 
  // value_d
  // 
  void Byte_256Impl::value_d (ACE_UINT64 value_d)
  {
    this->value_d_ = value_d;
  }

  // 
  // value_d
  // 
  ACE_UINT64 Byte_256Impl::value_d (void) const
  {
    return this->value_d_;
  }
}

