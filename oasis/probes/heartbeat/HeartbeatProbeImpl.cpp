// $Id$

#include "HeartbeatProbeImpl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{

  // 
  // HeartbeatProbeImpl
  // 
  HeartbeatProbeImpl::HeartbeatProbeImpl (void) 
  {
     this->uuid_ = this->metadata ().uuid_;
  }

  // 
  // HeartbeatProbeImpl::__metadata__
  // 
  const ::OASIS::HeartbeatProbe_Metadata HeartbeatProbeImpl::__metadata__ =
  ::OASIS::HeartbeatProbe_Metadata ();


  // 
  // HeartbeatProbeImpl::metadata
  // 
  const ::OASIS::HeartbeatProbe_Metadata & HeartbeatProbeImpl::metadata (void) const 
  {
    return ::OASIS::HeartbeatProbeImpl::__metadata__;
  }

  // 
  // ~HeartbeatProbeImpl
  // 
  HeartbeatProbeImpl::~HeartbeatProbeImpl (void) 
  {
  }

  // 
  // package_data
  // 
  int HeartbeatProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
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
  void HeartbeatProbeImpl::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe_Impl::dump (output);
  }
}

