// -*- C++ -*-

//=============================================================================
/**
 * @file      Probe_Schema_Generator.h
 *
 *  $Id: Schema_Type_Generator.h 1896 2011-09-07 14:56:19Z hillj $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_SCHEMA_TYPE_GENERATOR_H_
#define _OASIS_PDL_SCHEMA_TYPE_GENERATOR_H_

#include "Probe_Schema_Generator_export.h"
#include "fe/PDL_Visitor.h"
#include <iosfwd>

/**
 * @class OASIS_PDL_Schema_Type_Generator
 *
 * Visitor responsible for generating the XML Schema Type for
 * a given PDL type.
 */
class OASIS_PDL_SCHEMA_GENERATOR_Export OASIS_PDL_Schema_Type_Generator :
  public OASIS_PDL_Visitor
{
public:
  /**
   * Initializing constuctor.
   *
   * @param[in]           out         Target output stream
   */
  OASIS_PDL_Schema_Type_Generator (std::ostream & out);

  /// Destructor.
  virtual ~OASIS_PDL_Schema_Type_Generator (void);

  // Visit a probe type.
  virtual void visit_probe (const OASIS_PDL_Probe & probe);

  // Visit a struct element.
  virtual void visit_struct (const OASIS_PDL_Struct & s);

  // Visit a simple type element.
  virtual void visit_simple_type (const OASIS_PDL_Simple_Type & s);

  // Visit a vector type element.
  virtual void visit_vector_type (const OASIS_PDL_Vector_Type & v);

private:
  /// Target output stream.
  std::ostream & out_;
};

#endif  // !defined  _OASIS_PDL_SCHEMA_TYPE_GENERATOR_H_
