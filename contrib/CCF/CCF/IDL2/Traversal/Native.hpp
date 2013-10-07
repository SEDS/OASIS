// file      : CCF/IDL2/Traversal/Native.hpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Native.hpp 54957 2003-12-30 23:13:30Z boris $

#ifndef CCF_IDL2_TRAVERSAL_NATIVE_HPP
#define CCF_IDL2_TRAVERSAL_NATIVE_HPP

#include "CCF/IDL2/Traversal/Elements.hpp"
#include "CCF/IDL2/SemanticGraph/Native.hpp"

namespace CCF
{
  namespace IDL2
  {
    namespace Traversal
    {
      typedef
      Node<SemanticGraph::Native>
      Native;
    }
  }
}

#endif  // CCF_IDL2_TRAVERSAL_NATIVE_HPP
