// -*- C++ -*-

//==============================================================================
/**
 *  @file        SwitchProbe_Impl.h
 *
 *  $Id: SwitchProbe_Impl.h 2232 2013-01-28 16:07:41Z dfeiock $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_NETWORK_SWITCH_SWITCHPROBE_IMPL_H_
#define _OASIS_NETWORK_SWITCH_SWITCHPROBE_IMPL_H_

#include "SwitchProbe_Impl_export.h"
#include "SwitchProbeImpl.h"
#include "oasis/probes/Software_Probe_Factory_T.h"
#include "Snmp_Wrapper.h"

namespace OASIS
{
namespace Network
{
namespace Switch
{

/**
 * @class SwitchProbe_Impl
 *
 * Probe implementation for gather switch performance metrics.
 * Requires net-snmp.
 */
class SWITCHPROBE_IMPL_Export SwitchProbe_Impl :
  public SwitchProbeImpl
{
public:
  /// Default constructor.
  SwitchProbe_Impl (void);

  /// Destructor.
  virtual ~SwitchProbe_Impl (void);

  /// Collect a new set of data
  virtual int handle_collect_data (void);

  /// Initalize the software probe
  virtual int init (const char * params, const char * name = 0);

protected:
  /// Helper for parsing command-line arguments
  int parse_args (const char * args);

  /// Helper method for processing port data
  void process_port (std::vector <OID> & oids);

  /// Object for snmp functionality
  Snmp_Wrapper snmp_;

  /// OID for uptime
  OID uptime_oid_;

  /// OID for cpu load
  OID cpu_oid_;

  /// OID for memory usage
  OID memory_usage_oid_;

  /// OID for total memory
  OID total_memory_oid_;

  /// OIDs for ports
  std::vector < std::vector <OID> > port_oids_;

  /// Base OID strings for each monitored port;
  std::vector <ACE_CString> base_port_oids_;

  /// Host to connect to
  ACE_CString host_;

  /// Community string
  ACE_CString community_;

  /// Ports to monitor
  std::vector <ACE_CString> port_args_;
};

/// Type definition for the software probe's factory
typedef ::OASIS::Software_Probe_Factory_T <SwitchProbe_Impl>
 SwitchProbe_Impl_Factory;

/// Export the interface for the software probe factory.
OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_DECL (SWITCHPROBE_IMPL_Export,
                                          create_OASIS_Network_Switch_SwitchProbe_Impl_Factory);

} // namespace OASIS
} // namespace Network
} // namespace Switch

#if defined (__OASIS_INLINE__)
#include "SwitchProbe_Impl.inl"
#endif  // !defined __OASIS_INLINE__

#endif  // _OASIS_NETWORK_SWITCH_SWITCHPROBE_IMPL_H_
