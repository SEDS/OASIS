// $Id$

#include "FooImpl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{

  // 
  // FooImpl
  // 
  FooImpl::FooImpl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // FooImpl::__metadata__
  // 
  const ::OASIS::Foo_Metadata FooImpl::__metadata__ =
  ::OASIS::Foo_Metadata ();


  // 
  // FooImpl::metadata
  // 
  const ::OASIS::Foo_Metadata & FooImpl::metadata (void) const 
  {
    return ::OASIS::FooImpl::__metadata__;
  }

  // 
  // ~FooImpl
  // 
  FooImpl::~FooImpl (void) 
  {
  }

  // 
  // package_data
  // 
  int FooImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
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
  void FooImpl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
  }
}

