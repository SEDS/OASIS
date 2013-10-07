// -*- C++ -*-

//=============================================================================
/**
 *  @file       Smoke_Test_App.h
 *
 *  $Id: Smoke_Test_App.h 2190 2012-05-31 18:13:59Z dfeiock $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TESTEXECUTIONMANAGER_SMOKE_TEST_APP_H_
#define _OASIS_TESTEXECUTIONMANAGER_SMOKE_TEST_APP_H_

#include "tao/corba.h"

/**
 * @class Smoke_Test_App
 *
 * Main entry point class for the smoke test.
 */
class Smoke_Test_App
{
public:
  /// Default constructor.
  Smoke_Test_App (void);

  /// Destructor.
  ~Smoke_Test_App (void);

  /// Main entry point for the class.
  int run_main (int argc, char * argv []);

private:
  /// Helper method that parse command-line arguments.
  int parse_args (int argc, char * argv []);

  /// The ORB for the application.
  CORBA::ORB_var orb_;

  /// The expected number of DACs
  int expected_value_;
};

#endif  // !defined _OASIS_TESTEXECUTIONMANAGER_SMOKE_TEST_APP_H_
