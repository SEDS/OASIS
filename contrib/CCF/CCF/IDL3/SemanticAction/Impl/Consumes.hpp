// file      : CCF/IDL3/SemanticAction/Impl/Consumes.hpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Consumes.hpp 54992 2004-01-01 00:12:30Z boris $

#ifndef CCF_IDL3_SEMANTIC_ACTION_IMPL_CONSUMES_HPP
#define CCF_IDL3_SEMANTIC_ACTION_IMPL_CONSUMES_HPP

#include "CCF/IDL3/SemanticGraph/EventType.hpp"
#include "CCF/IDL3/SemanticAction/Consumes.hpp"
#include "CCF/IDL3/SemanticAction/Impl/Elements.hpp"

namespace CCF
{
  namespace IDL3
  {
    namespace SemanticAction
    {
      namespace Impl
      {
        struct Consumes : SemanticAction::Consumes, Base
        {
          Consumes (Context& c);

          virtual void
          type (IdentifierPtr const& id);

          virtual void
          name (SimpleIdentifierPtr const& id);

        private:
          SemanticGraph::EventType* type_;
        };
      }
    }
  }
}

#endif  // CCF_IDL3_SEMANTIC_ACTION_IMPL_CONSUMES_HPP
