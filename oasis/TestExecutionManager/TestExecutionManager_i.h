// -*- C++ -*-

//=============================================================================
/**
 *  @file       TestExecutionManager_i.h
 *
 *  $Id: TestExecutionManager_i.h 2188 2012-05-31 14:23:54Z dfeiock $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TESTEXECUTIONMANAGER_I_H_
#define _OASIS_TESTEXECUTIONMANAGER_I_H_

#include "TestExecutionManagerS.h"

namespace OASIS
{
// Forward decl.
class TestExecutionManager_App;

/**
 * @class TestExecutionManager_i
 *
 * Main entry point class for the application.
 */
class TestExecutionManager_i : public POA_OASIS::TestExecutionManager
{
public:
  /// Default constructor.
  TestExecutionManager_i (TestExecutionManager_App & app);

  /// Destructor.
  virtual ~TestExecutionManager_i (void);

  /// Get the collection of DACs known by the test and execution
  /// manager object.
  virtual DataAcquisitionControllerSeq * get_DACs (void);

  /// Get a specific DAC
  virtual DataAcquisitionController_ptr get_DAC (const char * name);

  // Get the name
  virtual char* name (void);

  // Register a DAC
  virtual void register_DAC (DataAcquisitionController_ptr the_DAC);

  // Unregister a DAC
  virtual void unregister_DAC (DataAcquisitionController_ptr the_DAC);

private:
  /// Reference to the parent application.
  TestExecutionManager_App & app_;

  /// The listing of DACs.
  typedef
    ACE_Hash_Map_Manager <ACE_CString,
                          DataAcquisitionController_var,
                          ACE_Thread_Mutex> DAC_List_Manager;

  DAC_List_Manager dac_list_;
};

}

#endif  // !define _OASIS_TESTEXECUTIONMANAGER_APP_H_
