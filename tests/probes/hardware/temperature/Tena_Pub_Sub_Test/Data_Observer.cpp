// $Id: Data_Observer.cpp 2112 2012-01-12 21:27:36Z dfeiock $

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
printValues (PlatformTemperatureProbe::PublicationStatePtr const & pPubState)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("  temperatureCelcius = %0.2f\n")
              ACE_TEXT ("  serialNumber = %s\n")
              ACE_TEXT ("  installedLocation = %s\n")
              ACE_TEXT ("  partNumber = %s\n")
              ACE_TEXT ("  manufacturer = %s\n"),
              pPubState->get_temperatureCelcius (),
              pPubState->get_serialNumber ().c_str (),
              pPubState->get_installedLocation ().c_str (),
              pPubState->get_partNumber ().c_str (),
              pPubState->get_manufacturer ().c_str ()));
}


//
// discoveryEvent
//
void Data_Observer::
discoveryEvent (PlatformTemperatureProbe::ProxyPtr const & pProxy,
                PlatformTemperatureProbe::PublicationStatePtr const & pPubState)

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
stateChangeEvent (PlatformTemperatureProbe::ProxyPtr const & pProxy,
                  PlatformTemperatureProbe::PublicationStatePtr const & pPubState)
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
destructionEvent (PlatformTemperatureProbe::ProxyPtr const & pProxy,
                  PlatformTemperatureProbe::PublicationStatePtr const & pPubState)
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
