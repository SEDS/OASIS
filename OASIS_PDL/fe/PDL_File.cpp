// $Id: PDL_File.cpp 1820 2011-08-08 23:58:09Z hillj $

#include "PDL_File.h"

#if !defined (__OASIS_INLINE__)
#include "PDL_File.inl"
#endif

#include "PDL_Visitor.h"

//
// OASIS_PDL_File_Attr
//
OASIS_PDL_File_Attr::OASIS_PDL_File_Attr (void)
: version_major_ (1),
  version_minor_ (0)
{

}

//
// accept
//
void OASIS_PDL_File::accept (OASIS_PDL_Visitor & v) const
{
  v.visit_file (*this);
}

//
// attr
//
const OASIS_PDL_File_Attr & OASIS_PDL_File::attr (void) const
{
  return this->attr_;
}

//
// attr
//
OASIS_PDL_File_Attr & OASIS_PDL_File::attr (void)
{
  return this->attr_;
}
