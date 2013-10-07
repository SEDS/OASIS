// $Id: PDL_Struct.cpp 1716 2010-11-29 00:53:50Z hillj $

#include "PDL_Struct.h"

#if !defined (__OASIS_INLINE__)
#include "PDL_Struct.inl"
#endif

#include "PDL_Visitor.h"

//
// accept
//
void OASIS_PDL_Struct::accept (OASIS_PDL_Visitor & v) const
{
  v.visit_struct (*this);
}
