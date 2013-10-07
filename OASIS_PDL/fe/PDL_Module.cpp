// $Id: PDL_Module.cpp 1716 2010-11-29 00:53:50Z hillj $

#include "PDL_Module.h"

#if !defined (__OASIS_INLINE__)
#include "PDL_Module.inl"
#endif

#include "PDL_Visitor.h"

//
// accept
//
void OASIS_PDL_Module::accept (OASIS_PDL_Visitor & v) const
{
  v.visit_module (*this);
}
