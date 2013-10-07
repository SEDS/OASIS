// -*- C++ -*-

//=============================================================================
/**
 * @file        Exceptions.h
 *
 * $Id: EINode_Connect_Task.h 2085 2011-12-31 07:49:04Z hillj $
 *
 * @author      Dennis C. Feiock <dfeiock@iupui.edu>
 */
//=============================================================================

#ifndef _STANDARD_EINODE_CONNECT_TASK_H_
#define _STANDARD_EINODE_CONNECT_TASK_H_

#include "ace/Task.h"

namespace OASIS
{

// Forward decl.
class Data_Channel;

// Forward decl.
class Standard_EINode;

/**
 * @class EINode_Connect_Task
 *
 * Task (or active object) for connecting a data channel to its
 * remote servant.  This will retry if the connection fails. When
 * the connection is established, it deactivates itself.
 */
class EINode_Connect_Task : public ACE_Task_Base
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       Standard_EINode   The host EINode
   */
  EINode_Connect_Task (Standard_EINode * einode);

  /// Destructor.
  virtual ~EINode_Connect_Task (void);

  /**
   * Set the data channel to reconnect.
   *
   * @param[in]       channel           Target Data_Channel
   */
  void set_data_channel (Data_Channel * channel);

  /**
   * Activate the task.
   *
   * @parm[in]        interval          Timeout interval
   */
  int activate (const ACE_Time_Value & interval);

  /**
   * Reschedule the timeout for the task.
   *
   * @param[in]       interval          New timeout interval
   */
  int reschedule (const ACE_Time_Value & interval);

  /// Deactivate the task.
  int deactivate (void);

  /// Service handler routine.
  virtual int svc (void);

  /**
   * Handle the timeout notification
   *
   * @param[in]       current           The current timeout value
   * @param[in]       act               Action to execute
   */
  virtual int handle_timeout (const ACE_Time_Value & current, const void * act);

protected:
  /// Pointer to the target EINode
  Standard_EINode * einode_;

  /// Pointer to the target Data_Channel
  Data_Channel * channel_;

  /// The task is active.
  bool is_active_;

  /// Timer id for this task.
  long timer_id_;
};

}

#endif // !defined _EINODE_CONNECT_TASK_H_
