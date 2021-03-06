divert(-1)

# file      : CCF/IDL2/SemanticGraph/Fundamental.hpp.m4
# author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
# cvs-id    : $Id: Fundamental.hpp.m4 74499 2006-09-22 10:02:37Z boris $

include(`Fundamental.m4')

define(`fundamental_type', `fundamental_type_impl(`make_class_name(`$1')', `$1')')

define(`fundamental_type_impl', `

      //
      //
      //
      class $1 : public virtual FundamentalType
      {
      public:
        static Introspection::TypeInfo const&
        static_type_info ();

      protected:
        friend class Graph<Node, Edge>;

        $1 (Path const& path, unsigned long line)
            : Node (path, line)
        {
          type_info (static_type_info ());
        }
      };')
divert(0)dnl
dnl
dnl
dnl
// file      : CCF/IDL2/SemanticGraph/Fundamental.hpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Fundamental.hpp.m4 74499 2006-09-22 10:02:37Z boris $

// Note, that this file is automatically generated!
//

#ifndef CCF_IDL2_SEMANTIC_GRAPH_FUNDAMENTAL_HPP
#define CCF_IDL2_SEMANTIC_GRAPH_FUNDAMENTAL_HPP

#include "CCF/IDL2/SemanticGraph/Elements.hpp"

namespace CCF
{
  namespace IDL2
  {
    namespace SemanticGraph
    {
      // @@ Object & ValueBase should be of interface & valuetype types?
      //
      //
      class FundamentalType : public virtual Type
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
        FundamentalType () // For virtual inheritance only.
        {
          type_info (static_type_info ());
        }

        virtual
        ~FundamentalType () = 0;
      };
dnl
fundamental_type(`Object')
fundamental_type(`ValueBase')
fundamental_type(`any')
fundamental_type(`boolean')
fundamental_type(`char')
fundamental_type(`double')
fundamental_type(`float')
fundamental_type(`long')
fundamental_type(`long double')
fundamental_type(`long long')
fundamental_type(`octet')
fundamental_type(`short')
fundamental_type(`string')
fundamental_type(`unsigned long')
fundamental_type(`unsigned long long')
fundamental_type(`unsigned short')
fundamental_type(`void')
fundamental_type(`wchar')
fundamental_type(`wstring')
dnl
    }
  }
}

#endif  // CCF_IDL2_SEMANTIC_GRAPH_FUNDAMENTAL_HPP
