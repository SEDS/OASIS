// file      : CCF/IDL3/LexicalAnalyzer.hpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: LexicalAnalyzer.hpp 54957 2003-12-30 23:13:30Z boris $

#ifndef CCF_IDL3_LEXICAL_ANALYZER_HPP
#define CCF_IDL3_LEXICAL_ANALYZER_HPP

#include "CCF/IDL2/LexicalAnalyzer.hpp"

namespace CCF
{
  namespace IDL3
  {
    class LexicalAnalyzer : public virtual IDL2::LexicalAnalyzer
    {
    public:
      LexicalAnalyzer (CompilerElements::TokenStream<Char>& is);
    };
  }
}

#endif  // CCF_IDL3_LEXICAL_ANALYZER_HPP
