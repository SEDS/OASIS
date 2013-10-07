// file      : CCF/IDL2/SemanticGraph/Literals.cpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Literals.cpp 74499 2006-09-22 10:02:37Z boris $

#include "CCF/IDL2/SemanticGraph/Literals.hpp"

#include <ostream>

namespace CCF
{
  namespace IDL2
  {
    namespace SemanticGraph
    {
    }
  }
}

std::ostream&
operator<< (std::ostream& o,
            CCF::IDL2::SemanticGraph::StringLiteral const& lit)
{
  return o << '\"' << lit.literal () << '\"';
}
