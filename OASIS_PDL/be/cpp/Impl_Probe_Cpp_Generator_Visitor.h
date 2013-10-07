// -*- C++ -*-

//=============================================================================
/**
 * @file      Impl_Probe_Cpp_Generator_Visitor.h
 *
 * $Id: Impl_Probe_Cpp_Generator_Visitor.h 2211 2012-07-25 12:55:51Z dfeiock $
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_IMPL_PROBE_CPP_GENERATOR_VISITOR_H_
#define _OASIS_PDL_IMPL_PROBE_CPP_GENERATOR_VISITOR_H_

#include <iosfwd>

#include "fe/PDL_Visitor.h"

/**
 * @class OASIS_PDL_Impl_Probe_Cpp_Generator
 */
class OASIS_PDL_Impl_Probe_Cpp_Generator_Visitor :
  public OASIS_PDL_Visitor
{
public:
  /// Default constructor.
  OASIS_PDL_Impl_Probe_Cpp_Generator_Visitor (std::ostream & hfile,
                                         std::ostream & cppfile);

  /// Destructor.
  virtual ~OASIS_PDL_Impl_Probe_Cpp_Generator_Visitor (void);

  virtual void visit_file (const OASIS_PDL_File & file);

  virtual void visit_module (const OASIS_PDL_Module & module);

  virtual void visit_probe (const OASIS_PDL_Probe & probe);

  virtual void visit_struct (const OASIS_PDL_Struct & s);

private:
  void generate_impl (const OASIS_PDL_Probe & probe);

  /// The header file's output stream.
  std::ostream & hfile_;

  /// The source file's output stream.
  std::ostream & cppfile_;
};

#endif  // !defined _OASIS_PDL_IMPL_PROBE_CPP_GENERATOR_VISITOR_H_
