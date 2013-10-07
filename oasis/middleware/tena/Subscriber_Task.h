// -*- C++ -*-

//=============================================================================
/**
 * @file        Tena_Subscriber_Task.h
 *
 * $Id: Subscriber_Task.h 1862 2011-08-19 17:07:25Z hillj $
 *
 * @author      Harold Owens II
 */
//=============================================================================

#ifndef _OASIS_TENA_SUBSCRIBER_TASK_H_
#define _OASIS_TENA_SUBSCRIBER_TASK_H_

#include "TENA/Middleware/SessionPtr.h"

#include "ace/Task.h"
#include "oasis/config.h"

#include "Tena_export.h"

namespace OASIS
{

/**
 * @class Tena_Subscriber_Task
 *
 * Helper object for running multiple TENA threads in a server.
 */
class OASIS_TENA_Export Tena_Subscriber_Task :
  public ACE_Task_Base
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]         session         The target session.
   */
  Tena_Subscriber_Task (TENA::Middleware::SessionPtr session);

  /// Default Construtor
  Tena_Subscriber_Task (void);

  /// Destructor.
  virtual ~Tena_Subscriber_Task (void);

  /**
   * Initialize the ORB for the task.
   *
   * @param[in]         session         The targret session.
   */
  int reset (::TENA::Middleware::SessionPtr session = TENA::Middleware::SessionPtr ());

  /**
   * Service routine for the task. If you do not want to spawn mutiple
   * SESSION threads, then you can invoke this method directly. If will run
   * the SESSION's main event loop using the current thread.
   */
  virtual int svc (void);

private:
  /// Target TENA middleware session controlled by this task
  ::TENA::Middleware::SessionPtr session_;
};

}

#if defined (__OASIS_INLINE__)
#include "Subscriber_Task.inl"
#endif

#endif  // !defined _OASIS_TENA_SERVER_TASK_H_
