// -*- C++ -*-
// $Id: Software_Probe_Impl.inl 2235 2013-02-06 20:18:09Z dfeiock $

#include "oasis/DataChannel/Local_Data_Channel.h"

namespace OASIS
{

//
// ~Software_Probe_Impl
//
OASIS_INLINE
Software_Probe_Impl::~Software_Probe_Impl (void)
{
  this->packager_->release ();
  this->packager_ = 0;
}

//
// UUID
//
OASIS_INLINE
const ACE_Utils::UUID & Software_Probe_Impl::uuid (void) const
{
  return this->uuid_;
}

//
// timestamp
//
OASIS_INLINE
const ACE_Time_Value & Software_Probe_Impl::timestamp (void) const
{
  return this->last_ts_;
}

//
// sequence_number
//
OASIS_INLINE
const ACE_UINT32 & Software_Probe_Impl::sequence_number (void) const
{
  return this->seqnum_;
}

//
// state
//
OASIS_INLINE
const ACE_UINT16 & Software_Probe_Impl::state (void) const
{
  return this->state_;
}

//
// data_size
//
OASIS_INLINE
const ACE_UINT32 & Software_Probe_Impl::data_size (void) const
{
  return this->datasize_;
}

//
// fini
//
OASIS_INLINE
int Software_Probe_Impl::fini (void)
{
  this->data_channel_ = 0;

  return 0;
}

//
// handle_collect_data
//
OASIS_INLINE
int Software_Probe_Impl::handle_collect_data (void)
{
  return 0;
}

//
// flush_interval
//
OASIS_INLINE
const ACE_Time_Value &
Software_Probe_Impl::flush_interval (void) const
{
  return this->interval_;
}

//
// flush_interval
//
OASIS_INLINE
void
Software_Probe_Impl::flush_interval (const ACE_Time_Value & interval)
{
  this->interval_ = interval;
}

//
// is_active_object
//
OASIS_INLINE
bool
Software_Probe_Impl::is_active_object (void) const
{
  if (this->interval_ != ACE_Time_Value::zero)
    return true;
  return false;
}

//
// is_initalized
//
OASIS_INLINE
bool Software_Probe_Impl::is_initalized (void)
{
  return this->is_init_;
}

//
// instance_name
//
OASIS_INLINE
const ACE_CString &
Software_Probe_Impl::instance_name (void) const
{
  return this->name_;
}

}
