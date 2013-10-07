// file      : Test/IDL3/Compiler/Generator.cpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Generator.cpp 54723 2003-12-22 22:26:40Z boris $

#include "Generator.hpp"
#include "GeneratorImpl.hpp"

namespace IDL3
{
  Generator::
  ~Generator ()
  {
  }

  Generator::
  Generator ()
      : pimpl_ (new GeneratorImpl), impl_ (*pimpl_)
  {
  }

  Generator::
  Generator (GeneratorImpl& gi)
      : pimpl_ (), impl_ (gi)
  {
  }

  void Generator::
  generate (CCF::IDL3::SemanticGraph::TranslationUnit& tu)
  {
    impl_.generate (tu);
  }
}
