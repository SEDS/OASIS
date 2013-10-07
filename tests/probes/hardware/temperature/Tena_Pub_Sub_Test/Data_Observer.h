// -*- C++ -*-

//=============================================================================
/**
 *  @file       Data_Channel_Subscriber.h
 *
 *  $Id: Data_Observer.h 2111 2012-01-12 21:03:49Z dfeiock $
 *
 *  @author     Harold Owens II
 */
//=============================================================================

#ifndef _OASIS_TENA_REGISTRATION_CHANNEL_OBSERVER_H_
#define _OASIS_TENA_REGISTRATION_CHANNEL_OBSERVER_H_

#include "ace/Condition_T.h"
#include "ace/Thread_Mutex.h"
#include "OASIS/HardwareProbes/TemperatureProbe.h"

namespace OASIS
{
namespace Test
{

  namespace PlatformTemperatureProbe = OASIS::HardwareProbes::TemperatureProbe;

/**
 * @class Tena_Data_Channel_Observer
 *
 * Implementation of the observer for the TENA data channel. It only
 * listens for events from specific channels.
 */
class Data_Observer : public PlatformTemperatureProbe::AbstractObserver
{
public:
  /// Default constructor.
  Data_Observer (size_t iterations);

  /// Destructor.
  virtual ~Data_Observer (void);

  virtual void
    discoveryEvent (PlatformTemperatureProbe::ProxyPtr const & pProxy,
                    PlatformTemperatureProbe::PublicationStatePtr const & pPubState);

  virtual void
    stateChangeEvent (PlatformTemperatureProbe::ProxyPtr const & pProxy,
                      PlatformTemperatureProbe::PublicationStatePtr const & pPubState);

  virtual void
    destructionEvent (PlatformTemperatureProbe::ProxyPtr const & pProxy,
                      PlatformTemperatureProbe::PublicationStatePtr const & pPubState);

  /// Wait for the observer to observe all events.
  void wait (void);

private:
  /// Helper to output probe values
  void printValues (PlatformTemperatureProbe::PublicationStatePtr const & pPubState);

  /// The thread lock.
  ACE_Thread_Mutex lock_;

  /// Condition assigned to lock_.
  ACE_Condition <ACE_Thread_Mutex> cond_;

  /// Number of iterations to watch.
  size_t iterations_;

  /// Map of current iterations for each servant.
  std::map <std::string, size_t> curr_;
};

}
}

#endif  // !defined _OASIS_TENA_DATA_CHANNEL_OBSERVER_H_
