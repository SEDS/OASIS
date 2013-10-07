// $Id: Tdl_Generator.cpp 1819 2011-08-02 18:46:55Z hillj $

#include "Tdl_Generator.h"

#if !defined (__OASIS_INLINE__)
#include "Tdl_Generator.inl"
#endif

#include "Tdl_Generator_Visitor.h"
#include "fe/PDL_Configuration.h"
#include "fe/PDL_File.h"

#include <fstream>
#include <sstream>

OASIS_PDL_BE_IMPL (_make_OASIS_PDL_Tdl_Generator, OASIS_PDL_Tdl_Generator);

//
// generate
//
int OASIS_PDL_Tdl_Generator::
generate (const OASIS_PDL_File & file)
{
  OASIS_PDL_Tdl_Generator_Visitor tdl_visitor;
  file.accept (tdl_visitor);

  return 0;
}
