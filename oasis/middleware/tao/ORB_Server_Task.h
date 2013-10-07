// -*- C++ -*-

//=============================================================================
/**
 * @file        ORB_Server_Task.h
 *
 * $Id: ORB_Server_Task.h 1863 2011-08-19 18:39:59Z hillj $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_ORB_SERVER_TASK_H_
#define _OASIS_ORB_SERVER_TASK_H_

#include "tao/ORB.h"
#include "ace/Task.h"
#include "oasis/config.h"

#include "OASIS_Tao_export.h"

namespace OASIS
{
/**
 * @class ORB_Server_Task
 *
 * Helper object for running multiple ORB threads in a server.
 */
class OASIS_TAO_Export ORB_Server_Task :
  public ACE_Task_Base
{
public:
  /**
   * Initializing constructor.
   */
  ORB_Server_Task (CORBA::ORB_ptr orb = CORBA::ORB::_nil ());

  /// Destructor.
  virtual ~ORB_Server_Task (void);

  /**
   * Initialize the ORB for the task.
   */
  int reset (CORBA::ORB_ptr orb = CORBA::ORB::_nil ());

  /**
   * Service routine for the task. If you do not want to spawn mutiple
   * ORB threads, then you can invoke this method directly. If will run
   * the ORB's main event loop using the current thread.
   */
  virtual int svc (void);

private:
  /// Target ORB controlled by this task.
  ::CORBA::ORB_var orb_;
};

}

#if defined (__OASIS_INLINE__)
#include "ORB_Server_Task.inl"
#endif

#endif  // !defined _OASIS_ORB_SERVER_TASK_H_
