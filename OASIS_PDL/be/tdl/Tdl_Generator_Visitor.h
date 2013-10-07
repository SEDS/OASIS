// -*- C++ -*-

//=============================================================================
/**
 * @file      Probe_Schema_Generator.h
 *
 * $Id: Tdl_Generator_Visitor.h 1824 2011-08-10 14:42:58Z hillj $
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_PROBE_SCHEMA_GENERATOR_VISITOR_H_
#define _OASIS_PDL_PROBE_SCHEMA_GENERATOR_VISITOR_H_

#include "fe/PDL_Visitor.h"

/**
 * @class OASIS_PDL_Tdl_Generator_Visitor
 *
 * Visitor that is responsible for generating the contents of a
 * TDL file based on the provided PDL.
 */
class OASIS_PDL_Tdl_Generator_Visitor : public OASIS_PDL_Visitor
{
public:
  /// Default constructor.
  OASIS_PDL_Tdl_Generator_Visitor (void);

  /// Destructor.
  virtual ~OASIS_PDL_Tdl_Generator_Visitor (void);

  // Visit a file element.
  virtual void visit_file (const OASIS_PDL_File & file);
};

#if defined (__OASIS_INLINE__)
#include "Tdl_Generator_Visitor.inl"
#endif

#endif  // !defined _OASIS_PDL_PROBE_SCHEMA_GENERATOR_VISITOR_H_
