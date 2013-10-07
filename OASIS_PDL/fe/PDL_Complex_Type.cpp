// $Id: PDL_Complex_Type.cpp 1716 2010-11-29 00:53:50Z hillj $

#include "PDL_Complex_Type.h"

#if !defined (__OASIS_INLINE__)
#include "PDL_Complex_Type.inl"
#endif

#include "PDL_Visitor.h"

//
// accept
//
void OASIS_PDL_Complex_Type_Member::accept (OASIS_PDL_Visitor & v) const
{
  v.visit_complex_type_member (*this);
}

//
// OASIS_PDL_Complex_Type
//
OASIS_PDL_Complex_Type::~OASIS_PDL_Complex_Type (void)
{
  std::vector <OASIS_PDL_Complex_Type_Member *>::iterator
    iter = this->members_.begin (),
    iter_end = this->members_.end ();

  for (; iter != iter_end; ++ iter)
    delete *iter;
}

//
// new_member
//
OASIS_PDL_Complex_Type_Member *
OASIS_PDL_Complex_Type::new_member (void)
{
  OASIS_PDL_Complex_Type_Member * m = new OASIS_PDL_Complex_Type_Member ();
  this->members_.push_back (m);

  return m;
}
