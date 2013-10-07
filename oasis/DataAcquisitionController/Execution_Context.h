// -*- C++ -*-

//=============================================================================
/**
 *  @file       Context.h
 *
 *  $Id: Execution_Context.h 2140 2012-03-23 16:51:45Z dfeiock $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DAC_CONTEXT_H_
#define _OASIS_DAC_CONTEXT_H_


#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"
#include "ace/SString.h"
#include "ace/Thread_Mutex.h"

#include "Configuration.h"
#include "Database.h"

namespace OASIS
{
namespace DAC
{

// Forward decl.
class Data_Packet;

// Forward decl.
struct Registration_Packet;

// Forward decl.
class Command_Channel;

// Forward decl.
class Data_Handler;

// Forward decl.
class Data_Channel;

/**
 * @class Execution_Context
 *
 * The main context for the DAC. The context is shared by the DAC
 * application, and all its loaded services. The execution context
 * is a Singleon and can only be created and destroyed by the
 * ACE_Singleton class.
 */
class OASIS_DAC_CORE_Export Execution_Context
{
  // Friend decl.
  template <typename T, typename LOCK>
  friend class ACE_Singleton;

public:
  /// Default constructor.
  Execution_Context (void);

  /// Destructor.
  ~Execution_Context (void);

  /// Set the name of the execution context.
  void name (const ACE_CString & n);

  /// Get the name of the execution context.
  const ACE_CString & name (void);

  /// Get a reference to the execution context's database.
  Database & get_database (void);

  /**
   * @overloaded
   */
  const Database & get_database (void) const;

  typedef
    ACE_Hash_Map_Manager <ACE_CString,
                          Data_Handler *,
                          ACE_Thread_Mutex> Data_Handler_Manager;
  typedef
    ACE_Hash_Map_Manager <ACE_CString,
                          Data_Channel *,
                          ACE_Thread_Mutex> Data_Channel_Manager;

  /**
   * Load a new data handler.
   *
   * @param[in]       directive         ACE_Service_Config directive
   */
  int load_data_handler (const DAC_Service_Configuration::Directive & directive);

  /**
   * Load a new data channel.
   *
   * @param[in]       directive         ACE_Service_Config directive
   */
  int load_data_channel (const char * directive);

  /// Activate the execution context.
  int activate (void);

  /// Deactivate the execution context.
  int deactivate (void);

  /// Handle a new data packet. This method notifies all loaded
  /// data handlers of the new data packet.
  int handle_data (const Data_Packet & packet);

  /// Handle a new registration packet. This method notifies all loaded
  /// data handlers of the new registration packet.
  int handle_registration (const Registration_Packet & packet);

  // Handle an unregistration of an einode.
  int handle_unregister_einode (const ACE_Utils::UUID & uuid);

  /**
   * Handle a new command
   *
   * @param[in]         einode          Target EINode
   * @param[in]         command         Command to send to EINode
   */
  int handle_command (const ACE_CString & einode, const ACE_CString & command);

  /// Get the list of data handlers.
  const Data_Handler_Manager & get_data_handlers (void) const;

private:
  /// Name of the execution context.
  ACE_CString name_;

  /// The single database of the context.
  Database database_;

  /// Collection of loaded handlers.
  Data_Handler_Manager handlers_;

  /// Collection of loaded channels.
  Data_Channel_Manager channels_;

  /// Type definition of the command channel managar.
  typedef
    ACE_Hash_Map_Manager <ACE_CString,
                          Command_Channel *,
                          ACE_Thread_Mutex> Command_Channel_Manager;

  /// Collection of command channel.
  Command_Channel_Manager cmd_channels_;
};

/// Type definition of the global execution context.
typedef ACE_Singleton <Execution_Context, ACE_Null_Mutex> EXECUTION_CONTEXT;

OASIS_DAC_CORE_SINGLETON_DECLARE (ACE_Singleton,
                                  Execution_Context,
                                  ACE_Null_Mutex);

}
}

#if defined (__OASIS_INLINE__)
#include "Execution_Context.inl"
#endif

#endif  // !defined _OASIS_DAC_CONTEXT_H_
