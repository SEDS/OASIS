// -*- C++ -*-

//=============================================================================
/**
 * @file      Probe_Csharp_Generator_Visitor.h
 *
 * $Id: Probe_Csharp_Generator_Visitor.h 2118 2012-01-13 20:29:17Z dpuranik $
 *
 * @author    Darshan Puranik
 */
//=============================================================================

#ifndef _OASIS_PDL_PROBE_Csharp_GENERATOR_VISITOR_H_
#define _OASIS_PDL_PROBE_Csharp_GENERATOR_VISITOR_H_

#include <iosfwd>

#include "fe/PDL_Visitor.h"

/**
 * @class OASIS_PDL_Probe_Cpp_Generator
 */
class OASIS_PDL_Probe_Csharp_Generator_Visitor :
  public OASIS_PDL_Visitor
{
public:
  /// Default constructor.
  OASIS_PDL_Probe_Csharp_Generator_Visitor (std::ostream & csfile);

  /// Destructor.
  virtual ~OASIS_PDL_Probe_Csharp_Generator_Visitor (void);

  virtual void visit_file (const OASIS_PDL_File & file);

  virtual void visit_module (const OASIS_PDL_Module & module);

  virtual void visit_probe (const OASIS_PDL_Probe & probe);

  virtual void visit_struct (const OASIS_PDL_Struct & s);

private:
  void generate_stub (const OASIS_PDL_Probe & probe);
  void generate_impl (const OASIS_PDL_Probe & probe);

  /// The source file's output stream.
  std::ostream & csfile_;
};

#endif  // !defined _OASIS_PDL_PROBE_Csharp_GENERATOR_VISITOR_H_
