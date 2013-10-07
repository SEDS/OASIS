// file      : CCF/IDL2/SemanticGraph/Module.hpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Module.hpp 74499 2006-09-22 10:02:37Z boris $

#ifndef CCF_IDL2_SEMANTIC_GRAPH_MODULE_HPP
#define CCF_IDL2_SEMANTIC_GRAPH_MODULE_HPP

#include "CCF/IDL2/SemanticGraph/Elements.hpp"

namespace CCF
{
  namespace IDL2
  {
    namespace SemanticGraph
    {
      class Module : public virtual Scope
      {
      public:
        static Introspection::TypeInfo const&
        static_type_info ();

      protected:
        friend class Graph<Node, Edge>;

        Module (Path const& path, unsigned long line)
            : Node (path, line)
        {
          type_info (static_type_info ());
        }
      };
    }
  }
}

#endif  // CCF_IDL2_SEMANTIC_GRAPH_MODULE_HPP
