// -*- C++ -*-
// $Id: Data_Channel.inl 2224 2012-12-10 06:35:58Z dfeiock $

namespace OASIS
{
//
// Data_Channel
//
OASIS_INLINE
Data_Channel::Data_Channel (void)
: is_connected_ (false),
  packager_ (0)
{

}

//
// ~Data_Channel
//
OASIS_INLINE
Data_Channel::~Data_Channel (void)
{

}

//
// is_connected
//
OASIS_INLINE
bool Data_Channel::is_connected (void) const
{
  return this->is_connected_;
}

}
