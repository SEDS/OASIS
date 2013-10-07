// -*- C++ -*-

#ifndef _OASIS_SOFTWARE_PROBE_IMPL_H_
#define _OASIS_SOFTWARE_PROBE_IMPL_H_

#include "SoftwareProbe_Core_export.h"
#include "oasis/config.h"

#include "oasis/DataChannel/Software_Probe_Data_Packager.h"
#include "Software_Probe_Task.h"
#include "Software_Probe_Metadata.h"
#include "oasis/EINode/Standard_EINode.h"

namespace OASIS
{
/// Forward decl.
class Local_Data_Channel;

/**
 * @class Software_Probe_Impl
 *
 * The base class for all software probe implementations. The implementation
 * an actually an active object. It therefore has methods for initalization
 * and finalization. Moreover, the implementation is connected to an EINode
 * which allows the software probe implementation to flush data. This implies
 * the software stub is not allows to flush information.
 */
class OASIS_SOFTWAREPROBE_CORE_Export Software_Probe_Impl
{
protected:
  /// Default constructor.
  Software_Probe_Impl (void);

  /// Destructor.
  virtual ~Software_Probe_Impl (void);

public:
  /// Get the software probe's instance name.
  const ACE_CString & instance_name (void) const;

  /// Get the software probe's UUID
  const ACE_Utils::UUID & uuid (void) const;

  /// Get the software probe's latest timestamp for the data
  const ACE_Time_Value & timestamp (void) const;

  /// Get the software probe's current sequence number for the data
  const ACE_UINT32 & sequence_number (void) const;

  /// Get the software probe's state for the data
  const ACE_UINT16 & state (void) const;

  /// Get the size of the software probe's data
  const ACE_UINT32 & data_size (void) const;

  /// Dump the contents of the probe to ACE_DEUBG
  virtual void dump (std::ostream & output) const;

  /// Get the software probe's metadata.
  virtual const Software_Probe_Metadata & metadata (void) const = 0;

  /// Set the data channel.
  void set_data_channel (Local_Data_Channel * channel);

  /// Initialize the software probe.
  virtual int init (const char * params, const char * name = 0);

  /// Finalize the software probe.
  virtual int fini (void);

  /// Deactivate the probe
  virtual int deactivate (void);

  /// Activate the probe
  virtual int activate (void);

  /// Handle command from outside world.
  virtual void handle_command (const char * command);

  /// Getter for interval which the probe flushes at
  const ACE_Time_Value & flush_interval (void) const;

  /// Setter for the interval which the probe flushes at
  void flush_interval (const ACE_Time_Value & interval);

  /// Returns true if the probe automatically publishes data
  bool is_active_object (void) const;

  /// Getter for the initialization state
  bool is_initalized (void);

  /**
   * @name Data Collection Methods
   */
  ///@{
  /// Flush the current data to the attached EINode.
  int flush (void);

  /// Handle an event from the software probe's task to collect
  /// a new data sample.
  virtual int handle_collect_data (void);

  ///@}

protected:
  /// UUID of the probe
  ACE_Utils::UUID uuid_;

  /// The latest timestamp of the probe
  ACE_Time_Value last_ts_;

  /// The current sequence number for the probe
  ACE_UINT32 seqnum_;

  /// The state of the probe
  ACE_UINT16 state_;

  /// The size of the software probe's data
  ACE_UINT32 datasize_;

  /**
   * Package the software probe's data. This method allows the
   * client to manually (re)package the data and the flush ()
   * method to package the data before sending it to an EINode.
   *
   * @param[in]       p             Target data packager.
   */
  virtual int package_data (Software_Probe_Data_Packager * p);

  /// Helper method to parse command-line arguments.
  int parse_args (const char * args);

  /// Helper method that handles the --hertz option.
  int handle_hertz_command (const char * args);

  /// Helper method to set the instance name
  void instance_name (const ACE_CString & name);

  /// Helper method to send packaged data to EINode.
  int send_data (Software_Probe_Data_Packager * p);

  /// Data channel assigned to the software probe. The probe
  /// uses this data channel to send metrics to the EINode.
  Local_Data_Channel * data_channel_;

  /// Task that runs to flush probe state
  Software_Probe_Task task_;

  /// used by task_ for time out
  ACE_Time_Value interval_;

  /// Packager for the software probe implementation.
  Software_Probe_Data_Packager * packager_;

  /// Probe initialization flag
  bool is_init_;

  /// Size of the probe data
  size_t data_size_;

  /// Flag for dumping probe values prior to packaging
  bool dump_;

  /// Instance name of the probe
  ACE_CString name_;
};

}

#if defined (__OASIS_INLINE__)
#include "Software_Probe_Impl.inl"
#endif

#endif  // !defined _OASIS_SOFTWARE_PROBE_IMPL_H_
