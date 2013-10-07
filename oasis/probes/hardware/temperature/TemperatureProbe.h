// -*- C++ -*-

//============================================================================
/**
 * @file        TemperatureProbe.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _TEMPERATUREPROBE_H_
#define _TEMPERATUREPROBE_H_

#include "oasis/probes/Data_Types.h"
#include "oasis/probes/Software_Probe.h"
#include "TemperatureProbe_Metadata.h"
#include <iostream>

#include "TemperatureProbe_stub_export.h"

namespace OASIS
{
  namespace HardwareProbes
  {
    /**
     * @class TemperatureProbe
     */
    class OASIS_TEMPERATUREPROBE_STUB_Export TemperatureProbe :
      public virtual ::OASIS::Software_Probe 
    {
      public:
      // Type definition of the software probe's metadata.
      typedef ::OASIS::HardwareProbes::TemperatureProbe_Metadata METADATA_TYPE;

      /// The metadata for the software probe.
      static const METADATA_TYPE __metadata__;

      /// Default constructor
      TemperatureProbe (void);

      /// Destructor
      virtual ~TemperatureProbe (void);

      /// Getter for the probe's metadata
      virtual const METADATA_TYPE & metadata (void) const;

      public:
      /// Recall the software probe's data.
      virtual int recall (const char * data, size_t length, int byte_order);

      protected:
      /// Helper method for recalling the data.
      int recall (ACE_InputCDR & input);

      public:
      /// Stub_Dump the software probe's data.
      virtual void dump (std::ostream & output);


      public:
      // Getter method for temperatureCelcius
      double temperatureCelcius (void) const;

      protected:
      double temperatureCelcius_;
    };
  }
}

#endif  // !defined __TEMPERATUREPROBE_H__

