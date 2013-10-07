// -*- C++ -*-
// $Id$

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v2.1.2
 * TAO and the TAO IDL Compiler have been developed by:
 *       Center for Distributed Object Computing
 *       Washington University
 *       St. Louis, MO
 *       USA
 *       http://www.cs.wustl.edu/~schmidt/doc-center.html
 * and
 *       Distributed Object Computing Laboratory
 *       University of California at Irvine
 *       Irvine, CA
 *       USA
 * and
 *       Institute for Software Integrated Systems
 *       Vanderbilt University
 *       Nashville, TN
 *       USA
 *       http://www.isis.vanderbilt.edu/
 *
 * Information about TAO is available at:
 *     http://www.cs.wustl.edu/~schmidt/TAO.html
 **/

// TAO_IDL - Generated from
// .\be\be_codegen.cpp:461

#ifndef _TAO_IDL_OASIS_COMMONS_OH1WKN_H_
#define _TAO_IDL_OASIS_COMMONS_OH1WKN_H_

#include /**/ "ace/pre.h"

#include "OASIS_CommonC.h"
#include "tao/PortableServer/Basic_SArguments.h"
#include "tao/PortableServer/Special_Basic_SArguments.h"
#include "tao/PortableServer/Fixed_Size_SArgument_T.h"
#include "tao/PortableServer/Var_Size_SArgument_T.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include /**/ "OASIS_Tao_skel_export.h"

#if defined (TAO_EXPORT_MACRO)
#undef TAO_EXPORT_MACRO
#endif
#define TAO_EXPORT_MACRO OASIS_TAO_SKEL_Export

// TAO_IDL - Generated from
// .\be\be_visitor_arg_traits.cpp:68

TAO_BEGIN_VERSIONED_NAMESPACE_DECL


// Arg traits specializations.
namespace TAO
{

  // TAO_IDL - Generated from
  // .\be\be_visitor_arg_traits.cpp:685

  template<>
  class SArg_Traits< ::OASIS::CharStream>
    : public
        Var_Size_SArg_Traits_T<
            ::OASIS::CharStream,
            TAO::Any_Insert_Policy_Noop
          >
  {
  };

  // TAO_IDL - Generated from
  // .\be\be_visitor_arg_traits.cpp:685

  template<>
  class SArg_Traits< ::OASIS::BinaryStream>
    : public
        Var_Size_SArg_Traits_T<
            ::OASIS::BinaryStream,
            TAO::Any_Insert_Policy_Noop
          >
  {
  };

  // TAO_IDL - Generated from
  // .\be\be_visitor_arg_traits.cpp:947

  template<>
  class SArg_Traits< ::OASIS::TimeStamp>
    : public
        Fixed_Size_SArg_Traits_T<
            ::OASIS::TimeStamp,
            TAO::Any_Insert_Policy_Noop
          >
  {
  };
}

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// .\be\be_visitor_module\module_sh.cpp:38

namespace POA_OASIS
{
  

// TAO_IDL - Generated from
// .\be\be_visitor_module\module_sh.cpp:69

} // module OASIS

#include /**/ "ace/post.h"

#endif /* ifndef */

