// $Id: Data_Channel_Subscriber.cpp 2095 2012-01-05 15:51:11Z dfeiock $

#include "Data_Channel_Subscriber.h"
#include "Configuration.h"
#include "EINode_Observer.h"

#include <string>

namespace OASIS
{

//
// Tena_Data_Channel_Subscriber
//
Tena_Data_Channel_Subscriber::Tena_Data_Channel_Subscriber (void)
{

}

//
// ~Tena_Data_Channel_Subscriber
//
Tena_Data_Channel_Subscriber::~Tena_Data_Channel_Subscriber (void)
{

}

//
// init
//
int Tena_Data_Channel_Subscriber::init (int argc, ACE_TCHAR * argv [])
{
  try
  {
    // Parse the configuration and initialize the TENA middleware.
    this->config_.parse (argc, argv);
    this->runtime_ = TENA::Middleware::init (this->config_.tenaConfiguration ());

    // Extract the current settings from the configuration.
    std::string channel = this->config_["channelName"].getValue <std::string> ().c_str ();
    TENA::uint32 verbosity = this->config_["verbosity"].getValue <TENA::uint32>();
    bool self_reflection = this->config_["enableSelfReflection"].getValue< bool >();
    bool want_pruning = this->config_["pruneExpiredStateChange"].getValue< bool >();

    TENA::Middleware::CommunicationProperties
      communication_properties = this->config_["bestEffort"].isSet() ?
      TENA::Middleware::BestEffort : TENA::Middleware::Reliable;

    // Extract the endpoint and join the specified TENA execution.
    TENA::Middleware::Endpoint endpoint = this->config_["emEndpoint"].getValue <TENA::Middleware::Endpoint> ();
    this->execution_ = this->runtime_->joinExecution (endpoint);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - joining execution %s\n"),
                endpoint.toString ().c_str ()));

    // Extract the session from the configuration. We are going to
    // use this to determine what session we should join.
    std::string session = this->config_["sessionName"].getValue <std::string> ().c_str ();
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - joining session %s\n"),
                session.c_str ()));

    this->session_ = this->execution_->createSession (session);

    // Create a new data channel subscription pointer. We are then
    // going to subscribe, but we do not allow self-reflection (i.e.,
    // we can't receive our own objects) since it does not make sense
    // in this case.
    this->data_subscription_.reset (new OASIS::Middleware::DataChannel::Subscription ());
    this->registration_subscription_.reset (new OASIS::Middleware::RegistrationChannel::Subscription ());

    // Create the observer and add it to the subscription(s).
    Einode_Observer * observer = new Einode_Observer (*this);
    this->observer_.reset (observer);

    this->registration_subscription_->addObserver (
      OASIS::Middleware::RegistrationChannel::AbstractObserverPtr (observer));

    OASIS::Middleware::RegistrationChannel::subscribe (*this->session_,
                                                       this->registration_subscription_,
                                                       false);

    this->data_subscription_->addObserver (
      OASIS::Middleware::DataChannel::AbstractObserverPtr (observer));

    OASIS::Middleware::DataChannel::subscribe (*this->session_,
                                               this->data_subscription_,
                                               false);

    // We can now start listening for callbacks.
    this->task_.reset (this->session_);
    this->task_.activate ();

    return 0;
  }
  catch (const TENA::Middleware::ConfigurationError & ex)
  {
    std::cerr << "Configuration Error: \n" << ex.what() << std::endl;
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - Configuration Error: %s\n"),
                ex.what ()));
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - Error: Exception raised: %s\n"),
                ex.what ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));
  }

  return -1;
}

//
// handle_deactivate
//
int Tena_Data_Channel_Subscriber::handle_deactivate (void)
{
  try
  {
    // Unsubscribe from the data channel.
    OASIS::Middleware::DataChannel::unsubscribe (*this->session_);

    return 0;
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }

  return -1;
}

//
// fini
//
int Tena_Data_Channel_Subscriber::fini (void)
{
  try
  {
    this->task_.reset ();
    this->task_.wait ();

    if (this->session_.isValid ())
      this->session_.reset ();

    if (this->runtime_.isValid ())
      this->runtime_.reset ();

    return 0;
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what()));
  }

  return -1;
}


//
// channel_names
//
const std::set <std::string> &
Tena_Data_Channel_Subscriber::channel_names (void) const
{
  return this->channel_names_;
}

//
// get_registration_subscription
//
OASIS::Middleware::RegistrationChannel::SubscriptionPtr
Tena_Data_Channel_Subscriber::get_registration_subscription (void) const
{
  return this->registration_subscription_;
}

//
// get_data_subscription
//
OASIS::Middleware::DataChannel::SubscriptionPtr
Tena_Data_Channel_Subscriber::get_data_subscription (void) const
{
  return this->data_subscription_;
}

}

ACE_FACTORY_NAMESPACE_DEFINE (OASIS_TENA_DATACHANNEL_SUBSCRIBER,
                              OASIS_Tena_Data_Channel_Subscriber,
                              OASIS::Tena_Data_Channel_Subscriber)
