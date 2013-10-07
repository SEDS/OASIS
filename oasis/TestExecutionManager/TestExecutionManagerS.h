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

#ifndef _TAO_IDL_TESTEXECUTIONMANAGERS_KJWUFU_H_
#define _TAO_IDL_TESTEXECUTIONMANAGERS_KJWUFU_H_

#include /**/ "ace/pre.h"

#include "TestExecutionManagerC.h"
#include "oasis/DataAcquisitionController/DataAcquisitionControllerS.h"
#include "tao/PortableServer/Basic_SArguments.h"
#include "tao/PortableServer/Special_Basic_SArguments.h"
#include "tao/PortableServer/Fixed_Size_SArgument_T.h"
#include "tao/PortableServer/Var_Size_SArgument_T.h"
#include "tao/PortableServer/Object_SArg_Traits.h"
#include "tao/PortableServer/UB_String_SArguments.h"
#include "tao/PortableServer/Object_SArg_Traits.h"
#include "tao/PortableServer/get_arg.h"
#include "tao/Special_Basic_Arguments.h"
#include "tao/UB_String_Arguments.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/PortableServer/PortableServer.h"
#include "tao/PortableServer/Servant_Base.h"

#include /**/ "TestExecutionManager_skel_export.h"

#if defined (TAO_EXPORT_MACRO)
#undef TAO_EXPORT_MACRO
#endif
#define TAO_EXPORT_MACRO OASIS_TESTEXECUTIONMANAGER_SKEL_Export

// TAO_IDL - Generated from
// .\be\be_visitor_arg_traits.cpp:68

TAO_BEGIN_VERSIONED_NAMESPACE_DECL


// Arg traits specializations.
namespace TAO
{

  // TAO_IDL - Generated from
  // .\be\be_visitor_arg_traits.cpp:685

  template<>
  class SArg_Traits< ::OASIS::DataAcquisitionControllerSeq>
    : public
        Var_Size_SArg_Traits_T<
            ::OASIS::DataAcquisitionControllerSeq,
            TAO::Any_Insert_Policy_Noop
          >
  {
  };

  // TAO_IDL - Generated from
  // .\be\be_visitor_arg_traits.cpp:147

#if !defined (_OASIS_TESTEXECUTIONMANAGERVIEWER__SARG_TRAITS_)
#define _OASIS_TESTEXECUTIONMANAGERVIEWER__SARG_TRAITS_

  template<>
  class  SArg_Traits< ::OASIS::TestExecutionManagerViewer>
    : public
        Object_SArg_Traits_T<
            ::OASIS::TestExecutionManagerViewer_ptr,
            ::OASIS::TestExecutionManagerViewer_var,
            ::OASIS::TestExecutionManagerViewer_out,
            TAO::Any_Insert_Policy_Noop
          >
  {
  };

#endif /* end #if !defined */

  // TAO_IDL - Generated from
  // .\be\be_visitor_arg_traits.cpp:147

#if !defined (_OASIS_TESTEXECUTIONMANAGER__SARG_TRAITS_)
#define _OASIS_TESTEXECUTIONMANAGER__SARG_TRAITS_

  template<>
  class  SArg_Traits< ::OASIS::TestExecutionManager>
    : public
        Object_SArg_Traits_T<
            ::OASIS::TestExecutionManager_ptr,
            ::OASIS::TestExecutionManager_var,
            ::OASIS::TestExecutionManager_out,
            TAO::Any_Insert_Policy_Noop
          >
  {
  };

#endif /* end #if !defined */
}

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// .\be\be_visitor_module\module_sh.cpp:38

namespace POA_OASIS
{
  

  // TAO_IDL - Generated from
  // .\be\be_visitor_interface\interface_sh.cpp:76

  class TestExecutionManagerViewer;
  typedef TestExecutionManagerViewer *TestExecutionManagerViewer_ptr;

  class OASIS_TESTEXECUTIONMANAGER_SKEL_Export TestExecutionManagerViewer
    : public virtual PortableServer::ServantBase
  {
  protected:
    TestExecutionManagerViewer (void);
  
  public:
    /// Useful for template programming.
    typedef ::OASIS::TestExecutionManagerViewer _stub_type;
    typedef ::OASIS::TestExecutionManagerViewer_ptr _stub_ptr_type;
    typedef ::OASIS::TestExecutionManagerViewer_var _stub_var_type;

    TestExecutionManagerViewer (const TestExecutionManagerViewer& rhs);
    virtual ~TestExecutionManagerViewer (void);

    virtual ::CORBA::Boolean _is_a (const char* logical_type_id);

    virtual void _dispatch (
        TAO_ServerRequest & req,
        TAO::Portable_Server::Servant_Upcall *servant_upcall);
    
    ::OASIS::TestExecutionManagerViewer *_this (void);
    
    virtual const char* _interface_repository_id (void) const;

    // TAO_IDL - Generated from
    // .\be\be_visitor_operation\operation_sh.cpp:39

    virtual char * name (
      void) = 0;

    static void _get_name_skel (
        TAO_ServerRequest &server_request,
        TAO::Portable_Server::Servant_Upcall *servant_upcall,
        TAO_ServantBase *servant);

    // TAO_IDL - Generated from
    // .\be\be_visitor_operation\operation_sh.cpp:39

    virtual ::OASIS::DataAcquisitionControllerSeq * get_DACs (
      void) = 0;

    static void get_DACs_skel (
        TAO_ServerRequest &server_request,
        TAO::Portable_Server::Servant_Upcall *servant_upcall,
        TAO_ServantBase *servant);

    // TAO_IDL - Generated from
    // .\be\be_visitor_operation\operation_sh.cpp:39

    virtual ::OASIS::DataAcquisitionController_ptr get_DAC (
      const char * name) = 0;

    static void get_DAC_skel (
        TAO_ServerRequest &server_request,
        TAO::Portable_Server::Servant_Upcall *servant_upcall,
        TAO_ServantBase *servant);
  };

  // TAO_IDL - Generated from
  // .\be\be_visitor_interface\interface_sh.cpp:76

  class TestExecutionManager;
  typedef TestExecutionManager *TestExecutionManager_ptr;

  class OASIS_TESTEXECUTIONMANAGER_SKEL_Export TestExecutionManager
    : public virtual POA_OASIS::TestExecutionManagerViewer
  {
  protected:
    TestExecutionManager (void);
  
  public:
    /// Useful for template programming.
    typedef ::OASIS::TestExecutionManager _stub_type;
    typedef ::OASIS::TestExecutionManager_ptr _stub_ptr_type;
    typedef ::OASIS::TestExecutionManager_var _stub_var_type;

    TestExecutionManager (const TestExecutionManager& rhs);
    virtual ~TestExecutionManager (void);

    virtual ::CORBA::Boolean _is_a (const char* logical_type_id);

    virtual void _dispatch (
        TAO_ServerRequest & req,
        TAO::Portable_Server::Servant_Upcall *servant_upcall);
    
    ::OASIS::TestExecutionManager *_this (void);
    
    virtual const char* _interface_repository_id (void) const;

    // TAO_IDL - Generated from
    // .\be\be_visitor_operation\operation_sh.cpp:39

    virtual void register_DAC (
      ::OASIS::DataAcquisitionController_ptr dac) = 0;

    static void register_DAC_skel (
        TAO_ServerRequest &server_request,
        TAO::Portable_Server::Servant_Upcall *servant_upcall,
        TAO_ServantBase *servant);

    // TAO_IDL - Generated from
    // .\be\be_visitor_operation\operation_sh.cpp:39

    virtual void unregister_DAC (
      ::OASIS::DataAcquisitionController_ptr dac) = 0;

    static void unregister_DAC_skel (
        TAO_ServerRequest &server_request,
        TAO::Portable_Server::Servant_Upcall *servant_upcall,
        TAO_ServantBase *servant);
  };

// TAO_IDL - Generated from
// .\be\be_visitor_module\module_sh.cpp:69

} // module OASIS

#include /**/ "ace/post.h"

#endif /* ifndef */

