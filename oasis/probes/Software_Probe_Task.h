// -*- C++ -*-

//=============================================================================
/**
 * @file        Software_Probe_Task.h
 *
 * $Id: Software_Probe_Task.h 1756 2011-02-21 05:33:37Z hillj $
 *
 * @author      Harold Owens II
 */
//=============================================================================

#ifndef _SOFTWARE_PROBE_TASK_H_
#define _SOFTWARE_PROBE_TASK_H_

#include "ace/Task.h"
#include "SoftwareProbe_Core_export.h"

namespace OASIS
{
// Forward decl.
class Software_Probe_Impl;

/**
 * @class Software_Probe_Task
 *
 * The default task (or active object) for all software probes.
 */
class OASIS_SOFTWAREPROBE_CORE_Export Software_Probe_Task :
  protected ACE_Task_Base
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       probe       The host probe.
   */
  Software_Probe_Task (Software_Probe_Impl * probe);

  /// Destructor.
  virtual ~Software_Probe_Task (void);

  /**
   * Activate the task.
   *
   * @param[in]       interval          Timeout interval
   */
  int activate (const ACE_Time_Value & interval);

  /**
   * Reschedule the timeout for the task.
   *
   * @param[in]       interval          New timeout interval
   */
  int reschedule (const ACE_Time_Value & interval);

  /// Deactive the task.
  int deactivate (void);

  /// Service handler routine.
  virtual int svc (void);

  /**
   * Handle the timeout notification.
   *
   * @param[in]       current           The current timeout value
   * @param[in]       act               Action to execute
   */
  virtual int handle_timeout (const ACE_Time_Value & current, const void * act);

private:
  /// Pointer to the target system software probe
  Software_Probe_Impl * probe_;

  /// The task is active.
  bool is_active_;

  /// Timer id for this task.
  long timer_id_;
};

}

#endif  // !defined _SOFTWARE_PROBE_TASK_H_
