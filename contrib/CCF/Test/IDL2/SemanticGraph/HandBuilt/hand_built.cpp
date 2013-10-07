// file      : Test/IDL2/SemanticGraph/HandBuilt/hand_built.cpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: hand_built.cpp 80755 2008-02-27 16:09:34Z sowayaa $

#include "Builder.hpp"

using namespace CCF::IDL2;

//FUZZ: disable check_for_improper_main_declaration

int
main ()
{
  Builder b;
  SemanticGraph::TranslationUnit& tu (*b.build ());

  delete &tu;
}
