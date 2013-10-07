// -*- C++ -*-

//=============================================================================
/**
 * @file        Console_Printer_Tool.h
 *
 * $Id: Console_Printer_Tool.h 2071 2011-12-01 15:48:16Z hillj $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_CONSOLE_PRINTER_TOOL_H_
#define _OASIS_CONSOLE_PRINTER_TOOL_H_

#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"
#include "ace/UUID.h"

#include "oasis/middleware/tao/Servant_Manager_T.h"
#include "oasis/DataAcquisitionController/DataAcquisitionControllerC.h"
#include "Console_Printer_DataSubscriber_i.h"

namespace OASIS
{

/**
 * @class Console_Printer_Tool
 *
 * Main entry point class for the console printer tool.
 */
class Console_Printer_Tool
{
public:
  /// Default constructor.
  Console_Printer_Tool (void);

  /// Destructor.
  ~Console_Printer_Tool (void);

  /// Main entry point for the class.
  int run_main (int argc, char * argv []);

  /// Shutdown the subscriber application.
  void shutdown (void);

private:
  /// Helper method that parse command-line arguments.
  int parse_args (int argc, char * argv []);

  /// Helper method that runs the server.
  int run_server (void);

  /**
   * Register the subscriber with the publisher service.
   *
   * @param[in]         handle        Handle to publisher service
   */
  int register_subscriber (DataAcquisitionController_ptr the_DAC);

  /// The ORB for the application.
  CORBA::ORB_var orb_;

  Console_Printer_DataSubscriber_i subscriber_impl_;

  Servant_Manager_T <Console_Printer_DataSubscriber_i> servant_;

  PublisherService_var pulisher_service_;

  /// Target software probe of interest.
  ACE_Utils::UUID probe_;

  /// Name of the DAC.
  ACE_CString dac_name_;
};

}

#endif  // !defined _OASIS_CONSOLE_PRINTER_TOOL_H_
