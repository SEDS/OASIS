// $Id: Memory_Data_Observer.cpp 2099 2012-01-09 22:28:58Z dfeiock $

#include "Memory_Data_Observer.h"

namespace OASIS
{
namespace Test
{

//
// Memory_Data_Observer
//
Memory_Data_Observer::Memory_Data_Observer (size_t iterations)
: cond_ (lock_),
  iterations_ (iterations)
{

}

//
// ~Memory_Data_Observer
//
Memory_Data_Observer::~Memory_Data_Observer (void)
{

}

//
// printValues
//
void Memory_Data_Observer::
printValues (PlatformMemoryProbe::PublicationStatePtr const & pPubState)
{
#if defined (_WIN32)
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("  physical_memory_avail = %q kB\n")
              ACE_TEXT ("  physical_memory_total = %q kB\n")
              ACE_TEXT ("  system_cache = %q kB\n")
              ACE_TEXT ("  commit_total = %q kB\n")
              ACE_TEXT ("  commit_limit = %q kB\n")
              ACE_TEXT ("  virtual_total = %q kB\n")
              ACE_TEXT ("  virtual_used = %q kB\n"),
              pPubState->get_physical_memory_avail (),
              pPubState->get_physical_memory_total (),
              pPubState->get_system_cache (),
              pPubState->get_commit_total (),
              pPubState->get_commit_limit (),
              pPubState->get_virtual_total (),
              pPubState->get_virtual_used ()));
#else
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("  physical_memory_avail = %q kB\n")
              ACE_TEXT ("  physical_memory_total = %q kB\n")
              ACE_TEXT ("  system_cache = %q kB\n")
              ACE_TEXT ("  commit_total = %q kB\n")
              ACE_TEXT ("  commit_limit = %q kB\n")
              ACE_TEXT ("  virtual_total = %q kB\n")
              ACE_TEXT ("  virtual_used = %q kB\n")
              ACE_TEXT ("  buffers = %q kB\n")
              ACE_TEXT ("  swap_cache = %q kB\n")
              ACE_TEXT ("  inactive = %q kB\n")
              ACE_TEXT ("  active   = %q kB\n")
              ACE_TEXT ("  high_total = %q kB\n")
              ACE_TEXT ("  high_free = %q kB\n")
              ACE_TEXT ("  low_total = %q kB\n")
              ACE_TEXT ("  low_free = %q kB\n")
              ACE_TEXT ("  swap_total = %q kB\n")
              ACE_TEXT ("  swap_free = %q kB\n")
              ACE_TEXT ("  dirty = %q kB\n")
              ACE_TEXT ("  write_back = %q kB\n")
              ACE_TEXT ("  virtual_chunk = %q kB\n"),
              pPubState->get_physical_memory_avail (),
              pPubState->get_physical_memory_total (),
              pPubState->get_system_cache (),
              pPubState->get_commit_total (),
              pPubState->get_commit_limit (),
              pPubState->get_virtual_total (),
              pPubState->get_virtual_used (),
              pPubState->get_buffers (),
              pPubState->get_swap_cache (),
              pPubState->get_inactive (),
              pPubState->get_active (),
              pPubState->get_high_total (),
              pPubState->get_high_free (),
              pPubState->get_low_total (),
              pPubState->get_low_free (),
              pPubState->get_swap_total (),
              pPubState->get_swap_free (),
              pPubState->get_dirty (),
              pPubState->get_write_back (),
              pPubState->get_virtual_chunk ()));
#endif
}


//
// discoveryEvent
//
void Memory_Data_Observer::
discoveryEvent (PlatformMemoryProbe::ProxyPtr const & pProxy,
                PlatformMemoryProbe::PublicationStatePtr const & pPubState)

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
void Memory_Data_Observer::
stateChangeEvent (PlatformMemoryProbe::ProxyPtr const & pProxy,
                  PlatformMemoryProbe::PublicationStatePtr const & pPubState)
{
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - subscriber: stateChangeEvent() for %s\n"),
              pPubState->get_name ().c_str ()));

  this->printValues (pPubState);
}

//
// destructionEvent
//
void Memory_Data_Observer::
destructionEvent (PlatformMemoryProbe::ProxyPtr const & pProxy,
                  PlatformMemoryProbe::PublicationStatePtr const & pPubState)
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
void Memory_Data_Observer::wait (void)
{
  ACE_GUARD (ACE_Thread_Mutex, guard, this->lock_);
  this->cond_.wait ();
}

}
}
