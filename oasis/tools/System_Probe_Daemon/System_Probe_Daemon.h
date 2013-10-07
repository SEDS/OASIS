// $Id:

#ifndef _SYSTEM_PROBE_DAEMON_H_
#define _SYSTEM_PROBE_DAEMON_H_

// Signal handlers
#include "ace/Condition_T.h"
#include "ace/Thread_Mutex.h"
#include "ace/SString.h"
#include <iostream>

#include "oasis/EINode/Standard_EINode.h"

namespace OASIS
{
namespace System
{

class System_Probe_Daemon
{
public:
  /// Default Constructor
  System_Probe_Daemon (void);

  /// Destructor
  ~System_Probe_Daemon (void);

  /// Shutdown the Daemon
  void shutdown (void);

  /// main
  int run_main (int argc, char * argv []);

private:
  /// Helper for starting the EINode
  int attach_and_run (void);

  /// Helper method to parse command-line arguments.
  int parse_args (int argc, char * argv []);

  /// Helper method that enables the logging levels
  void enable_log_level (int level);

  /// Print the help message.  This method does not return.
  void print_help (void);

  /// Lock for the exit condition.
  ACE_Thread_Mutex lock_;

  /// Exit condition guard.
  ACE_Condition <ACE_Thread_Mutex> exit_;

  /// EINode which this daemon starts
  ::OASIS::Standard_EINode einode_;

  /// Hertz for attached system probes
  ACE_CString hertz_;

  /// List of disabled system probes
  ACE_CString disabled_;

  /// Config file to use for the EINode
  ACE_CString config_file_;

  /// List of system probes to dump
  ACE_CString dump_;
};

}
}

#endif  // !defined _SYSTEM_PROBE_DAEMON_H_
