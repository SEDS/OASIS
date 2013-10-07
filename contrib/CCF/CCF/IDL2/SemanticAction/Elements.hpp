// file      : CCF/IDL2/SemanticAction/Elements.hpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Elements.hpp 77342 2007-02-22 22:16:47Z wotte $

#ifndef CCF_IDL2_SEMANTIC_ACTION_ELEMENTS_HPP
#define CCF_IDL2_SEMANTIC_ACTION_ELEMENTS_HPP

#include "CCF/IDL2/Token.hpp"

namespace CCF
{
  namespace IDL2
  {
    namespace SemanticAction
    {
      struct Scope
      {
        virtual ~Scope ()
        {
        }
        
        virtual void
        open_scope () = 0;

        virtual void
        close_scope () = 0;
      };
    }
  }
}

#endif  // CCF_IDL2_SEMANTIC_ACTION_ELEMENTS_HPP
