// -*- C++ -*-

//=============================================================================
/**
 *  @file       Data_Channel_Subscriber.h
 *
 *  $Id: Data_Observer.h 2007 2011-10-11 12:54:21Z dfeiock $
 *
 *  @author     Harold Owens II
 */
//=============================================================================

#ifndef _OASIS_TENA_REGISTRATION_CHANNEL_OBSERVER_H_
#define _OASIS_TENA_REGISTRATION_CHANNEL_OBSERVER_H_

#include "ace/Condition_T.h"
#include "ace/Thread_Mutex.h"

#if defined (_WIN32)
  #include "OASIS/System/Network/WindowsNetworkProbe.h"
#else
  #include "OASIS/System/Network/LinuxNetworkProbe.h"
#endif

namespace OASIS
{
namespace Test
{

#if defined (_WIN32)
    namespace PlatformNetworkProbe = OASIS::System::Network::WindowsNetworkProbe;
#else
    namespace PlatformNetworkProbe = OASIS::System::Network::LinuxNetworkProbe;
#endif

/**
 * @class Tena_Data_Channel_Observer
 *
 * Implementation of the observer for the TENA data channel. It only
 * listens for events from specific channels.
 */
class Data_Observer : public PlatformNetworkProbe::AbstractObserver
{
public:
  /// Default constructor.
  Data_Observer (size_t iterations);

  /// Destructor.
  virtual ~Data_Observer (void);

  virtual void
    discoveryEvent (PlatformNetworkProbe::ProxyPtr const & pProxy,
                    PlatformNetworkProbe::PublicationStatePtr const & pPubState);

  virtual void
    stateChangeEvent (PlatformNetworkProbe::ProxyPtr const & pProxy,
                      PlatformNetworkProbe::PublicationStatePtr const & pPubState);

  virtual void
    destructionEvent (PlatformNetworkProbe::ProxyPtr const & pProxy,
                      PlatformNetworkProbe::PublicationStatePtr const & pPubState);

  /// Wait for the observer to observe all events.
  void wait (void);

private:
  /// Helper to output probe values
  void printValues (PlatformNetworkProbe::PublicationStatePtr const & pPubState);

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
