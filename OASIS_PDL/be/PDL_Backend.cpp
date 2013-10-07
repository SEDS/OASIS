// $Id: PDL_Backend.cpp 1716 2010-11-29 00:53:50Z hillj $

#include "PDL_Backend.h"

#if !defined (__OASIS_INLINE__)
#include "PDL_Backend.inl"
#endif

//
// destroy
//
void OASIS_PDL_Backend::destroy (void)
{
  delete this;
}
