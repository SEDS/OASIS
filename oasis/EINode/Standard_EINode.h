// -*- C++ -*-

//=============================================================================
/**
 * @file        Standard_EINode.h
 *
 * $Id: Standard_EINode.h 2235 2013-02-06 20:18:09Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_STANDARD_EINODE_H_
#define _OASIS_STANDARD_EINODE_H_

#include "ace/Thread_Mutex.h"
#include "ace/Singleton.h"
#include "ace/Time_Value.h"

#include "Configuration.h"
#include "Data_Channel.h"
#include "EINode_Connect_Task.h"

#include "EINode_Core_export.h"

namespace OASIS
{
// Forward decl.
class Software_Probe_Impl;
class Local_Data_Channel_i;

/**
 * @class Standard_EINode
 *
 * Wrapper class for the standard EINode's implementation.
 */
class OASIS_EINODE_CORE_Export Standard_EINode
{
public:
  /// Friend decl.
  friend class EINode_Connect_Task;

  /// Default constructor.
  Standard_EINode (void);

  /// Destructor.
  ~Standard_EINode (void);

  /// Get the current configuration
  const Einode_Configuration & configuration (void) const;

  /// Get the loaded software probes.
  const SoftwareProbe_Hash_Map & software_probes (void) const;

  /**
   * Initialize the object.
   *
   * @param[in]       argc          Number of command-line arguments
   * @param[in]       argv          The command-line arguments
   * @param[in]       orb_name      Name of the ORB
   */
  int init (int argc, char * argv []);

  /**
   * Activate the EINode. This method will also initialize the
   * EINode with the specified configuration.
   *
   * @param[in]         config        Target configuration.
   */
  int load_configuration (const char * config);

  /// Activate the EINode.
  int activate (void);

  /// Deactivate the EINode.
  int deactivate (void);

  /// Destroy the EINode's resources.
  void destroy (void);

  /**
   * Load the specified software probe.
   *
   * @param[in]       id              The software probe's id.
   * @param[in]       location        Location of the software probe
   * @param[in]       entrypoint      Entry point for software probe
   * @param[in]       params          The probes parameters.
   */
  int load_software_probe (const Einode_Configuration::Software_Probe & probe);

  /**
   * Register a software probe with the EINode. The software probe is
   * considered to be a application-level software probe.
   *
   * @param[in]       probe           The actual software probe.
   */
  int register_probe (Software_Probe_Impl * probe);

  /**
   * Unregister a software probe
   *
   * @param[in]       name            Name of the probe.
   */
  void unregister_probe (const char * name);

  /**
   * Force the EINode to send the specified data to the DAC.
   *
   * @param[in]       instance        Software probe instance
   * @param[in]       data            Data to send
   * @param[in]       length          The data's size
   * @throws          Transient_Error Data failed to send
   */
  void send_data (const char * data, size_t length);

  /**
   * Handle a command. The format of the command is:
   *
   *  PROBE COMMAND_LINE
   *
   * where PROBE is the target probe and COMMAND_LINE is the command-line
   * to pass to the target probe. This method will extract the probe name
   * from the command and then pass the remaining portion of the command
   * to the located software probe.
   *
   * @param[in]         command       Command to pass along.
   * @retval            0             The probe was located
   * @retval            -1            The probe was not located
   */
  int handle_command (const char * command);

private:
  /// Helper method to load the metadata from a configuration.
  void load_metadata (const char * config);

  /// Helper method that performance registration.
  void perform_registration (void);

  /// Helper method to connect the data channel
  int handle_connect (void);

  /// The Einode's configuration.
  Einode_Configuration config_;

  /// Collection of probes in this EINode.
  SoftwareProbe_Hash_Map probes_;

  /// Target data channel for the EINode.
  Data_Channel_Service * channel_;

  /// The local data channel for this node.
  ACE_Auto_Ptr < Local_Data_Channel_i > local_channel_;

  /// The active state of the EINode.
  bool is_active_;

  /// Retry interval for middleware failes
  ACE_Time_Value reconnect_timeout_;

  /// Task for connecting the data channel
  EINode_Connect_Task connect_task_;
};

/// The global single for the application context. This Einode is
/// primarily used by software probes that leverage auto-registration.
typedef ACE_Singleton <Standard_EINode, ACE_Thread_Mutex> GLOBAL_EINODE;

}

OASIS_EINODE_CORE_SINGLETON_DECLARE (ACE_Singleton,
                                     OASIS::Standard_EINode,
                                     ACE_Thread_Mutex);

#if defined (__OASIS_INLINE__)
#include "Standard_EINode.inl"
#endif

#endif  // !defined _OASIS_STANDARD_EINODE_H_
