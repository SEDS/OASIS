// -*- C++ -*-

//=============================================================================
/**
 * @file      Flush_Generator.h
 *
 *  $Id: Recall_Generator.h 2213 2012-08-01 14:05:58Z dfeiock $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_BE_CPP_RECALL_GENERATOR_H_
#define _OASIS_PDL_BE_CPP_RECALL_GENERATOR_H_

#include "fe/PDL_Visitor.h"
#include <ostream>

namespace OASIS_PDL_BE
{
namespace Cpp
{

/**
 * @class Flush_Generator
 *
 * Visitor that generates the packaging implementation.
 */
class Recall_Generator : public OASIS_PDL_Visitor
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       out       Target output stream.
   */
  Recall_Generator (std::ostream & hfile, std::ostream & cppfile);

  /// Destructor.
  virtual ~Recall_Generator (void);

  virtual void visit_probe (const OASIS_PDL_Probe & p);

  virtual void visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & );

  virtual void visit_struct (const OASIS_PDL_Struct & s);

  virtual void visit_simple_type (const OASIS_PDL_Simple_Type & s);

  virtual void visit_vector_type (const OASIS_PDL_Vector_Type & v);

private:
  /// Target source file stream.
  std::ostream & hfile_;

  /// Target source file stream.
  std::ostream & cppfile_;

  /// We are generating types for probes.
  bool is_probe_;

  /// Name of the vector which we are visiting
  std::string vector_name_;
};

}
}

#endif  // !defined _OASIS_PDL_BE_CPP_VAR_TYPE_GENERATOR_H_
