// $Id: Local_Data_Channel.cpp 2221 2012-11-19 20:26:38Z dfeiock $

#include "Local_Data_Channel.h"

#if !defined (__OASIS_INLINE__)
#include "Local_Data_Channel.inl"
#endif

namespace OASIS
{

//
// packager
//
Software_Probe_Data_Packager *
Local_Data_Channel::packager (void)
{
  return this->packager_->clone ();
}

//
// packager
//
void
Local_Data_Channel::packager (Software_Probe_Data_Packager * p)
{
  this->packager_ = p;
}

}
