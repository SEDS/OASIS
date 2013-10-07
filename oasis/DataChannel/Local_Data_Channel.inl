// -*- C++ -*-
// $Id: Local_Data_Channel.inl 2085 2011-12-31 07:49:04Z hillj $


namespace OASIS
{

//
// Local_Data_Channel
//
OASIS_INLINE
Local_Data_Channel::Local_Data_Channel (void)
{

}

//
// ~Local_Data_Channel
//
OASIS_INLINE
Local_Data_Channel::~Local_Data_Channel (void)
{

}

//
// connect
//
OASIS_INLINE
void Local_Data_Channel::connect (void)
{
  this->is_connected_ = true;
}

}
