// -*- C++ -*-

//=============================================================================
/**
 *  @file       Data_Channel_Subscriber.h
 *
 *  $Id: Processor_Data_Observer.h 2099 2012-01-09 22:28:58Z dfeiock $
 *
 *  @author     Harold Owens II
 */
//=============================================================================

#ifndef _OASIS_PROCESSOR_DATA_OBSERVER_H_
#define _OASIS_PROCESSOR_DATA_OBSERVER_H_

#include "ace/Condition_T.h"
#include "ace/Thread_Mutex.h"

#if defined (_WIN32)
  #include "OASIS/System/Processor/WindowsProcessorProbe.h"
#else
  #include "OASIS/System/Processor/LinuxProcessorProbe.h"
#endif

namespace OASIS
{
namespace Test
{

#if defined (_WIN32)
    namespace PlatformProcessorProbe = OASIS::System::Processor::WindowsProcessorProbe;
#else
    namespace PlatformProcessorProbe = OASIS::System::Processor::LinuxProcessorProbe;
#endif

/**
 * @class Tena_Data_Channel_Observer
 *
 * Implementation of the observer for the TENA data channel. It only
 * listens for events from specific channels.
 */
class Processor_Data_Observer : public PlatformProcessorProbe::AbstractObserver
{
public:
  /// Default constructor.
  Processor_Data_Observer (size_t iterations);

  /// Destructor.
  virtual ~Processor_Data_Observer (void);

  virtual void
    discoveryEvent (PlatformProcessorProbe::ProxyPtr const & pProxy,
                    PlatformProcessorProbe::PublicationStatePtr const & pPubState);

  virtual void
    stateChangeEvent (PlatformProcessorProbe::ProxyPtr const & pProxy,
                      PlatformProcessorProbe::PublicationStatePtr const & pPubState);

  virtual void
    destructionEvent (PlatformProcessorProbe::ProxyPtr const & pProxy,
                      PlatformProcessorProbe::PublicationStatePtr const & pPubState);

  /// Wait for the observer to observe all events.
  void wait (void);

private:
  /// Helper to output probe values
  void printValues (PlatformProcessorProbe::PublicationStatePtr const & pPubState);

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

#endif  // !defined _OASIS_PROCESSOR_DATA_OBSERVER_H_
