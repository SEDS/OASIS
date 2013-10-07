// file      : CCF/CIDL/SemanticAction/Composition.cpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Composition.cpp 80204 2007-12-06 17:58:19Z wotte $

#include "CCF/CIDL/SemanticAction/Composition.hpp"

#include <ostream>

namespace CCF
{
  namespace CIDL
  {
    namespace SemanticAction
    {
    }
  }
}

namespace
{
  const char* labels[] = {"entity", "process", "service", "session" };
}

std::ostream&
operator<< (std::ostream& o,
            CCF::CIDL::SemanticAction::Composition::Category::Value v)
{
  return o << labels[v];
}
