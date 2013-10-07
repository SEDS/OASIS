// $Id: Data_Observer.cpp 2123 2012-01-23 17:23:03Z dfeiock $

#include "Data_Observer.h"

namespace OASIS
{
namespace Test
{

//
// Data_Observer
//
Data_Observer::Data_Observer (size_t iterations)
: cond_ (lock_),
  iterations_ (iterations)
{

}

//
// ~Data_Observer
//
Data_Observer::~Data_Observer (void)
{

}

//
// printValues
//
void Data_Observer::
printValues (PlatformProcessorProbe::PublicationStatePtr const & pPubState)
{
#if defined (_WIN32)
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("  idle_time = %q\n")
              ACE_TEXT ("  system_time = %q\n")
              ACE_TEXT ("  user_time = %q\n"),
              pPubState->get_idle_time (),
              pPubState->get_system_time (),
              pPubState->get_user_time ()));
#else
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("  idle_time = %q\n")
              ACE_TEXT ("  system_time = %q\n")
              ACE_TEXT ("  user_time = %q\n")
              ACE_TEXT ("  nice_time = %q\n")
              ACE_TEXT ("  iowait_time = %q\n")
              ACE_TEXT ("  irq_time = %q\n")
              ACE_TEXT ("  soft_irq_time = %q\n"),
              pPubState->get_idle_time (),
              pPubState->get_system_time (),
              pPubState->get_user_time (),
              pPubState->get_nice_time (),
              pPubState->get_iowait_time (),
              pPubState->get_irq_time (),
              pPubState->get_soft_irq_time ()));
#endif
}


//
// discoveryEvent
//
void Data_Observer::
discoveryEvent (PlatformProcessorProbe::ProxyPtr const & pProxy,
                PlatformProcessorProbe::PublicationStatePtr const & pPubState)

{
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - subscriber: discoveryEvent () for %s\n"),
              pPubState->get_name ().c_str ()));

  this->curr_[pPubState->get_name ()] = 1;
  this->printValues (pPubState);
}

//
// stateChangeEvent
//
void Data_Observer::
stateChangeEvent (PlatformProcessorProbe::ProxyPtr const & pProxy,
                  PlatformProcessorProbe::PublicationStatePtr const & pPubState)
{
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - subscriber: stateChangeEvent() for %s\n"),
              pPubState->get_name ().c_str ()));

  this->printValues (pPubState);
}

//
// destructionEvent
//
void Data_Observer::
destructionEvent (PlatformProcessorProbe::ProxyPtr const & pProxy,
                  PlatformProcessorProbe::PublicationStatePtr const & pPubState)
{
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - subscriber: destructionEvent() for %s\n"),
              pPubState->get_name ().c_str ()));

  // Remove the counter from the collection.
  this->curr_.erase (pPubState->get_name ());

  ACE_GUARD (ACE_Thread_Mutex, guard, this->lock_);
  if (this->curr_.empty ())
    this->cond_.signal ();
}

//
// wait
//
void Data_Observer::wait (void)
{
  ACE_GUARD (ACE_Thread_Mutex, guard, this->lock_);
  this->cond_.wait ();
}

}
}
