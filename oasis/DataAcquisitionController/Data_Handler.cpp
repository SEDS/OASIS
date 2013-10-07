// $Id: Data_Handler.cpp 1991 2011-10-10 02:05:19Z hillj $

#include "Data_Handler.h"

#if !defined (__OASIS_INLINE__)
#include "Data_Handler.inl"
#endif

namespace OASIS
{
namespace DAC
{

//
// destroy
//
void Data_Handler::destroy (void)
{
  delete this;
}

}
}
