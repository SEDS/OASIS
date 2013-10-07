// -*- C++ -*-

//============================================================================
/**
 * @file        NetworkProbe_Impl.h
 *
 * $Id: NetworkProbe_Impl.h 2232 2013-01-28 16:07:41Z dfeiock $
 *
 * @author      Harold Owens II (owensh at cs dot iupui dot edu)
 *
 */
//============================================================================

#ifndef _NETWORKPROBE_IMPL_H_
#define _NETWORKPROBE_IMPL_H_

#include "NetworkProbeImpl.h"
#include "NetworkProbe_Impl_export.h"
#include "oasis/probes/Software_Probe_Factory_T.h"

namespace OASIS
{
namespace System
{
namespace Network
{
  // Forward decl.
  class Procnetdev_Parser;

/**
 * @class NetworkProbe_Impl
 *
 * Implementation of the network probe. Depending on the operating
 * system, the probe is implemented differently. For example, the
 * Windows version used Win32 API; whereas, the Linux version collects
 * its information from /proc/net/dev.
 */
class NETWORKPROBE_IMPL_Export SystemNetworkProbe_Impl :
#if defined (_WIN32)
  public ::OASIS::System::Network::WindowsNetworkProbeImpl
#else
  public ::OASIS::System::Network::LinuxNetworkProbeImpl
#endif
{
public:
  /// Default constructor
  SystemNetworkProbe_Impl (void);

  /// Destructor
  virtual ~SystemNetworkProbe_Impl (void);

  /// Collect a new set of data.
  virtual int handle_collect_data (void);

  /// Initialize the software probe.
  virtual int init (const char * params, const char * name = 0);

protected:
  /// Helper for parsing command-line arguments
  int parse_args (const char * args);

  /// Helper method that handles the --nic option.
  int handle_nic_command (const char * args);

#if !defined (_WIN32)
  /// Parser for extracting information from /proc/net/dev.
  ACE_Auto_Ptr <Procnetdev_Parser> parser_;
#endif
};

/// Type definition for the software probe's factory
typedef ::OASIS::Software_Probe_Factory_T <SystemNetworkProbe_Impl>
 System_NetworkProbe_Impl_Factory;

/// Export the interface for the software probe factory.
OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_DECL (NETWORKPROBE_IMPL_Export,
                                          create_OASIS_System_Network_NetworkProbe_Impl_Factory);
}
}
}
#endif  // !defined _NETWORKPROBE_IMPL_H_
