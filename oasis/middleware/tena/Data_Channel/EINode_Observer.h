// -*- C++ -*-

//=============================================================================
/**
 *  @file       Data_Channel_Subscriber.h
 *
 *  $Id: EINode_Observer.h 1964 2011-10-03 02:59:33Z hillj $
 *
 *  @author     Harold Owens II
 */
//=============================================================================

#ifndef _OASIS_TENA_REGISTRATION_CHANNEL_OBSERVER_H_
#define _OASIS_TENA_REGISTRATION_CHANNEL_OBSERVER_H_

#include "OASIS/Middleware/RegistrationChannel.h"
#include "OASIS/Middleware/DataChannel.h"

namespace OASIS
{
/// Forward decl.
class Tena_Data_Channel_Subscriber;

/**
 * @class Tena_Data_Channel_Observer
 *
 * Implementation of the observer for the TENA data channel. It only
 * listens for events from specific channels.
 */
class Einode_Observer :
  public OASIS::Middleware::RegistrationChannel::AbstractObserver,
  public OASIS::Middleware::DataChannel::AbstractObserver
{
public:
  /// Default constructor.
  Einode_Observer (Tena_Data_Channel_Subscriber & parent);

  /// Destructor.
  virtual ~Einode_Observer (void);

  virtual void
    discoveryEvent (OASIS::Middleware::RegistrationChannel::ProxyPtr const & pProxy,
                    OASIS::Middleware::RegistrationChannel::PublicationStatePtr const & pPubState);

  virtual void
    discoveryEvent (OASIS::Middleware::DataChannel::ProxyPtr const & pProxy,
                    OASIS::Middleware::DataChannel::PublicationStatePtr const & pPubState);

  virtual void
    stateChangeEvent (OASIS::Middleware::RegistrationChannel::ProxyPtr const & pProxy,
                      OASIS::Middleware::RegistrationChannel::PublicationStatePtr const & pPubState);

  virtual void
    stateChangeEvent (OASIS::Middleware::DataChannel::ProxyPtr const & pProxy,
                      OASIS::Middleware::DataChannel::PublicationStatePtr const & pPubState);

private:
  void handle_registration (const OASIS::Middleware::RegistrationChannel::PublicationStatePtr & state);
  void handle_data (const OASIS::Middleware::DataChannel::PublicationStatePtr & state);

  /// Callback for received messages.
  Tena_Data_Channel_Subscriber & parent_;
};

}

#endif  // !defined _OASIS_TENA_DATA_CHANNEL_OBSERVER_H_
