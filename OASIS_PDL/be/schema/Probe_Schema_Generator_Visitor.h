// -*- C++ -*-

//=============================================================================
/**
 * @file      Probe_Schema_Generator.h
 *
 * $Id: Probe_Schema_Generator_Visitor.h 1896 2011-09-07 14:56:19Z hillj $
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_PROBE_SCHEMA_GENERATOR_VISITOR_H_
#define _OASIS_PDL_PROBE_SCHEMA_GENERATOR_VISITOR_H_

#include "fe/PDL_Visitor.h"
#include <ostream>

/**
 * @class OASIS_PDL_Probe_Schema_Generator
 */
class OASIS_PDL_Probe_Schema_Generator_Visitor :
  public OASIS_PDL_Visitor
{
public:
  /// Default constructor.
  OASIS_PDL_Probe_Schema_Generator_Visitor (std::ostream & out);

  /// Destructor.
  virtual ~OASIS_PDL_Probe_Schema_Generator_Visitor (void);

  virtual void visit_file (const OASIS_PDL_File & file);

  virtual void visit_module (const OASIS_PDL_Module & module);

  virtual void visit_probe (const OASIS_PDL_Probe & probe);

  virtual void visit_struct (const OASIS_PDL_Struct & s);

  virtual void visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m);

  virtual void visit_vector_type (const OASIS_PDL_Vector_Type & v);

private:
  void visit_complex_type (const OASIS_PDL_Complex_Type & t);

  void complex_type_begin (const OASIS_PDL_Complex_Type & t);
  void complex_type_end (void);

  std::ostream & out_;
};

#endif  // !defined _OASIS_PDL_PROBE_SCHEMA_GENERATOR_VISITOR_H_
