// file      : CCF/IDL2/SemanticAction/Const.hpp
// author    : Boris Kolpackov <boris@kolpackov.net>
// cvs-id    : $Id: Const.hpp 77342 2007-02-22 22:16:47Z wotte $

#ifndef CCF_IDL2_SEMANTIC_ACTION_CONST_HPP
#define CCF_IDL2_SEMANTIC_ACTION_CONST_HPP

#include "CCF/IDL2/SemanticAction/Elements.hpp"

namespace CCF
{
  namespace IDL2
  {
    namespace SemanticAction
    {
      struct Const
      {
        virtual ~Const ()
        {
        }
        
        virtual void
        begin (IdentifierPtr const& type,
               SimpleIdentifierPtr const& name) = 0;

        virtual void
        expr () = 0;
      };
    }
  }
}

#endif  // CCF_IDL2_SEMANTIC_ACTION_CONST_HPP
