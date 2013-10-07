// -*- C++ -*-

//=============================================================================
/**
 *  @file       Smoke_Test_Subscriber.h
 *
 *  $Id: Smoke_Test_Subscriber.h 2071 2011-12-01 15:48:16Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_SMOKE_TEST_SUBSCRIBER_H_
#define _OASIS_SMOKE_TEST_SUBSCRIBER_H_

#include "oasis/middleware/tao/Servant_Manager_T.h"
#include "oasis/DataAcquisitionController/DataAcquisitionControllerC.h"
#include "Simple_Data_Subscriber.h"

/**
 * @class Smoke_Test_Subscriber
 *
 * Main entry point class for the smoke test.
 */
class Smoke_Test_Subscriber
{
public:
  /// Default constructor.
  Smoke_Test_Subscriber (void);

  /// Destructor.
  ~Smoke_Test_Subscriber (void);

  /// Main entry point for the class.
  int run_main (int argc, char * argv []);

  /// Shutdown the subscriber application.
  void shutdown (void);

private:
  /// Helper method that parse command-line arguments.
  int parse_args (int argc, char * argv []);

  /// Helper method that runs the server.
  int run_server (OASIS::PublisherService_ptr publisher);

  /// The ORB for the application.
  ::CORBA::ORB_var orb_;

  Simple_Data_Subscriber subscriber_impl_;

  OASIS::Servant_Manager_T <Simple_Data_Subscriber> servant_;

  /// The publisher for from the DAC.
  OASIS::PublisherService_var publisher_;
};

#endif  // !defined _OASIS_SMOKE_TEST_SUBSCRIBER_H_
