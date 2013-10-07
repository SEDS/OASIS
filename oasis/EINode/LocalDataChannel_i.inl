// -*- C++ -*-
// $Id: LocalDataChannel_i.inl 2221 2012-11-19 20:26:38Z dfeiock $

#include "Standard_EINode.h"

namespace OASIS
{
//
// Local_Data_Channel_i
//
OASIS_INLINE
Local_Data_Channel_i::
Local_Data_Channel_i (Standard_EINode * einode)
: einode_ (einode)
{

}

//
// Local_Data_Channel_i
//
OASIS_INLINE
Local_Data_Channel_i::~Local_Data_Channel_i (void)
{

}

//
// send_data
//
OASIS_INLINE
void Local_Data_Channel_i::send_data (const char * data, size_t length)
{
  this->einode_->send_data (data, length);
}

}
