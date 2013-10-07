// -*- C++ -*-

//=============================================================================
/**
 *  @file       Software_Probe_Test_Task.h
 *
 *  $Id: Software_Probe_Test_Task.h 1858 2011-08-18 03:13:41Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_SOFTWARE_PROBE_TEST_TASK_H_
#define _OASIS_SOFTWARE_PROBE_TEST_TASK_H_

#include "ace/Task.h"

#include "Software_Probe_Test_export.h"

namespace OASIS
{
// Forward decl.
class Software_Probe_Impl;

/**
 * Test task that is responsible for setting the probe's values
 * and flushing it. This will cause the test data channel to receive
 * the software probe's latest data, in package format.
 */
class OASIS_SOFTWARE_PROBE_TEST_Export Software_Probe_Test_Task :
  public ACE_Task_Base
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]         probe         Target software probe.
   */
  Software_Probe_Test_Task (Software_Probe_Impl & probe);

  /// Destructor.
  virtual ~Software_Probe_Test_Task (void);

  /// Service handler routine.
  virtual int svc (void);

private:
  /// The target software probe.
  OASIS::Software_Probe_Impl & probe_;
};

}

#endif
