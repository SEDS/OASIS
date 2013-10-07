// -*- C++ -*-
// $Id: PDL_Simple_Type.inl 1716 2010-11-29 00:53:50Z hillj $

//
// OASIS_PDL_Simple_Type
//
OASIS_INLINE
OASIS_PDL_Simple_Type::OASIS_PDL_Simple_Type (void)
{

}

//
// ~OASIS_PDL_Simple_Type
//
OASIS_INLINE
OASIS_PDL_Simple_Type::~OASIS_PDL_Simple_Type (void)
{

}

//
// kind
//
OASIS_INLINE
void OASIS_PDL_Simple_Type::kind (tk_kind kind)
{
  this->kind_ = kind;
}

//
// kind
//
OASIS_INLINE
OASIS_PDL_Simple_Type::tk_kind OASIS_PDL_Simple_Type::kind (void) const
{
  return this->kind_;
}
