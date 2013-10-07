// -*- C++ -*-

//=============================================================================
/**
 * @file      Metadata_Cpp_Generator_Visitor.h
 *
 * $Id: Metadata_Cpp_Generator_Visitor.h 2250 2013-09-07 19:38:37Z hillj $
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_METADATA_CPP_GENERATOR_VISITOR_H_
#define _OASIS_PDL_METADATA_CPP_GENERATOR_VISITOR_H_

#include <iosfwd>

#include "fe/PDL_Visitor.h"

/**
 * @class OASIS_PDL_Metadata_Cpp_Generator
 */
class OASIS_PDL_Metadata_Cpp_Generator_Visitor :
  public OASIS_PDL_Visitor
{
public:
  /// Default constructor.
  OASIS_PDL_Metadata_Cpp_Generator_Visitor (std::ostream & hfile,
                                            std::ostream & cppfile);

  /// Destructor.
  virtual ~OASIS_PDL_Metadata_Cpp_Generator_Visitor (void);

  virtual void visit_file (const OASIS_PDL_File & file);

  virtual void visit_module (const OASIS_PDL_Module & module);

  virtual void visit_probe (const OASIS_PDL_Probe & probe);

private:
  /// The header file's output stream.
  std::ostream & hfile_;

  /// The source file's output stream.
  std::ostream & cppfile_;
};

#endif  // !defined _OASIS_PDL_METADATA_CPP_GENERATOR_VISITOR_H_
