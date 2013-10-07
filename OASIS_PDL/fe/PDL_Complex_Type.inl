// -*- C++ -*-
// $Id: PDL_Complex_Type.inl 2235 2013-02-06 20:18:09Z dfeiock $

//
// OASIS_PDL_Complex_Type_Member
//
OASIS_INLINE
OASIS_PDL_Complex_Type_Member::
OASIS_PDL_Complex_Type_Member (void)
{

}

//
// ~OASIS_PDL_Complex_Type_Member
//
OASIS_INLINE
OASIS_PDL_Complex_Type_Member::
~OASIS_PDL_Complex_Type_Member (void)
{

}

//
// type
//
OASIS_INLINE
OASIS_PDL_Type * OASIS_PDL_Complex_Type_Member::type (void) const
{
  return this->type_;
}

//
// type
//
OASIS_INLINE
void OASIS_PDL_Complex_Type_Member::type (OASIS_PDL_Type * t)
{
  this->type_ = t;
}

//
// ~OASIS_PDL_Complex_Type
//
OASIS_INLINE
OASIS_PDL_Complex_Type::OASIS_PDL_Complex_Type (void)
{

}

//
// members
//
OASIS_INLINE
const std::vector <OASIS_PDL_Complex_Type_Member *> &
OASIS_PDL_Complex_Type::members (void) const
{
  return this->members_;
}

//
// add_member
//
OASIS_INLINE
void OASIS_PDL_Complex_Type::add_member (OASIS_PDL_Complex_Type_Member * type)
{
  this->members_.push_back (type);
}
