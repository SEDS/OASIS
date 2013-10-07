// -*- C++ -*-

//=============================================================================
/**
 * @file      Tdl_Probe_Generator.h
 *
 * $Id: Tdl_Probe_Generator.h 2235 2013-02-06 20:18:09Z dfeiock $
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TDL_PROBE_GENERATOR_VISITOR_H_
#define _OASIS_TDL_PROBE_GENERATOR_VISITOR_H_

#include "fe/PDL_Visitor.h"
#include "Tdl_Stream.h"

/**
 * @class OASIS_PDL_Tdl_Probe_Generator
 *
 * Visitor that is responsible for generating the contents of a
 * TDL file based on the provided PDL.
 */
class OASIS_PDL_Tdl_Probe_Generator :
  public OASIS_PDL_Visitor
{
public:
  /// Default constructor.
  OASIS_PDL_Tdl_Probe_Generator (std::ostream & out);

  /// Destructor.
  virtual ~OASIS_PDL_Tdl_Probe_Generator (void);

  // Visit a file element.
  virtual void visit_file (const OASIS_PDL_File & file);

  // Visit a module element.
  virtual void visit_module (const OASIS_PDL_Module & module);

  // Visit a probe element.
  virtual void visit_probe (const OASIS_PDL_Probe & probe);

  // Visit a complex type member.
  virtual void visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m);

private:
  /// Target TDL output stream.
  Tdl_Stream tdl_;
};

#endif  // !defined _OASIS_PDL_PROBE_SCHEMA_GENERATOR_VISITOR_H_
