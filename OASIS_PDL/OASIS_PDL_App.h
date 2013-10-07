// -*- C++ -*-

//=============================================================================
/**
 *  @file       OASIS_PDL_App.h
 *
 *  $Id: OASIS_PDL_App.h 1866 2011-08-22 13:06:27Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_APP_H_
#define _OASIS_PDL_APP_H_

#include <set>
#include <string>

// Forward decl.
class OASIS_PDL_Backend;

/**
 * @class OASIS_PDL_App
 *
 * Wrapper class for the application.
 */
class OASIS_PDL_App
{
public:
  /// Default constructor.
  OASIS_PDL_App (void);

  /// Destructor.
  ~OASIS_PDL_App (void);

  /**
   * Main entry point for the application.
   *
   * @param[in]       argc          Number of command-line arguments
   * @param[in]       argv          The command-line arguments.
   */
  int run_main (int argc, char * argv []);

private:
  /// List the backend generators.
  void list_backends (void);

  // Helper method to process a file.
  int process_file (int argc,
                    char * argv [],
                    const std::string & file,
                    OASIS_PDL_Backend * pdl_backend) const;

  // Helper method to parse command-line arguments.
  int parse_args (int argc, char * argv []);

  /// Get the target backend generator.
  OASIS_PDL_Backend * get_backend (void);

  /// Print a help message. This method does not return.
  void print_help (void);

  /// Target backend generator.
  std::string backend_;

  /// Collection of input files.
  std::set <std::string> input_;

  /// Generate schema definition for inputs.
  bool generate_schema_;

  /// Print the help screen.
  bool print_help_;
};

#endif  // !defined _OASIS_PDL_APP_H_
