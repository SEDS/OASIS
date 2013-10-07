// $Id$

#include "nodataImpl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"

namespace Test
{

  // 
  // NoDataProbeImpl
  // 
  NoDataProbeImpl::NoDataProbeImpl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // NoDataProbeImpl::__metadata__
  // 
  const ::Test::NoDataProbe_Metadata NoDataProbeImpl::__metadata__ =
  ::Test::NoDataProbe_Metadata ();


  // 
  // NoDataProbeImpl::metadata
  // 
  const ::Test::NoDataProbe_Metadata & NoDataProbeImpl::metadata (void) const 
  {
    return ::Test::NoDataProbeImpl::__metadata__;
  }

  // 
  // ~NoDataProbeImpl
  // 
  NoDataProbeImpl::~NoDataProbeImpl (void) 
  {
  }

  // 
  // package_data
  // 
  int NoDataProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
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
  void NoDataProbeImpl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
  }
}

