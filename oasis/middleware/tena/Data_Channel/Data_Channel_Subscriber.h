// -*- C++ -*-

//=============================================================================
/**
 *  @file       Data_Channel_Subscriber.h
 *
 *  $Id: Data_Channel_Subscriber.h 1964 2011-10-03 02:59:33Z hillj $
 *
 *  @author     Harold Owens II
 */
//=============================================================================

#ifndef _OASIS_TENA_DATA_CHANNEL_SUBSCRIBER_H_
#define _OASIS_TENA_DATA_CHANNEL_SUBSCRIBER_H_

#include "OASIS/Middleware/DataChannel.h"
#include "OASIS/Middleware/RegistrationChannel.h"

#include "oasis/DataAcquisitionController/Data_Channel.h"
#include "oasis/middleware/tena/Subscriber_Task.h"

#include "Configuration.h"

#include "Data_Channel_Subscriber_export.h"

namespace OASIS
{
class Einode_Observer;

/**
 * @class Tena_Data_Channel_Subscriber
 *
 * Implementation of the standard DAC's data channel.
 */
class Tena_Data_Channel_Subscriber : public DAC::Data_Channel
{
public:
  /// Constructor.
  Tena_Data_Channel_Subscriber (void);

  /// Destructor.
  virtual ~Tena_Data_Channel_Subscriber (void);

  /// Initialize the object.
  virtual int init (int argc, ACE_TCHAR * argv []);

  /// Finalize the object.
  virtual int fini (void);

  /// Handle deactivation of the handler.
  virtual int handle_deactivate (void);

  /// Get listing of interested channels.
  const std::set <std::string> & channel_names (void) const;

  /// Get the registration channel subscription pointer.
  Middleware::RegistrationChannel::SubscriptionPtr
    get_registration_subscription (void) const;

  /// Get the data channel subscription pointer.
  Middleware::DataChannel::SubscriptionPtr
    get_data_subscription (void) const;

private:
  /// TENA middleware runtime
  TENA::Middleware::RuntimePtr runtime_;

  /// TENA middleware execution
  TENA::Middleware::ExecutionPtr execution_;

  /// TENA middleware session
  TENA::Middleware::SessionPtr session_;

  /// The task for the TENA middleware.
  Tena_Subscriber_Task task_;

  /// TENA subscription to data channel
  Middleware::DataChannel::SubscriptionPtr data_subscription_;
  Middleware::RegistrationChannel::SubscriptionPtr registration_subscription_;

  /// The one and only observer for the channel.
  std::auto_ptr <Einode_Observer> observer_;

  /// The application's configuration.
  Configuration config_;

  /// List of names for channelss to subscribe to.
  std::set <std::string> channel_names_;
};
}

ACE_FACTORY_DECLARE (OASIS_TENA_DATACHANNEL_SUBSCRIBER, OASIS_Tena_Data_Channel_Subscriber)

#endif  // !defined _OASIS_STANDARD_DAC_DATACHANNEL_I_H_
