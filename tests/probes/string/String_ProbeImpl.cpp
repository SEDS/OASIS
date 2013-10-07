// $Id$

#include "String_ProbeImpl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{

  // 
  // String_SoftwareProbeImpl
  // 
  String_SoftwareProbeImpl::String_SoftwareProbeImpl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // String_SoftwareProbeImpl::__metadata__
  // 
  const ::OASIS::String_SoftwareProbe_Metadata String_SoftwareProbeImpl::__metadata__ =
  ::OASIS::String_SoftwareProbe_Metadata ();


  // 
  // String_SoftwareProbeImpl::metadata
  // 
  const ::OASIS::String_SoftwareProbe_Metadata & String_SoftwareProbeImpl::metadata (void) const 
  {
    return ::OASIS::String_SoftwareProbeImpl::__metadata__;
  }

  // 
  // ~String_SoftwareProbeImpl
  // 
  String_SoftwareProbeImpl::~String_SoftwareProbeImpl (void) 
  {
  }

  // 
  // package_data
  // 
  int String_SoftwareProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
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
  void String_SoftwareProbeImpl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
    output << "  value: " << this->value () << std::endl;
  }

  // 
  // value
  // 
  void String_SoftwareProbeImpl::value (const ACE_CString & value)
  {
    this->value_ = value;
  }

  // 
  // value
  // 
  const ACE_CString & String_SoftwareProbeImpl::value (void) const
  {
    return this->value_;
  }
}

