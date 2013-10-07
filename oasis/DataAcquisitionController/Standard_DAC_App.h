// -*- C++ -*-

//=============================================================================
/**
 *  @file       Standard_DAC_App.h
 *
 *  $Id: Standard_DAC_App.h 2188 2012-05-31 14:23:54Z dfeiock $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_STANDARD_DAC_APP_H_
#define _OASIS_STANDARD_DAC_APP_H_

#include "ace/Condition_T.h"
#include "ace/SString.h"
#include "ace/Thread_Mutex.h"

#include "Configuration.h"
#include "Execution_Context.h"

#if defined (OASIS_HAS_TAO_DAC_SERVANT)
#include "DataAcquisitionController_i.h"

#include "oasis/middleware/tao/IOR_File_Trait.h"
#include "oasis/middleware/tao/IOR_Table_Trait.h"
#include "oasis/middleware/tao/ORB_Server_Task.h"
#include "oasis/middleware/tao/Servant_Traits_T.h"
#include "oasis/middleware/tao/Servant_Manager_T.h"
#endif

namespace OASIS
{

/**
 * @class Standard_DAC_App
 *
 * Implementation of the DAC application.
 */
class Standard_DAC_App
{
public:
  /// Default constructor.
  Standard_DAC_App (void);

  /// Destructor.
  ~Standard_DAC_App (void);

  /// Main entry point for the application class.
  int run_main (int argc, char * argv []);

  /// Shutdown the application.
  void shutdown (void);

  /// Get the application's name.
  const ACE_CString & name (void) const;

private:
  /// Helper method to parse command-line arguments.
  int parse_args (int argc, char * argv []);

  /// Helper method to initialize the services.
  int initialize_services (void);

  /// Helper method that enables the logging levels
  void enable_log_level (int level);

  /// Print the help message. This method does not return.
  void print_help (void);

  /// Connection string for the database.
  ACE_CString connstr_;

  /// The service configuration for the DAC.
  DAC_Service_Configuration svc_config_;

  /// Lock for the exit condition.
  ACE_Thread_Mutex lock_;

  /// Exit condition guard.
  ACE_Condition <ACE_Thread_Mutex> exit_;

#if defined (OASIS_HAS_TAO_DAC_SERVANT)
  CORBA::ORB_var orb_;

  /// The actual servant.
  DataAcquisitionController_i servant_impl_;

  /// Type definition of the servant traits.
  typedef
    Servant_Trait_T <IOR_File_Trait,
    Servant_Trait_T <IOR_Table_Trait> >
    servant_traits_t;

  /// The servant manager for the servant.
  Servant_Manager_Ex_T <DataAcquisitionController_i, servant_traits_t> servant_;

  ORB_Server_Task orb_task_;

  // Helper method to register the DAC with the TEM
  void register_with_TEM (void);

  // Helper method to unregister the DAC with the TEM
  void unregister_with_TEM (void);
#endif
};

}

#if defined (__OASIS_INLINE__)
#include "Standard_DAC_App.inl"
#endif

#endif  // !defined _OASIS_STANDARD_DAC_APP_H_
