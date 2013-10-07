// file      : CCF/IDL2/SemanticGraph/Native.hpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Native.hpp 74499 2006-09-22 10:02:37Z boris $

#ifndef CCF_IDL2_SEMANTIC_GRAPH_NATIVE_HPP
#define CCF_IDL2_SEMANTIC_GRAPH_NATIVE_HPP

#include "CCF/IDL2/SemanticGraph/Elements.hpp"

namespace CCF
{
  namespace IDL2
  {
    namespace SemanticGraph
    {
      class Native : public virtual Type
      {
      public:
        virtual bool
        complete () const
        {
          return true;
        }

        static Introspection::TypeInfo const&
        static_type_info ();

      protected:
        friend class Graph<Node, Edge>;

        Native (Path const& path, unsigned long line)
            : Node (path, line)
        {
          type_info (static_type_info ());
        }
      };
    }
  }
}

#endif  // CCF_IDL2_SEMANTIC_GRAPH_NATIVE_HPP
