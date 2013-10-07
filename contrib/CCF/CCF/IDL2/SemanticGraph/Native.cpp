// file      : CCF/IDL2/SemanticGraph/Native.cpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Native.cpp 72251 2006-04-21 16:29:20Z wotte $

#include "CCF/IDL2/SemanticGraph/Native.hpp"

namespace CCF
{
  namespace IDL2
  {
    namespace SemanticGraph
    {
      using Introspection::TypeInfo;
      using Introspection::Access;

      namespace
      {
        TypeInfo
        native_init_ ()
        {
          TypeInfo ti (typeid (Native));
          ti.add_base (Access::PUBLIC, true, Type::static_type_info ());
          return ti;
        }

        TypeInfo native_ (native_init_ ());
      }

      TypeInfo const& Native::
      static_type_info () { return native_; }
    }
  }
}
