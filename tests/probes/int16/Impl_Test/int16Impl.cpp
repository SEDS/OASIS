// $Id$

#include "int16Impl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{

  // 
  // Int16_SoftwareProbeImpl
  // 
  Int16_SoftwareProbeImpl::Int16_SoftwareProbeImpl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // Int16_SoftwareProbeImpl::__metadata__
  // 
  const ::OASIS::Int16_SoftwareProbe_Metadata Int16_SoftwareProbeImpl::__metadata__ =
  ::OASIS::Int16_SoftwareProbe_Metadata ();


  // 
  // Int16_SoftwareProbeImpl::metadata
  // 
  const ::OASIS::Int16_SoftwareProbe_Metadata & Int16_SoftwareProbeImpl::metadata (void) const 
  {
    return ::OASIS::Int16_SoftwareProbeImpl::__metadata__;
  }

  // 
  // ~Int16_SoftwareProbeImpl
  // 
  Int16_SoftwareProbeImpl::~Int16_SoftwareProbeImpl (void) 
  {
  }

  // 
  // package_data
  // 
  int Int16_SoftwareProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
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
  void Int16_SoftwareProbeImpl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
    output << "  value: " << this->value () << std::endl;
  }

  // 
  // value
  // 
  void Int16_SoftwareProbeImpl::value (ACE_INT16 value)
  {
    this->value_ = value;
  }

  // 
  // value
  // 
  ACE_INT16 Int16_SoftwareProbeImpl::value (void) const
  {
    return this->value_;
  }
}

