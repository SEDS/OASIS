// file      : CCF/IDL2/Traversal/Struct.cpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Struct.cpp 54723 2003-12-22 22:26:40Z boris $

#include "CCF/IDL2/Traversal/Struct.hpp"

namespace CCF
{
  namespace IDL2
  {
    namespace Traversal
    {
      void Struct::
      traverse (Type& s)
      {
        pre (s);
        name (s);
        names (s);
        post (s);
      }

      void Struct::
      pre (Type&)
      {
      }

      void Struct::
      name (Type&)
      {
      }

      void Struct::
      post (Type&)
      {
      }
    }
  }
}
