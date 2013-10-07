// -*- C++ -*-
// $Id4

namespace OASIS
{

//
// ~Latest_Local_Data_Channel
//
OASIS_INLINE
Latest_Local_Data_Channel::~Latest_Local_Data_Channel (void)
{

}

//
// get_data
//
OASIS_INLINE
const char * Latest_Local_Data_Channel::get_data (void) const
{
  return this->data_.get ();
}

//
// get_data_length
//
OASIS_INLINE
size_t Latest_Local_Data_Channel::get_data_length (void) const
{
  return this->length_;
}

}
