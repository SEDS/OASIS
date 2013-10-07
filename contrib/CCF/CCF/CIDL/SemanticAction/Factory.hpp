// file      : CCF/CIDL/SemanticAction/Factory.hpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Factory.hpp 72251 2006-04-21 16:29:20Z wotte $

#ifndef CCF_CIDL_SEMANTIC_ACTION_FACTORY_HPP
#define CCF_CIDL_SEMANTIC_ACTION_FACTORY_HPP

#include "CCF/IDL3/SemanticAction/Factory.hpp"

namespace CCF
{
  namespace CIDL
  {
    namespace SemanticAction
    {
      struct Composition;
      struct HomeExecutor;

      struct Factory : virtual IDL3::SemanticAction::Factory
      {
        virtual Composition&
        composition () = 0;

        virtual HomeExecutor&
        home_executor () = 0;
      };
    }
  }
}

#endif  // CCF_CIDL_SEMANTIC_ACTION_FACTORY_HPP
