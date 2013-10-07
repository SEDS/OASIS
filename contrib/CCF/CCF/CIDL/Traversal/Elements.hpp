// file      : CCF/CIDL/Traversal/Elements.hpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Elements.hpp 54723 2003-12-22 22:26:40Z boris $

#ifndef CCF_CIDL_TRAVERSAL_ELEMENTS_HPP
#define CCF_CIDL_TRAVERSAL_ELEMENTS_HPP

#include "CCF/IDL3/Traversal/Elements.hpp"

#include "CCF/CIDL/SemanticGraph/Elements.hpp"

namespace CCF
{
  namespace CIDL
  {
    namespace Traversal
    {
      using namespace IDL3::Traversal;

      //
      //
      //
      struct Implements : Edge<SemanticGraph::Implements>
      {
        virtual void
        traverse (Type& e)
        {
          node_traverser ().traverse (e.implementee ());
        }
      };

    }
  }
}

#endif  // CCF_CIDL_TRAVERSAL_ELEMENTS_HPP
