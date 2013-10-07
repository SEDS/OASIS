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
// printValues
//
void Data_Observer::
printValues (PlatformNetworkProbe::PublicationStatePtr const & pPubState)
{
#if defined (_WIN32)
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("  nic = %s\n")
              ACE_TEXT ("  recv_bytes = %q\n")
              ACE_TEXT ("  recv_packets = %q\n")
              ACE_TEXT ("  recv_errors = %q\n")
              ACE_TEXT ("  recv_drop = %q\n")
              ACE_TEXT ("  recv_multicast = %q\n")
              ACE_TEXT ("  sent_bytes = %q\n")
              ACE_TEXT ("  sent_packets = %q\n")
              ACE_TEXT ("  sent_errors = %q\n")
              ACE_TEXT ("  sent_drop = %q\n")
              ACE_TEXT ("  recv_unknown = %q\n")
              ACE_TEXT ("  outbound_queue_length = %q\n"),
              pPubState->get_nic ().c_str (),
              pPubState->get_recv_bytes (),
              pPubState->get_recv_packets (),
              pPubState->get_recv_errors (),
              pPubState->get_recv_drop (),
              pPubState->get_recv_multicast (),
              pPubState->get_sent_bytes (),
              pPubState->get_sent_packets (),
              pPubState->get_sent_errors (),
              pPubState->get_sent_drop (),
              pPubState->get_recv_unknown (),
              pPubState->get_outbound_queue_length ()));
#else
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("  nic = %s\n")
              ACE_TEXT ("  recv_bytes = %q\n")
              ACE_TEXT ("  recv_packets = %q\n")
              ACE_TEXT ("  recv_errors = %q\n")
              ACE_TEXT ("  recv_drop = %q\n")
              ACE_TEXT ("  recv_multicast = %q\n")
              ACE_TEXT ("  sent_bytes = %q\n")
              ACE_TEXT ("  sent_packets = %q\n")
              ACE_TEXT ("  sent_errors = %q\n")
              ACE_TEXT ("  sent_drop = %q\n")
              ACE_TEXT ("  recv_compressed = %q\n")
              ACE_TEXT ("  recv_fifo = %q\n")
              ACE_TEXT ("  recv_frames = %q\n")
              ACE_TEXT ("  sent_compressed = %q\n")
              ACE_TEXT ("  sent_fifo = %q\n")
              ACE_TEXT ("  sent_collision = %q\n")
              ACE_TEXT ("  sent_carrier = %q\n"),
              pPubState->get_nic ().c_str (),
              pPubState->get_recv_bytes (),
              pPubState->get_recv_packets (),
              pPubState->get_recv_errors (),
              pPubState->get_recv_drop (),
              pPubState->get_recv_multicast (),
              pPubState->get_sent_bytes (),
              pPubState->get_sent_packets (),
              pPubState->get_sent_errors (),
              pPubState->get_sent_drop (),
              pPubState->get_recv_compressed (),
              pPubState->get_recv_fifo (),
              pPubState->get_recv_frames (),
              pPubState->get_sent_compressed (),
              pPubState->get_sent_fifo (),
              pPubState->get_sent_collision (),
              pPubState->get_sent_carrier ()));
#endif
}


//
// discoveryEvent
//
void Data_Observer::
discoveryEvent (PlatformNetworkProbe::ProxyPtr const & pProxy,
                PlatformNetworkProbe::PublicationStatePtr const & pPubState)

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
stateChangeEvent (PlatformNetworkProbe::ProxyPtr const & pProxy,
                  PlatformNetworkProbe::PublicationStatePtr const & pPubState)
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
destructionEvent (PlatformNetworkProbe::ProxyPtr const & pProxy,
                  PlatformNetworkProbe::PublicationStatePtr const & pPubState)
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
