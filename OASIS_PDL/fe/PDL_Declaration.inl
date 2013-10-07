// -*- C++ -*-
// $Id: PDL_Declaration.inl 2235 2013-02-06 20:18:09Z dfeiock $

//
// OASIS_PDL_Declaration
//
OASIS_INLINE
OASIS_PDL_Declaration::OASIS_PDL_Declaration (void)
: parent_ (0)
{

}

//
// OASIS_PDL_Declaration
//
OASIS_INLINE
OASIS_PDL_Declaration::~OASIS_PDL_Declaration (void)
{

}

//
// name
//
OASIS_INLINE
const std::string & OASIS_PDL_Declaration::name (void) const
{
  return this->name_;
}

//
// name
//
OASIS_INLINE
void OASIS_PDL_Declaration::name (const std::string & name)
{
  this->name_ = name;
}

//
// parent
//
OASIS_INLINE
OASIS_PDL_Declaration * OASIS_PDL_Declaration::parent (void) const
{
  return this->parent_;
}

//
// parent
//
OASIS_INLINE
void OASIS_PDL_Declaration::parent (OASIS_PDL_Declaration * p)
{
  this->parent_ = p;
}
