// $Id$

#include "TemperatureProbeImpl.h"
#include "oasis/streams.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{
  namespace HardwareProbes
  {

    // 
    // TemperatureProbeImpl
    // 
    TemperatureProbeImpl::TemperatureProbeImpl (void) 
    {
       this->uuid_ = this->metadata ().uuid_;
    }

    // 
    // TemperatureProbeImpl::__metadata__
    // 
    const ::OASIS::HardwareProbes::TemperatureProbe_Metadata TemperatureProbeImpl::__metadata__ =
    ::OASIS::HardwareProbes::TemperatureProbe_Metadata ();


    // 
    // TemperatureProbeImpl::metadata
    // 
    const ::OASIS::HardwareProbes::TemperatureProbe_Metadata & TemperatureProbeImpl::metadata (void) const 
    {
      return ::OASIS::HardwareProbes::TemperatureProbeImpl::__metadata__;
    }

    // 
    // ~TemperatureProbeImpl
    // 
    TemperatureProbeImpl::~TemperatureProbeImpl (void) 
    {
    }

    // 
    // package_data
    // 
    int TemperatureProbeImpl::package_data (::OASIS::Software_Probe_Data_Packager & p) 
    {
      if (0 != ::OASIS::Software_Probe_Impl::package_data (p))
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                          -1);
      if (!(p.data_stream () << this->temperatureCelcius_))
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%T (%t) - %M - failed to package temperatureCelcius\n")),
                          -1);

      return p.data_stream ().good_bit () ? 0 : -1;
    }

    // 
    // dump
    // 
    void TemperatureProbeImpl::dump (std::ostream & output) 
    {
      ::OASIS::Software_Probe_Impl::dump (output);
      output << "  temperatureCelcius: " << this->temperatureCelcius () << std::endl;
    }

    // 
    // temperatureCelcius
    // 
    void TemperatureProbeImpl::temperatureCelcius (double temperatureCelcius)
    {
      this->temperatureCelcius_ = temperatureCelcius;
    }

    // 
    // temperatureCelcius
    // 
    double TemperatureProbeImpl::temperatureCelcius (void) const
    {
      return this->temperatureCelcius_;
    }
  }
}

