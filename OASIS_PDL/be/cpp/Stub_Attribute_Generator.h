// -*- C++ -*-

//=============================================================================
/**
 * @file      Stub_Attribute_Generator.h
 *
 *  $Id: Stub_Attribute_Generator.h 2211 2012-07-25 12:55:51Z dfeiock $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_BE_CPP_STUB_ATTRIBUTE_GENERATOR_H_
#define _OASIS_PDL_BE_CPP_STUB_ATTRIBUTE_GENERATOR_H_

#include "fe/PDL_Visitor.h"
#include <ostream>

namespace OASIS_PDL_BE
{
namespace Cpp
{

/**
 * @class Stub_Attribute_Generator
 *
 * Visitor that generates a variable's type declaration.
 */
class Stub_Attribute_Generator : public OASIS_PDL_Visitor
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       out       Target output stream.
   */
  Stub_Attribute_Generator (std::ostream & hfile, std::ostream & cppfile);

  /// Destructor.
  virtual ~Stub_Attribute_Generator (void);

  virtual void visit_probe (const OASIS_PDL_Probe & p);

  virtual void visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & );

  virtual void visit_simple_type (const OASIS_PDL_Simple_Type & s);

  virtual void visit_struct (const OASIS_PDL_Struct & s);

  virtual void visit_vector_type (const OASIS_PDL_Vector_Type & v);

private:
  /// The parent probe.
  const OASIS_PDL_Probe * probe_;

  /// Target header file stream.
  std::ostream & hfile_;

  /// Target source file stream.
  std::ostream & cppfile_;

  std::string member_name_;
};

}
}

#endif  // !defined _OASIS_PDL_BE_CPP_VAR_TYPE_GENERATOR_H_
