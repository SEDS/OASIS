// -*- C++ -*-

//=============================================================================
/**
 *  @file       PDL_Visitor.h
 *
 *  $Id: PDL_Visitor.h 1896 2011-09-07 14:56:19Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_VISITOR_H_
#define _OASIS_PDL_VISITOR_H_

#include "PDL_FE_export.h"
#include "oasis/config.h"

// Forward decl.
class OASIS_PDL_Complex_Type;
class OASIS_PDL_Complex_Type_Member;
class OASIS_PDL_File;
class OASIS_PDL_Module;
class OASIS_PDL_Probe;
class OASIS_PDL_Struct;
class OASIS_PDL_Simple_Type;
class OASIS_PDL_Vector_Type;

/**
 * @class OASIS_PDL_Visitor
 *
 * Base class for all visitor class types.
 */
class OASIS_PDL_FE_Export OASIS_PDL_Visitor
{
public:
  /// Default constructor.
  OASIS_PDL_Visitor (void);

  /// Destructor.
  virtual ~OASIS_PDL_Visitor (void);

  virtual void visit_file (const OASIS_PDL_File & file);

  virtual void visit_module (const OASIS_PDL_Module & module);

  virtual void visit_probe (const OASIS_PDL_Probe & probe);

  virtual void visit_struct (const OASIS_PDL_Struct & s);

  virtual void visit_simple_type (const OASIS_PDL_Simple_Type & s);

  virtual void visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m);

  virtual void visit_vector_type (const OASIS_PDL_Vector_Type & v);
};

#if defined (__OASIS_INLINE__)
#include "PDL_Visitor.inl"
#endif

#endif  // !defined _OASIS_PDL_VISITOR_H_
