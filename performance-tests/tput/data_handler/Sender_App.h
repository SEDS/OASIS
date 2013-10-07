// -*- C++ -*-

#include "data_handlerImpl.h"
#include "oasis/EINode/Standard_EINode.h"
#include "ace/SString.h"
#include <iostream>

class Sender_App
{
public:
  /// Default constructor.
  Sender_App (void);

  /// Destructor.
  ~Sender_App (void);

  // Run the sender
  int run_main (int argc, char * argv []);

  // Stop the sender
  void shutdown (void);

private:
  // Helper for parsing cli arguments
  int parse_args (int argc, char * argv []);

  // Flag for if the sender is running
  bool is_active_;

  // Type of probe to use
  ACE_CString probe_type_;

  // EINode configuration file
  ACE_CString config_file_;

  // Output file
  ACE_CString output_file_;

  // EINode to use for sending
  ::OASIS::Standard_EINode einode_;

  // Run the probe and track throughput
  int run_sender (::OASIS::Software_Probe_Impl * probe);
};
