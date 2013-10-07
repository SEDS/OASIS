// file      : CCF/IDL2/Traversal/Member.cpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Member.cpp 54723 2003-12-22 22:26:40Z boris $

#include "CCF/IDL2/Traversal/Member.hpp"

namespace CCF
{
  namespace IDL2
  {
    namespace Traversal
    {
      void Member::
      traverse (Type& m)
      {
        pre (m);
        belongs (m);
        name (m);
        post (m);
      }

      void Member::
      pre (Type&)
      {
      }

      void Member::
      belongs (Type& m, EdgeDispatcherBase& d)
      {
        d.traverse (m.belongs ());
      }

      void Member::
      belongs (Type& m)
      {
        belongs (m, edge_traverser ());
      }

      void Member::
      name (Type&)
      {
      }

      void Member::
      post (Type&)
      {
      }
    }
  }
}
