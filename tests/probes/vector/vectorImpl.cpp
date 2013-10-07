// $Id$

#include "vectorImpl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{

  // 
  // Int16_Vector_ProbeImpl
  // 
  Int16_Vector_ProbeImpl::Int16_Vector_ProbeImpl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // Int16_Vector_ProbeImpl::__metadata__
  // 
  const ::OASIS::Int16_Vector_Probe_Metadata Int16_Vector_ProbeImpl::__metadata__ =
  ::OASIS::Int16_Vector_Probe_Metadata ();


  // 
  // Int16_Vector_ProbeImpl::metadata
  // 
  const ::OASIS::Int16_Vector_Probe_Metadata & Int16_Vector_ProbeImpl::metadata (void) const 
  {
    return ::OASIS::Int16_Vector_ProbeImpl::__metadata__;
  }

  // 
  // ~Int16_Vector_ProbeImpl
  // 
  Int16_Vector_ProbeImpl::~Int16_Vector_ProbeImpl (void) 
  {
  }

  // 
  // package_data
  // 
  int Int16_Vector_ProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
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
  void Int16_Vector_ProbeImpl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
  }

  // 
  // value
  // 
  void Int16_Vector_ProbeImpl::value (const std::vector < ACE_INT16 > & value)
  {
    this->value_ = value;
  }

  // 
  // value
  // 
  const std::vector < ACE_INT16 > & Int16_Vector_ProbeImpl::value (void) const
  {
    return this->value_;
  }

  // 
  // value
  // 
  std::vector < ACE_INT16 > & Int16_Vector_ProbeImpl::value (void)
  {
    return this->value_;
  }
}

