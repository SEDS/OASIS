// -*- C++ -*-
// $Id: PDL_Module.inl 1819 2011-08-02 18:46:55Z hillj $

//
// OASIS_PDL_Module
//
OASIS_INLINE
OASIS_PDL_Module::OASIS_PDL_Module (void)
{

}

//
// ~OASIS_PDL_Module
//
OASIS_INLINE
OASIS_PDL_Module::~OASIS_PDL_Module (void)
{

}

//
// decls
//
OASIS_INLINE
const std::vector <OASIS_PDL_Declaration *> &
OASIS_PDL_Module::decls (void) const
{
  return this->decls_;
}

//
// add_decl
//
OASIS_INLINE
void OASIS_PDL_Module::add_decl (OASIS_PDL_Declaration * decl)
{
  this->decls_.push_back (decl);
  decl->parent (this);
}
