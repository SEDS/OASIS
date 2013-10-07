// $Id$

#include "int64Impl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{

  // 
  // Int64_SoftwareProbeImpl
  // 
  Int64_SoftwareProbeImpl::Int64_SoftwareProbeImpl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // Int64_SoftwareProbeImpl::__metadata__
  // 
  const ::OASIS::Int64_SoftwareProbe_Metadata Int64_SoftwareProbeImpl::__metadata__ =
  ::OASIS::Int64_SoftwareProbe_Metadata ();


  // 
  // Int64_SoftwareProbeImpl::metadata
  // 
  const ::OASIS::Int64_SoftwareProbe_Metadata & Int64_SoftwareProbeImpl::metadata (void) const 
  {
    return ::OASIS::Int64_SoftwareProbeImpl::__metadata__;
  }

  // 
  // ~Int64_SoftwareProbeImpl
  // 
  Int64_SoftwareProbeImpl::~Int64_SoftwareProbeImpl (void) 
  {
  }

  // 
  // package_data
  // 
  int Int64_SoftwareProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
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
  void Int64_SoftwareProbeImpl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
    output << "  value: " << this->value () << std::endl;
  }

  // 
  // value
  // 
  void Int64_SoftwareProbeImpl::value (ACE_INT64 value)
  {
    this->value_ = value;
  }

  // 
  // value
  // 
  ACE_INT64 Int64_SoftwareProbeImpl::value (void) const
  {
    return this->value_;
  }
}

