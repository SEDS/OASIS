// $Id$

#include "Smoke_Test_ProbeImpl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"


// 
// AImpl
// 
AImpl::AImpl (void) 
{
   this->uuid_ = this->metadata ().uuid_;
}

// 
// AImpl::__metadata__
// 
const ::A_Metadata AImpl::__metadata__ =
::A_Metadata ();


// 
// AImpl::metadata
// 
const ::A_Metadata & AImpl::metadata (void) const 
{
  return ::AImpl::__metadata__;
}

// 
// ~AImpl
// 
AImpl::~AImpl (void) 
{
}

// 
// package_data
// 
int AImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
{
  if (0 != ::OASIS::Software_Probe_Impl::package_data (p))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                      -1);
  if (!(p.data_stream () << this->a_value_))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to package a_value\n")),
                      -1);

  return p.data_stream ().good_bit () ? 0 : -1;
}

// 
// dump
// 
void AImpl::dump (std::ostream & output) 
{
  ::OASIS::Software_Probe_Impl::dump (output);
  output << "  a_value: " << this->a_value () << std::endl;
}

// 
// a_value
// 
void AImpl::a_value (ACE_INT32 a_value)
{
  this->a_value_ = a_value;
}

// 
// a_value
// 
ACE_INT32 AImpl::a_value (void) const
{
  return this->a_value_;
}

namespace SmokeTest
{

  // 
  // BImpl
  // 
  BImpl::BImpl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // BImpl::__metadata__
  // 
  const ::SmokeTest::B_Metadata BImpl::__metadata__ =
  ::SmokeTest::B_Metadata ();


  // 
  // BImpl::metadata
  // 
  const ::SmokeTest::B_Metadata & BImpl::metadata (void) const 
  {
    return ::SmokeTest::BImpl::__metadata__;
  }

  // 
  // ~BImpl
  // 
  BImpl::~BImpl (void) 
  {
  }

  // 
  // package_data
  // 
  int BImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
  {
    if (0 != ::AImpl::package_data (p))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                        -1);
    if (!(p.data_stream () << this->b_value_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package b_value\n")),
                        -1);

    return p.data_stream ().good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void BImpl::dump (std::ostream & output) 
  {
    ::AImpl::dump (output);
    output << "  b_value: " << this->b_value () << std::endl;
  }

  // 
  // b_value
  // 
  void BImpl::b_value (ACE_INT32 b_value)
  {
    this->b_value_ = b_value;
  }

  // 
  // b_value
  // 
  ACE_INT32 BImpl::b_value (void) const
  {
    return this->b_value_;
  }


  // 
  // CImpl
  // 
  CImpl::CImpl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // CImpl::__metadata__
  // 
  const ::SmokeTest::C_Metadata CImpl::__metadata__ =
  ::SmokeTest::C_Metadata ();


  // 
  // CImpl::metadata
  // 
  const ::SmokeTest::C_Metadata & CImpl::metadata (void) const 
  {
    return ::SmokeTest::CImpl::__metadata__;
  }

  // 
  // ~CImpl
  // 
  CImpl::~CImpl (void) 
  {
  }

  // 
  // package_data
  // 
  int CImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
  {
    if (0 != ::SmokeTest::BImpl::package_data (p))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                        -1);
    if (!(p.data_stream () << this->c_value_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package c_value\n")),
                        -1);

    return p.data_stream ().good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void CImpl::dump (std::ostream & output) 
  {
    ::SmokeTest::BImpl::dump (output);
    output << "  c_value: " << this->c_value () << std::endl;
  }

  // 
  // c_value
  // 
  void CImpl::c_value (ACE_INT32 c_value)
  {
    this->c_value_ = c_value;
  }

  // 
  // c_value
  // 
  ACE_INT32 CImpl::c_value (void) const
  {
    return this->c_value_;
  }
}

