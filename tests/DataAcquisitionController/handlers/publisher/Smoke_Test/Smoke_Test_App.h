// -*- C++ -*-

//=============================================================================
/**
 *  @file       Smoke_Test_App.h
 *
 *  $Id: Smoke_Test_App.h 1894 2011-09-04 23:12:45Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DAC_PUBLISHER_SERVICE_SMOKE_TEST_APP_H_
#define _OASIS_DAC_PUBLISHER_SERVICE_SMOKE_TEST_APP_H_

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
};

#endif  // !defined _OASIS_DAC_PUBLISHER_SERVICE_SMOKE_TEST_APP_H_
