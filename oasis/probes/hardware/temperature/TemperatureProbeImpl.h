// -*- C++ -*-

//============================================================================
/**
 * @file        TemperatureProbeImpl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _TEMPERATUREPROBEIMPL_H_
#define _TEMPERATUREPROBEIMPL_H_

#include "oasis/probes/Data_Types.h"
#include "TemperatureProbe_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

#include "TemperatureProbe_stub_export.h"

namespace OASIS
{
  namespace HardwareProbes
  {
    /**
     * @class TemperatureProbeImpl
     */
    class OASIS_TEMPERATUREPROBE_STUB_Export TemperatureProbeImpl :
      public virtual ::OASIS::Software_Probe_Impl
    {
      public:
      /// The metadata for the software probe.
      static const ::OASIS::HardwareProbes::TemperatureProbe_Metadata __metadata__;

      /// Default constructor
      TemperatureProbeImpl (void);

      /// Destructor
      virtual ~TemperatureProbeImpl (void);

      /// Getter for the probe's metadata
      virtual const ::OASIS::HardwareProbes::TemperatureProbe_Metadata & metadata (void) const;

      /// Package the software probe's data.
      protected:
      virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


      public:
      /// Impl_Dump the software probe's data.
      virtual void dump (std::ostream & output);


      public:
      // Setter and getter methods for temperatureCelcius
      void temperatureCelcius (double temperatureCelcius);
      double temperatureCelcius (void) const;

      protected:
      double temperatureCelcius_;
    };
  }
}

#endif  // !defined __TEMPERATUREPROBEIMPL_H__

