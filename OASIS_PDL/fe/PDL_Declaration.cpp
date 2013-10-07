// $Id: PDL_Declaration.cpp 1842 2011-08-15 23:28:59Z hillj $

#include "PDL_Declaration.h"

#if !defined (__OASIS_INLINE__)
#include "PDL_Declaration.inl"
#endif

#include "PDL_File.h"

#include <stack>
#include <typeinfo>

//
// fq_name
//
std::string OASIS_PDL_Declaration::
fq_name (const std::string & separator) const
{
  // Get the declaration's scope.
  std::string tempstr = this->scope (separator);

  // Determine if we need a separator.
  if (!tempstr.empty ())
    tempstr += separator;

  // Finally, append the name of the string.
  tempstr += this->name ();

  return tempstr;
}

//
// fq_name
//
std::string OASIS_PDL_Declaration::
scope (const std::string & separator) const
{
  std::stack <OASIS_PDL_Declaration *> scope;
  OASIS_PDL_Declaration * decl = this->parent ();

  while (0 != decl && typeid (*decl) != typeid (OASIS_PDL_File))
  {
    scope.push (decl);
    decl = decl->parent ();
  }

  std::string tempstr;

  if (!scope.empty ())
  {
    // Prepare the temporary string.
    decl = scope.top ();
    tempstr += decl->name ();

    // Remove the top of the stack.
    scope.pop ();

    while (!scope.empty ())
    {
      // Append the next level of the string.
      decl = scope.top ();
      tempstr += separator + decl->name ();

      // Remove the top of the stack.
      scope.pop ();
    }
  }

  return tempstr;
}
