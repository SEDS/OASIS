// $Id: Data_Observer.cpp 2067 2011-11-30 20:46:57Z dfeiock $

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
// discoveryEvent
//
void Data_Observer::
discoveryEvent (OASIS::Foo::ProxyPtr const & pProxy,
                OASIS::Foo::PublicationStatePtr const & pPubState)

{
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - subscriber: discoveryEvent () for %s\n"),
              pPubState->get_name ().c_str ()));

  this->curr_[pPubState->get_name ()] = 1;
}

//
// stateChangeEvent
//
void Data_Observer::
stateChangeEvent (OASIS::Foo::ProxyPtr const & pProxy,
                  OASIS::Foo::PublicationStatePtr const & pPubState)
{
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - subscriber: stateChangeEvent() for %s\n"),
              pPubState->get_name ().c_str ()));
}

//
// destructionEvent
//
void Data_Observer::
destructionEvent (OASIS::Foo::ProxyPtr const & pProxy,
                  OASIS::Foo::PublicationStatePtr const & pPubState)
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
