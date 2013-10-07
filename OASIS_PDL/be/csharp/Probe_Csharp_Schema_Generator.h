// -*- C++ -*-

//=============================================================================
/**
 * @file      Probe_Csharp_Schema_Generator.h
 *
 * $Id: Probe_Csharp_Schema_Generator.h 2118 2012-01-13 20:29:17Z dpuranik $
 *
 * @author    Darshan Puranik
 */
//=============================================================================

#ifndef _OASIS_PDL_PROBE_CSHARP_SCHEMA_GENERATOR_H_
#define _OASIS_PDL_PROBE_CSHARP_SCHEMA_GENERATOR_H_

#include "fe/PDL_Visitor.h"
#include <ostream>

/**
 * @class OASIS_PDL_Probe_Schema_Generator
 */
class OASIS_PDL_Probe_Csharp_Schema_Generator :
  public OASIS_PDL_Visitor
{
public:
  /// Default constructor.
  OASIS_PDL_Probe_Csharp_Schema_Generator (std::ostream & csfile);

  /// Destructor.
  virtual ~OASIS_PDL_Probe_Csharp_Schema_Generator (void);

  virtual void visit_probe (const OASIS_PDL_Probe & probe);

  virtual void visit_struct (const OASIS_PDL_Struct & s);

  virtual void visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m);

private:
  /// Help method to generate a complex type.
  void visit_complex_type (const OASIS_PDL_Complex_Type & t);

  void complex_type_begin (const OASIS_PDL_Complex_Type & t);
  void complex_type_end (void);

  /// Target output stream.
  std::ostream & csfile_;

  /// Flag dictating inner probe generation.
  bool inner_probe_;

  /// Flag dictating the generation is inside a complex type
  bool in_complex_;
};

#endif  // !defined _OASIS_PDL_PROBE_CSHARP_SCHEMA_GENERATOR_H_
