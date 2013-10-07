// $Id: PDL_Vector_Type.cpp 1896 2011-09-07 14:56:19Z hillj $

#include "PDL_Vector_Type.h"

#if !defined (__OASIS_INLINE__)
#include "PDL_Vector_Type.inl"
#endif

#include "PDL_Visitor.h"

//
// accept
//
void OASIS_PDL_Vector_Type::accept (OASIS_PDL_Visitor & v) const
{
  v.visit_vector_type (*this);
}
