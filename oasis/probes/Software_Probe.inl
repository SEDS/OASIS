// -*- C++ -*-
// $Id: Software_Probe.inl 2211 2012-07-25 12:55:51Z dfeiock $

namespace OASIS
{

//
// Software_Probe
//
OASIS_INLINE
Software_Probe::Software_Probe (void)
{

}

//
// Software_Probe
//
OASIS_INLINE
Software_Probe::~Software_Probe (void)
{

}

//
// UUID
//
OASIS_INLINE
const ACE_Utils::UUID & Software_Probe::uuid (void) const
{
  return this->uuid_;
}

//
// timestamp
//
OASIS_INLINE
const ACE_Time_Value & Software_Probe::timestamp (void) const
{
  return this->last_ts_;
}

//
// sequence_number
//
OASIS_INLINE
const ACE_UINT32 & Software_Probe::sequence_number (void) const
{
  return this->seqnum_;
}

//
// state
//
OASIS_INLINE
const ACE_UINT16 & Software_Probe::state (void) const
{
  return this->state_;
}

//
// data_size
//
OASIS_INLINE
const ACE_UINT32 & Software_Probe::data_size (void) const
{
  return this->datasize_;
}

//
// instance_name
//
OASIS_INLINE
const ACE_CString & Software_Probe::instance_name (void) const
{
  return this->name_;
}

}
