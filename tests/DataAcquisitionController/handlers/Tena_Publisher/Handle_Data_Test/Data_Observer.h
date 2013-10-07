// -*- C++ -*-

//=============================================================================
/**
 *  @file       Data_Channel_Subscriber.h
 *
 *  $Id: Data_Observer.h 1948 2011-09-30 16:32:04Z hillj $
 *
 *  @author     Harold Owens II
 */
//=============================================================================

#ifndef _OASIS_TENA_REGISTRATION_CHANNEL_OBSERVER_H_
#define _OASIS_TENA_REGISTRATION_CHANNEL_OBSERVER_H_

#include "OASIS/Foo.h"
#include "ace/Condition_T.h"
#include "ace/Thread_Mutex.h"

namespace OASIS
{
namespace Test
{

/**
 * @class Tena_Data_Channel_Observer
 *
 * Implementation of the observer for the TENA data channel. It only
 * listens for events from specific channels.
 */
class Data_Observer : public OASIS::Foo::AbstractObserver
{
public:
  /// Default constructor.
  Data_Observer (size_t iterations);

  /// Destructor.
  virtual ~Data_Observer (void);

  virtual void
    discoveryEvent (OASIS::Foo::ProxyPtr const & pProxy,
                    OASIS::Foo::PublicationStatePtr const & pPubState);

  virtual void
    stateChangeEvent (OASIS::Foo::ProxyPtr const & pProxy,
                      OASIS::Foo::PublicationStatePtr const & pPubState);

  virtual void
    destructionEvent (OASIS::Foo::ProxyPtr const & pProxy,
                      OASIS::Foo::PublicationStatePtr const & pPubState);

  /// Wait for the observer to observe all events.
  void wait (void);

private:
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
