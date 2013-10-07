// $Id: Command_Injector_App.h 1971 2011-10-03 20:07:30Z hillj $

//=============================================================================
/**
 *  @file         Command_Injector_App.h
 *
 *  $Id: Command_Injector_App.h 1971 2011-10-03 20:07:30Z hillj $
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _OASIS_COMMAND_INJECTOR_APP_H_
#define _OASIS_COMMAND_INJECTOR_APP_H_

#include <string>
#include <vector>

#include "tao/corba.h"
#include "oasis/TestExecutionManager/TestExecutionManagerC.h"

namespace OASIS
{

/**
 * @class Command_Injector_App
 *
 * Wrapper class for the main application.
 */
class Command_Injector_App
{
public:
  /// Default constructor.
  Command_Injector_App (void);

  /// Destructor.
  ~Command_Injector_App (void);

  /**
   * Run the main application.
   *
   * @param[in]       argc        Number of command-line arguments
   * @param[in]       argv        The command-line arguments
   */
  int run_main (int argc, char * argv []);

  /// Shutdown the application.
  void shutdown (void);

private:
  /// Parse the command-line options.
  int parse_args (int argc, char * argv []);

  /// Print the help screen.
  void print_help (void);

  /// Execute a single command.
  int execute_command (TestExecutionManager_ptr, const std::string & command);

  /// CORBA ORB for the application.
  ::CORBA::ORB_var orb_;

  /// List of commands to execute.
  std::vector <std::string> commands_;
};

}

#endif  // !defined _OASIS_COMMAND_INJECTOR_APP_H_
