// -*- C++ -*-

//============================================================================
/**
 * @file       AnalogTemperatureProbe_Impl.h
 *
 *
 * @author      schafrikr
 *
 */
//============================================================================

#ifndef _TEMPERATUREPROBE_IMPL_
#define _TEMPERATUREPROBE_IMPL_

#include "TemperatureProbeImpl.h"
#include "TemperatureProbe_Impl_Export.h"
#include "oasis/probes/Software_Probe_Factory_T.h"

namespace OASIS
{
namespace HardwareProbes
{
namespace Temperature
{


/**
 * @class TemperatureProbe_Impl
 *
 * Implementation of the temperature probe. Only runs on linux
 * and collects its information from /proc/meminfo.
 */
class TEMPERATUREPROBE_IMPL_Export AnalogTemperatureProbe_Impl :
public TemperatureProbeImpl
{
public:
  /// Default constructor
  AnalogTemperatureProbe_Impl (void);

  /// Destructor
  virtual ~AnalogTemperatureProbe_Impl (void);

  virtual int init (const char * params, const char * name = 0);

  virtual int fini (void);

  /// Collect a new set of data.
  virtual int handle_collect_data (void);

protected:
  // Read the channel and set the temperature
  int read_channel(void);

  // Helper for parsing command-line arguments
  int parse_args (const char * args);

  // Temperature correction for the temperature probe
  float temperature_correction_;

  // File descriptor for kernel adc
  int fd_;

  // Hardware channel to query
  int channel_;

  // Debug flag
  bool debug_;
};

/// Type definition for the software probe's factory
typedef
 ::OASIS::Software_Probe_Factory_T <AnalogTemperatureProbe_Impl>
 AnalogTemperatureProbe_Impl_Factory;

/// Export the interface for the software probe factory.
OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_DECL (TEMPERATUREPROBE_IMPL_Export,
                          create_OASIS_HardwareProbes_Temperature_AnalogTemperatureProbe_Impl_Factory);
}
}
}
#endif  // !defined _TEMPERATUREPROBE_IMPL_

