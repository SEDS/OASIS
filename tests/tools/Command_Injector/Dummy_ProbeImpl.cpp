// $Id$

#include "Dummy_ProbeImpl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"


// 
// Dummy_ProbeImpl
// 
Dummy_ProbeImpl::Dummy_ProbeImpl (void) 
{
   this->uuid_ = this->metadata ().uuid_;
}

// 
// Dummy_ProbeImpl::__metadata__
// 
const ::Dummy_Probe_Metadata Dummy_ProbeImpl::__metadata__ =
::Dummy_Probe_Metadata ();


// 
// Dummy_ProbeImpl::metadata
// 
const ::Dummy_Probe_Metadata & Dummy_ProbeImpl::metadata (void) const 
{
  return ::Dummy_ProbeImpl::__metadata__;
}

// 
// ~Dummy_ProbeImpl
// 
Dummy_ProbeImpl::~Dummy_ProbeImpl (void) 
{
}

// 
// package_data
// 
int Dummy_ProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
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
void Dummy_ProbeImpl::dump (std::ostream & output) 
{
  ::OASIS::Software_Probe_Impl::dump (output);
}

