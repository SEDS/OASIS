// file      : CCF/IDL3/SemanticAction/Emits.hpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Emits.hpp 77342 2007-02-22 22:16:47Z wotte $

#ifndef CCF_IDL3_SEMANTIC_ACTION_EMITS_HPP
#define CCF_IDL3_SEMANTIC_ACTION_EMITS_HPP

#include "CCF/IDL3/SemanticAction/Elements.hpp"

namespace CCF
{
  namespace IDL3
  {
    namespace SemanticAction
    {
      struct Emits
      {
        virtual ~Emits ()
        {
        }
        
        virtual void
        type (IdentifierPtr const& id) = 0;

        virtual void
        name (SimpleIdentifierPtr const& id) = 0;
      };
    }
  }
}

#endif  // CCF_IDL3_SEMANTIC_ACTION_EMITS_HPP
