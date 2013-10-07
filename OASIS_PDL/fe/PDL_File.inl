// -*- C++ -*-
// $Id: PDL_File.inl 1819 2011-08-02 18:46:55Z hillj $

//
// OASIS_PDL_File
//
OASIS_INLINE
OASIS_PDL_File::OASIS_PDL_File (void)
{

}

//
// ~OASIS_PDL_File
//
OASIS_INLINE
OASIS_PDL_File::~OASIS_PDL_File (void)
{

}


//
// decls
//
OASIS_INLINE
const std::vector <OASIS_PDL_Declaration *> &
OASIS_PDL_File::decls (void) const
{
  return this->decls_;
}

//
// add_decl
//
OASIS_INLINE
void OASIS_PDL_File::add_decl (OASIS_PDL_Declaration * decl)
{
  this->decls_.push_back (decl);
  decl->parent (this);
}
