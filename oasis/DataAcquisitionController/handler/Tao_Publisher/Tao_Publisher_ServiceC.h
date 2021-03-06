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
// .\be\be_codegen.cpp:152

#ifndef _TAO_IDL_TAO_PUBLISHER_SERVICEC_PNF6GE_H_
#define _TAO_IDL_TAO_PUBLISHER_SERVICEC_PNF6GE_H_

#include /**/ "ace/pre.h"


#include /**/ "ace/config-all.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include /**/ "Tao_Publisher_Service_stub_export.h"
#include "tao/ORB.h"
#include "tao/SystemException.h"
#include "tao/Basic_Types.h"
#include "tao/ORB_Constants.h"
#include "tao/Object.h"
#include "tao/String_Manager_T.h"
#include "tao/Sequence_T.h"
#include "tao/Objref_VarOut_T.h"
#include "tao/Seq_Var_T.h"
#include "tao/Seq_Out_T.h"
#include "tao/VarOut_T.h"
#include "tao/Arg_Traits_T.h"
#include "tao/Basic_Arguments.h"
#include "tao/Special_Basic_Arguments.h"
#include "tao/Any_Insert_Policy_T.h"
#include "tao/Fixed_Size_Argument_T.h"
#include "tao/Var_Size_Argument_T.h"
#include "tao/Object_Argument_T.h"
#include "tao/UB_String_Arguments.h"
#include /**/ "tao/Version.h"
#include /**/ "tao/Versioned_Namespace.h"

#include "oasis/DataAcquisitionController/Remote_ServiceC.h"
#include "oasis/middleware/tao/Data_Channel/CommandChannelC.h"
#include "oasis/middleware/tao/OASIS_UUIDC.h"

#if TAO_MAJOR_VERSION != 2 || TAO_MINOR_VERSION != 1 || TAO_BETA_VERSION != 2
#error This file should be regenerated with TAO_IDL
#endif

#if defined (TAO_EXPORT_MACRO)
#undef TAO_EXPORT_MACRO
#endif
#define TAO_EXPORT_MACRO OASIS_TAO_PUBLISHER_SERVICE_STUB_Export

// TAO_IDL - Generated from
// .\be\be_visitor_root\root_ch.cpp:160
TAO_BEGIN_VERSIONED_NAMESPACE_DECL



namespace TAO
{
  template<typename T> class Narrow_Utils;
}
TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// .\be\be_visitor_module\module_ch.cpp:38

namespace OASIS
{

  // TAO_IDL - Generated from
  // .\be\be_visitor_sequence\sequence_ch.cpp:102

#if !defined (_OASIS_SOFTWAREPROBEDATA_CH_)
#define _OASIS_SOFTWAREPROBEDATA_CH_

  class SoftwareProbeData;

  typedef
    ::TAO_FixedSeq_Var_T<
        SoftwareProbeData
      >
    SoftwareProbeData_var;

  typedef
    ::TAO_Seq_Out_T<
        SoftwareProbeData
      >
    SoftwareProbeData_out;

  class OASIS_TAO_PUBLISHER_SERVICE_STUB_Export SoftwareProbeData
    : public
        ::TAO::unbounded_value_sequence<
            ::CORBA::Octet
          >
  {
  public:
    SoftwareProbeData (void);
    SoftwareProbeData ( ::CORBA::ULong max);
    SoftwareProbeData (
      ::CORBA::ULong max,
      ::CORBA::ULong length,
      ::CORBA::Octet* buffer,
      ::CORBA::Boolean release = false);
    SoftwareProbeData (const SoftwareProbeData &);
    virtual ~SoftwareProbeData (void);
    

    // TAO_IDL - Generated from
    // .\be\be_type.cpp:307

    
    typedef SoftwareProbeData_var _var_type;
    typedef SoftwareProbeData_out _out_type;

    

#if (TAO_NO_COPY_OCTET_SEQUENCES == 1)
    SoftwareProbeData (
        ::CORBA::ULong length,
        const ACE_Message_Block* mb
      )
      : ::TAO::unbounded_value_sequence< ::CORBA::Octet> (length, mb) {}
#endif /* TAO_NO_COPY_OCTET_SEQUENCE == 1 */
  };

#endif /* end #if !defined */

  // TAO_IDL - Generated from
  // .\be\be_type.cpp:261

  struct SubscriberDataPacket;

  typedef
    ::TAO_Var_Var_T<
        SubscriberDataPacket
      >
    SubscriberDataPacket_var;

  typedef
    ::TAO_Out_T<
        SubscriberDataPacket
      >
    SubscriberDataPacket_out;

  // TAO_IDL - Generated from
  // .\be\be_visitor_structure\structure_ch.cpp:51

  struct OASIS_TAO_PUBLISHER_SERVICE_STUB_Export SubscriberDataPacket
  {

    // TAO_IDL - Generated from
    // .\be\be_type.cpp:307

    
    typedef SubscriberDataPacket_var _var_type;
    typedef SubscriberDataPacket_out _out_type;
    
    ::CORBA::Boolean byte_order;
    OASIS::UUID einode;
    OASIS::SoftwareProbeData data;
  };

  // TAO_IDL - Generated from
  // .\be\be_interface.cpp:750

#if !defined (_OASIS_DATASUBSCRIBER__VAR_OUT_CH_)
#define _OASIS_DATASUBSCRIBER__VAR_OUT_CH_

  class DataSubscriber;
  typedef DataSubscriber *DataSubscriber_ptr;

  typedef
    TAO_Objref_Var_T<
        DataSubscriber
      >
    DataSubscriber_var;
  
  typedef
    TAO_Objref_Out_T<
        DataSubscriber
      >
    DataSubscriber_out;

#endif /* end #if !defined */

  // TAO_IDL - Generated from
  // .\be\be_visitor_interface\interface_ch.cpp:43

  class OASIS_TAO_PUBLISHER_SERVICE_STUB_Export DataSubscriber
    : public virtual ::CORBA::Object
  {
  public:
    friend class TAO::Narrow_Utils<DataSubscriber>;

    // TAO_IDL - Generated from
    // .\be\be_type.cpp:307

    typedef DataSubscriber_ptr _ptr_type;
    typedef DataSubscriber_var _var_type;
    typedef DataSubscriber_out _out_type;

    // The static operations.
    static DataSubscriber_ptr _duplicate (DataSubscriber_ptr obj);

    static void _tao_release (DataSubscriber_ptr obj);

    static DataSubscriber_ptr _narrow (::CORBA::Object_ptr obj);
    static DataSubscriber_ptr _unchecked_narrow (::CORBA::Object_ptr obj);
    static DataSubscriber_ptr _nil (void);

    virtual char * name (
      void);

    virtual void handle_data (
      const ::OASIS::SubscriberDataPacket & packet);

    // TAO_IDL - Generated from
    // .\be\be_visitor_interface\interface_ch.cpp:140

    virtual ::CORBA::Boolean _is_a (const char *type_id);
    virtual const char* _interface_repository_id (void) const;
    virtual ::CORBA::Boolean marshal (TAO_OutputCDR &cdr);
  
  protected:
    // Concrete interface only.
    DataSubscriber (void);

    // Concrete non-local interface only.
    DataSubscriber (
        ::IOP::IOR *ior,
        TAO_ORB_Core *orb_core);
    
    // Non-local interface only.
    DataSubscriber (
        TAO_Stub *objref,
        ::CORBA::Boolean _tao_collocated = false,
        TAO_Abstract_ServantBase *servant = 0,
        TAO_ORB_Core *orb_core = 0);

    virtual ~DataSubscriber (void);
  
  private:
    // Private and unimplemented for concrete interfaces.
    DataSubscriber (const DataSubscriber &);

    void operator= (const DataSubscriber &);
  };

  // TAO_IDL - Generated from
  // .\be\be_interface.cpp:750

#if !defined (_OASIS_PUBLISHERSERVICE__VAR_OUT_CH_)
#define _OASIS_PUBLISHERSERVICE__VAR_OUT_CH_

  class PublisherService;
  typedef PublisherService *PublisherService_ptr;

  typedef
    TAO_Objref_Var_T<
        PublisherService
      >
    PublisherService_var;
  
  typedef
    TAO_Objref_Out_T<
        PublisherService
      >
    PublisherService_out;

#endif /* end #if !defined */

  // TAO_IDL - Generated from
  // .\be\be_visitor_interface\interface_ch.cpp:43

  class OASIS_TAO_PUBLISHER_SERVICE_STUB_Export PublisherService
    : public virtual ::OASIS::RemoteService
  
  {
  public:
    friend class TAO::Narrow_Utils<PublisherService>;

    // TAO_IDL - Generated from
    // .\be\be_type.cpp:307

    typedef PublisherService_ptr _ptr_type;
    typedef PublisherService_var _var_type;
    typedef PublisherService_out _out_type;

    // The static operations.
    static PublisherService_ptr _duplicate (PublisherService_ptr obj);

    static void _tao_release (PublisherService_ptr obj);

    static PublisherService_ptr _narrow (::CORBA::Object_ptr obj);
    static PublisherService_ptr _unchecked_narrow (::CORBA::Object_ptr obj);
    static PublisherService_ptr _nil (void);

    virtual void register_subscriber (
      const ::OASIS::UUID & probe_uuid,
      ::OASIS::DataSubscriber_ptr subscriber);

    virtual void unregister_subscriber (
      const ::OASIS::UUID & probe_uuid,
      ::OASIS::DataSubscriber_ptr subscriber);

    // TAO_IDL - Generated from
    // .\be\be_visitor_interface\interface_ch.cpp:140

    virtual ::CORBA::Boolean _is_a (const char *type_id);
    virtual const char* _interface_repository_id (void) const;
    virtual ::CORBA::Boolean marshal (TAO_OutputCDR &cdr);
  
  protected:
    // Concrete interface only.
    PublisherService (void);

    // Concrete non-local interface only.
    PublisherService (
        ::IOP::IOR *ior,
        TAO_ORB_Core *orb_core);
    
    // Non-local interface only.
    PublisherService (
        TAO_Stub *objref,
        ::CORBA::Boolean _tao_collocated = false,
        TAO_Abstract_ServantBase *servant = 0,
        TAO_ORB_Core *orb_core = 0);

    virtual ~PublisherService (void);
  
  private:
    // Private and unimplemented for concrete interfaces.
    PublisherService (const PublisherService &);

    void operator= (const PublisherService &);
  };

// TAO_IDL - Generated from
// .\be\be_visitor_module\module_ch.cpp:67

} // module OASIS

// TAO_IDL - Generated from
// .\be\be_visitor_arg_traits.cpp:68

TAO_BEGIN_VERSIONED_NAMESPACE_DECL


// Arg traits specializations.
namespace TAO
{

  // TAO_IDL - Generated from
  // .\be\be_visitor_arg_traits.cpp:685

  template<>
  class Arg_Traits< ::OASIS::SoftwareProbeData>
    : public
        Var_Size_Arg_Traits_T<
            ::OASIS::SoftwareProbeData,
            TAO::Any_Insert_Policy_Noop
          >
  {
  };

  // TAO_IDL - Generated from
  // .\be\be_visitor_arg_traits.cpp:947

  template<>
  class Arg_Traits< ::OASIS::SubscriberDataPacket>
    : public
        Var_Size_Arg_Traits_T<
            ::OASIS::SubscriberDataPacket,
            TAO::Any_Insert_Policy_Noop
          >
  {
  };

  // TAO_IDL - Generated from
  // .\be\be_visitor_arg_traits.cpp:147

#if !defined (_OASIS_DATASUBSCRIBER__ARG_TRAITS_)
#define _OASIS_DATASUBSCRIBER__ARG_TRAITS_

  template<>
  class  Arg_Traits< ::OASIS::DataSubscriber>
    : public
        Object_Arg_Traits_T<
            ::OASIS::DataSubscriber_ptr,
            ::OASIS::DataSubscriber_var,
            ::OASIS::DataSubscriber_out,
            TAO::Objref_Traits<OASIS::DataSubscriber>,
            TAO::Any_Insert_Policy_Noop
          >
  {
  };

#endif /* end #if !defined */

  // TAO_IDL - Generated from
  // .\be\be_visitor_arg_traits.cpp:147

#if !defined (_OASIS_PUBLISHERSERVICE__ARG_TRAITS_)
#define _OASIS_PUBLISHERSERVICE__ARG_TRAITS_

  template<>
  class  Arg_Traits< ::OASIS::PublisherService>
    : public
        Object_Arg_Traits_T<
            ::OASIS::PublisherService_ptr,
            ::OASIS::PublisherService_var,
            ::OASIS::PublisherService_out,
            TAO::Objref_Traits<OASIS::PublisherService>,
            TAO::Any_Insert_Policy_Noop
          >
  {
  };

#endif /* end #if !defined */
}

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// .\be\be_visitor_traits.cpp:62

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

// Traits specializations.
namespace TAO
{

#if !defined (_OASIS_DATASUBSCRIBER__TRAITS_)
#define _OASIS_DATASUBSCRIBER__TRAITS_

  template<>
  struct OASIS_TAO_PUBLISHER_SERVICE_STUB_Export Objref_Traits< ::OASIS::DataSubscriber>
  {
    static ::OASIS::DataSubscriber_ptr duplicate (
        ::OASIS::DataSubscriber_ptr p);
    static void release (
        ::OASIS::DataSubscriber_ptr p);
    static ::OASIS::DataSubscriber_ptr nil (void);
    static ::CORBA::Boolean marshal (
        const ::OASIS::DataSubscriber_ptr p,
        TAO_OutputCDR & cdr);
  };

#endif /* end #if !defined */

#if !defined (_OASIS_PUBLISHERSERVICE__TRAITS_)
#define _OASIS_PUBLISHERSERVICE__TRAITS_

  template<>
  struct OASIS_TAO_PUBLISHER_SERVICE_STUB_Export Objref_Traits< ::OASIS::PublisherService>
  {
    static ::OASIS::PublisherService_ptr duplicate (
        ::OASIS::PublisherService_ptr p);
    static void release (
        ::OASIS::PublisherService_ptr p);
    static ::OASIS::PublisherService_ptr nil (void);
    static ::CORBA::Boolean marshal (
        const ::OASIS::PublisherService_ptr p,
        TAO_OutputCDR & cdr);
  };

#endif /* end #if !defined */
}
TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// .\be\be_visitor_sequence\cdr_op_ch.cpp:68

#if !defined _TAO_CDR_OP_OASIS_SoftwareProbeData_H_
#define _TAO_CDR_OP_OASIS_SoftwareProbeData_H_
TAO_BEGIN_VERSIONED_NAMESPACE_DECL


OASIS_TAO_PUBLISHER_SERVICE_STUB_Export ::CORBA::Boolean operator<< (
    TAO_OutputCDR &strm,
    const OASIS::SoftwareProbeData &_tao_sequence);
OASIS_TAO_PUBLISHER_SERVICE_STUB_Export ::CORBA::Boolean operator>> (
    TAO_InputCDR &strm,
    OASIS::SoftwareProbeData &_tao_sequence);

TAO_END_VERSIONED_NAMESPACE_DECL



#endif /* _TAO_CDR_OP_OASIS_SoftwareProbeData_H_ */

// TAO_IDL - Generated from
// .\be\be_visitor_structure\cdr_op_ch.cpp:46


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

OASIS_TAO_PUBLISHER_SERVICE_STUB_Export ::CORBA::Boolean operator<< (TAO_OutputCDR &, const OASIS::SubscriberDataPacket &);
OASIS_TAO_PUBLISHER_SERVICE_STUB_Export ::CORBA::Boolean operator>> (TAO_InputCDR &, OASIS::SubscriberDataPacket &);

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// .\be\be_visitor_interface\cdr_op_ch.cpp:44

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

OASIS_TAO_PUBLISHER_SERVICE_STUB_Export ::CORBA::Boolean operator<< (TAO_OutputCDR &, const OASIS::DataSubscriber_ptr );
OASIS_TAO_PUBLISHER_SERVICE_STUB_Export ::CORBA::Boolean operator>> (TAO_InputCDR &, OASIS::DataSubscriber_ptr &);

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// .\be\be_visitor_interface\cdr_op_ch.cpp:44

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

OASIS_TAO_PUBLISHER_SERVICE_STUB_Export ::CORBA::Boolean operator<< (TAO_OutputCDR &, const OASIS::PublisherService_ptr );
OASIS_TAO_PUBLISHER_SERVICE_STUB_Export ::CORBA::Boolean operator>> (TAO_InputCDR &, OASIS::PublisherService_ptr &);

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// .\be\be_codegen.cpp:1703
#if defined (__ACE_INLINE__)
#include "Tao_Publisher_ServiceC.inl"
#endif /* defined INLINE */

#include /**/ "ace/post.h"

#endif /* ifndef */

