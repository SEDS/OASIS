// -*- C++ -*-
// $Id: Configuration.inl 2096 2012-01-06 14:02:03Z dfeiock $

namespace OASIS
{

//
// Einode_Configuration
//
OASIS_INLINE
Einode_Configuration::Einode_Configuration (void)
: reconnect_timeout_ (1,0)
{

}

//
// Einode_Configuration
//
OASIS_INLINE
Einode_Configuration::~Einode_Configuration (void)
{

}

//
// name
//
OASIS_INLINE
const std::string & Einode_Configuration::name (void) const
{
  return this->name_;
}

//
// uuid
//
OASIS_INLINE
const ACE_Utils::UUID & Einode_Configuration::uuid (void) const
{
  return this->uuid_;
}

//
// reconnect_timeout
//
OASIS_INLINE
const ACE_Time_Value & Einode_Configuration::reconnect_timeout (void) const
{
  return this->reconnect_timeout_;
}

//
// data_channel
//
OASIS_INLINE
const Einode_Configuration::Data_Channel &
Einode_Configuration::data_channel (void) const
{
  return this->data_channel_;
}

}
