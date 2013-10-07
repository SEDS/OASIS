// -*- C++ -*-

//=============================================================================
/**
 *  @file       Manager_App.h
 *
 *  $Id: Manager_App.h 2187 2012-05-30 17:28:06Z dfeiock $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TESTEXECUTIONMANAGER_APP_H_
#define _OASIS_TESTEXECUTIONMANAGER_APP_H_

#include "TestExecutionManager_i.h"

#include "oasis/middleware/tao/IOR_File_Trait.h"
#include "oasis/middleware/tao/IOR_Table_Trait.h"
#include "oasis/middleware/tao/Servant_Manager_T.h"
#include "oasis/middleware/tao/Servant_Traits_T.h"

namespace OASIS
{

/**
 * @class TestExecutionManager_App
 *
 * Main entry point class for the application.
 */
class TestExecutionManager_App
{
public:
  /// Default constructor.
  TestExecutionManager_App (void);

  /// Destructor.
  ~TestExecutionManager_App (void);

  /**
   * Run the main application
   *
   * @param[in]         argc          Number of command-line arguments
   * @param[in]         argv          The command-line arguments
   */
  int run_main (int argc, char * argv []);

    /// Shutdown the application.
  void shutdown (void);

  /// Destroy the application.
  void destroy (void);

  // Get the name
  const ACE_CString & name (void) const;

private:
  /// Parse the command-line arguments.
  int parse_args (int argc, char * argv []);

  /// The application's ORB.
  CORBA::ORB_var orb_;

  /// The RootPOA for the application.
  ::PortableServer::POA_var root_poa_;

  /// Type definition of the servant's traits.
  typedef Servant_Trait_T <IOR_File_Trait,
          Servant_Trait_T <IOR_Table_Trait> > servant_traits_t;

  /// The DAC's servant.
  Servant_Manager_Ex_T <TestExecutionManager_i, servant_traits_t> servant_;

  /// The name of this object.
  ACE_CString name_;
};

}

#endif  // !define _OASIS_TESTEXECUTIONMANAGER_APP_H_
