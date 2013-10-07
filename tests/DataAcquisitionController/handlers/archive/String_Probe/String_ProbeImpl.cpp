// $Id$

#include "String_ProbeImpl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"

namespace Test
{

  // 
  // String_ProbeImpl
  // 
  String_ProbeImpl::String_ProbeImpl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // String_ProbeImpl::__metadata__
  // 
  const ::Test::String_Probe_Metadata String_ProbeImpl::__metadata__ =
  ::Test::String_Probe_Metadata ();


  // 
  // String_ProbeImpl::metadata
  // 
  const ::Test::String_Probe_Metadata & String_ProbeImpl::metadata (void) const 
  {
    return ::Test::String_ProbeImpl::__metadata__;
  }

  // 
  // ~String_ProbeImpl
  // 
  String_ProbeImpl::~String_ProbeImpl (void) 
  {
  }

  // 
  // package_data
  // 
  int String_ProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
  {
    if (0 != ::OASIS::Software_Probe_Impl::package_data (p))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                        -1);
    if (!(p.data_stream () << this->str_value_))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to package str_value\n")),
                        -1);

    return p.data_stream ().good_bit () ? 0 : -1;
  }

  // 
  // dump
  // 
  void String_ProbeImpl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
    output << "  str_value: " << this->str_value () << std::endl;
  }

  // 
  // str_value
  // 
  void String_ProbeImpl::str_value (const ACE_CString & str_value)
  {
    this->str_value_ = str_value;
  }

  // 
  // str_value
  // 
  const ACE_CString & String_ProbeImpl::str_value (void) const
  {
    return this->str_value_;
  }
}

