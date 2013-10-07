// $Id$

#include "TemperatureProbe.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{
  namespace HardwareProbes
  {

    // 
    // TemperatureProbe::__metadata__
    // 
    const TemperatureProbe::METADATA_TYPE TemperatureProbe::__metadata__;

    // 
    // TemperatureProbe::metadata
    // 
    const TemperatureProbe::METADATA_TYPE & TemperatureProbe::metadata (void) const 
    {
      return ::OASIS::HardwareProbes::TemperatureProbe::__metadata__;
    }

    // 
    // TemperatureProbe
    // 
    TemperatureProbe::TemperatureProbe (void) 
    {
    }

    // 
    // ~TemperatureProbe
    // 
    TemperatureProbe::~TemperatureProbe (void) 
    {
    }

    // 
    // recall
    // 
    int TemperatureProbe::
    recall (const char * data, size_t length, int byte_order) 
    {
      ::OASIS::Software_Probe_Data_Preparer prep (data, length);
      ACE_InputCDR input (prep.message_block (), byte_order);
      return ::OASIS::HardwareProbes::TemperatureProbe::recall (input);
    }


    // 
    // recall
    // 
    int TemperatureProbe::recall (ACE_InputCDR & in) 
    {
      if (0 != ::OASIS::Software_Probe::recall (in))
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%T (%t) - %M - failed to recall ")
                           ACE_TEXT ("::OASIS::Software_Probe data\n")),
                          -1);

      if (!(in >> this->temperatureCelcius_))
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%T (%t) - %M - failed to unpackage temperatureCelcius\n")),
                          -1);

      return in.good_bit () ? 0 : -1;
    }

    // 
    // dump
    // 
    void TemperatureProbe::dump (std::ostream & output) 
    {
      ::OASIS::Software_Probe::dump (output);
      output << "  temperatureCelcius: " << this->temperatureCelcius_ << std::endl;
    }

    // 
    // temperatureCelcius
    // 
    double TemperatureProbe::temperatureCelcius (void) const
    {
      return this->temperatureCelcius_;
    }
  }
}

