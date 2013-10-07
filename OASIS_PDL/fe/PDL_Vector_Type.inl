// -*- C++ -*-
// $Id: PDL_Vector_Type.inl 2235 2013-02-06 20:18:09Z dfeiock $

//
// OASIS_PDL_Vector_Type
//
OASIS_INLINE
OASIS_PDL_Vector_Type::OASIS_PDL_Vector_Type (void)
: type_ (0)
{

}

//
// ~OASIS_PDL_Vector_Type
//
OASIS_INLINE
OASIS_PDL_Vector_Type::~OASIS_PDL_Vector_Type (void)
{

}

//
// type
//
OASIS_INLINE
void OASIS_PDL_Vector_Type::type (OASIS_PDL_Type * t)
{
  this->type_ = t;
}

//
// type
//
OASIS_INLINE
OASIS_PDL_Type * OASIS_PDL_Vector_Type::type (void) const
{
  return this->type_;
}
