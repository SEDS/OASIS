// -*- C++ -*-

//============================================================================
/**
 * @file        TemperatureProbe_Metadata.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _TEMPERATUREPROBE_METADATA_H_
#define _TEMPERATUREPROBE_METADATA_H_

#include "oasis/probes/Software_Probe_Metadata.h"

#include "TemperatureProbe_stub_export.h"

namespace OASIS
{
  namespace HardwareProbes
  {
    /**
     * @class TemperatureProbe_Metadata
     */
    class OASIS_TEMPERATUREPROBE_STUB_Export TemperatureProbe_Metadata :
      public ::OASIS::Software_Probe_Metadata 
    {
      public:
      /// Default constructor
      TemperatureProbe_Metadata (void);

      /// Destructor
      virtual ~TemperatureProbe_Metadata (void);

      protected:
      /// Initalizing constructor
      TemperatureProbe_Metadata (const char * uuid,
                                 const char * type_info,
                                 ACE_UINT8 version_major,
                                 ACE_UINT8 version_minor,
                                 const char * schema);

      private:
      /// The metadata's schema
      static const char * __schema__;
    };
  }
}

#endif  // !defined __TEMPERATUREPROBE_METADATA_H__

