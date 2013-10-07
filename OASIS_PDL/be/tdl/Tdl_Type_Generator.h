// -*- C++ -*-

//=============================================================================
/**
 * @file      Tdl_Type_Generator.h
 *
 *  $Id: Tdl_Type_Generator.h 1768 2011-03-01 01:04:39Z hillj $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_TDL_TYPE_GENERATOR_H_
#define _OASIS_PDL_TDL_TYPE_GENERATOR_H_

#include "fe/PDL_Visitor.h"
#include "Tdl_Stream.h"

/**
 * @class OASIS_PDL_Tdl_Type_Generator
 *
 * Visitor responsible for generating the XML Schema Type for
 * a given PDL type.
 */
class OASIS_PDL_Tdl_Type_Generator :
  public OASIS_PDL_Visitor
{
public:
  /**
   * Initializing constuctor.
   *
   * @param[in]           out         Target output stream
   */
  OASIS_PDL_Tdl_Type_Generator (Tdl_Stream & out);

  /// Destructor.
  virtual ~OASIS_PDL_Tdl_Type_Generator (void);

  // Visit a probe type.
  virtual void visit_probe (const OASIS_PDL_Probe & probe);

  // Visit a struct element.
  virtual void visit_struct (const OASIS_PDL_Struct & s);

  // Visit a simple type element.
  virtual void visit_simple_type (const OASIS_PDL_Simple_Type & s);

private:
  /// Target output stream.
  Tdl_Stream & tdl_;
};

#endif  // !defined  _OASIS_PDL_SCHEMA_TYPE_GENERATOR_H_
