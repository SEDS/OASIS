// $Id: PDL_Probe.cpp 1716 2010-11-29 00:53:50Z hillj $

#include "PDL_Probe.h"

#if !defined (__OASIS_INLINE__)
#include "PDL_Probe.inl"
#endif

#include "PDL_Visitor.h"

//
// accept
//
void OASIS_PDL_Probe::accept (OASIS_PDL_Visitor & v) const
{
  v.visit_probe (*this);
}
