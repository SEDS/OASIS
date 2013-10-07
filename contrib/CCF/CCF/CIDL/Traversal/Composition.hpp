// file      : CCF/CIDL/Traversal/Composition.hpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Composition.hpp 54723 2003-12-22 22:26:40Z boris $

#ifndef CCF_CIDL_TRAVERSAL_COMPOSITION_HPP
#define CCF_CIDL_TRAVERSAL_COMPOSITION_HPP

#include "CCF/CIDL/SemanticGraph/Composition.hpp"
#include "CCF/CIDL/Traversal/Elements.hpp"

namespace CCF
{
  namespace CIDL
  {
    namespace Traversal
    {
      template <typename T>
      struct CompositionTemplate : ScopeTemplate<T>
      {
        virtual void
        traverse (T&);

        virtual void
        pre (T&);

        virtual void
        name (T&);

        virtual void
        post (T&);
      };


      typedef
      CompositionTemplate <SemanticGraph::Composition>
      Composition;

      typedef
      CompositionTemplate <SemanticGraph::EntityComposition>
      EntityComposition;

      typedef
      CompositionTemplate <SemanticGraph::ProcessComposition>
      ProcessComposition;

      typedef
      CompositionTemplate <SemanticGraph::ServiceComposition>
      ServiceComposition;


      typedef
      CompositionTemplate <SemanticGraph::SessionComposition>
      SessionComposition;
    }
  }
}

#include "CCF/CIDL/Traversal/Composition.tpp"

#endif  // CCF_CIDL_TRAVERSAL_COMPOSITION_HPP
