// file      : CCF/IDL3/SemanticAction/Impl/Factory.cpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: Factory.cpp 74499 2006-09-22 10:02:37Z boris $

#include "CCF/IDL3/SemanticAction/Impl/Factory.hpp"

namespace CCF
{
  namespace IDL3
  {
    namespace SemanticAction
    {
      namespace Impl
      {
        Factory::
        Factory (CompilerElements::Context& context,
                 Diagnostic::Stream& dout,
                 SemanticGraph::TranslationUnit& tu)
            : IDL2::SemanticAction::Impl::Factory (context, dout, tu),

              component_ (ctx_),
              consumes_ (ctx_),
              emits_ (ctx_),
              event_type_ (ctx_),
              event_type_factory_ (ctx_),
              home_ (ctx_),
              home_factory_ (ctx_),
              home_finder_ (ctx_),
              include_ (ctx_, dout, *this),
              provides_ (ctx_),
              publishes_ (ctx_),
              uses_ (ctx_)
        {
        }
      }
    }
  }
}
