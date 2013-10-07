// file      : CCF/IDL2/Traversal/Exception.cpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Exception.cpp 54723 2003-12-22 22:26:40Z boris $

#include "CCF/IDL2/Traversal/Exception.hpp"

namespace CCF
{
  namespace IDL2
  {
    namespace Traversal
    {
      void Exception::
      traverse (Type& s)
      {
        pre (s);
        name (s);
        names (s);
        post (s);
      }

      void Exception::
      pre (Type&)
      {
      }

      void Exception::
      name (Type&)
      {
      }

      void Exception::
      post (Type&)
      {
      }
    }
  }
}
