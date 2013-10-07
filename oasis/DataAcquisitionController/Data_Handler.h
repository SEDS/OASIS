// -*- C++ -*-

//=============================================================================
/**
 *  @file       Data_Handler.h
 *
 *  $Id: Data_Handler.h 2152 2012-04-16 20:13:33Z dpuranik $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DAC_DATA_HANDLER_H_
#define _OASIS_DAC_DATA_HANDLER_H_

#include "oasis/config.h"

#if defined (OASIS_HAS_TAO_DAC_SERVANT)
#include "Remote_ServiceC.h"
#endif

#include "Data_Handler_export.h"

namespace OASIS
{
namespace DAC
{
// Forward decl.
class Data_Packet;

// Forward decl.
struct Registration_Packet;

// Forward decl.
struct Unregistration_Packet;

/**
 * @class Data_Handler
 *
 * Interface for handlers to operate on date received by the DAC.
 */
class OASIS_DAC_DATA_HANDLER_Export Data_Handler
{
public:
  /// Default constructor.
  Data_Handler (void);

  /// Destructor.
  virtual ~Data_Handler (void);

  /**
   * Initialize the data handler. This method is passed a set of command-line
   * arguments, which are specified at in the configuration file. Unlike the
   * command-line passed to main (), the first argument should not be skipped.
   *
   * @param[in]         argc       Number of command-line arguments
   * @param[in]         argv       The command-line arguments
   */
  virtual int init (int argc, char * argv []);

  /// Finalize the data handler. This is called right before
  /// the object is destroyed.
  virtual int fini (void);

  /// This method is called when the data handler is being destroyed.
  virtual void destroy (void);

  /// Callback for activating the data handler.
  virtual int handle_activate (void);

  /// Callback for deactivating the data handler.
  virtual int handle_deactivate (void);

  /// Callback for handling new data packet.
  virtual int handle_data (const Data_Packet & packet);

  /// Callback for handling new registration data.
  virtual int handle_registration (const Registration_Packet & packet);

  /// Callback for handling the destruction of einodes/probes.
  virtual int handle_unregister_einode (const Unregistration_Packet & packet);

#if defined (OASIS_HAS_TAO_DAC_SERVANT)
  /// Test if the service has a remote service capabilities.
  virtual ::OASIS::RemoteService_ptr get_remote_service (void);
#endif

};

}
}

#define OASIS_DAC_DATA_HANDLER_DECL(EXPORT, SYMBOL) \
  extern "C" EXPORT##_Export ::OASIS::DAC::Data_Handler * SYMBOL (void)

#define OASIS_DAC_DATA_HANDLER_IMPL(SYMBOL, HANDLER) \
  ::OASIS::DAC::Data_Handler * SYMBOL (void) { \
    ::OASIS::DAC::Data_Handler * handler = 0; \
    ACE_NEW_RETURN (handler, HANDLER (), 0); \
    return handler; \
  }

#if defined (__OASIS_INLINE__)
#include "Data_Handler.inl"
#endif

#endif  // !defined _OASIS_DAC_DATA_HANDLER_H_
