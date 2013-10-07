// $Id: Latest_Local_Data_Channel.cpp 2235 2013-02-06 20:18:09Z dfeiock $

#include "Latest_Local_Data_Channel.h"

#if !defined (__OASIS_INLINE__)
#include "Latest_Local_Data_Channel.inl"
#endif

#include "ace/OS_NS_string.h"
#include "Standard_Software_Probe_Data_Packager.h"

namespace OASIS
{

//
// Latest_Local_Data_Channel
//
Latest_Local_Data_Channel::Latest_Local_Data_Channel (void)
: length_ (0)
{
  this->packager_ = new Standard_Software_Probe_Data_Packager ();
}


//
// send_data
//
void Latest_Local_Data_Channel::send_data (const char * data, size_t length)
{
  // Store the latest snapshot of data received.
  this->data_.reset (new char [length]);
  this->length_ = length;

  ACE_OS::memcpy (this->data_.get (),
                  data,
                  length);
}

}
