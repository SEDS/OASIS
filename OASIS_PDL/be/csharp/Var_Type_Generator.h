// -*- C++ -*-

//=============================================================================
/**
 * @file      Var_Type_Generator.h
 *
 *  $Id: Var_Type_Generator.h 2118 2012-01-13 20:29:17Z dpuranik $
 *
 *  @author   Darshan G. Puranik
 */
//=============================================================================

#ifndef _OASIS_PDL_BE_CSHARP_VAR_TYPE_GENERATOR_H_
#define _OASIS_PDL_BE_CSHARP_VAR_TYPE_GENERATOR_H_

#include "fe/PDL_Visitor.h"
#include <ostream>

namespace OASIS_PDL_BE
{
namespace Csharp
{

/**
 * @class Var_Type_Generator
 *
 * Visitor that generates a variable's type declaration.
 */
class Var_Type_Generator : public OASIS_PDL_Visitor
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       out       Target output stream.
   */
  Var_Type_Generator (std::ostream & out, bool ending = false);

  /// Destructor.
  virtual ~Var_Type_Generator (void);

  virtual void visit_struct (const OASIS_PDL_Struct & s);

  virtual void visit_simple_type (const OASIS_PDL_Simple_Type & s);

  virtual void visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m);

private:
  /// Target output stream.
  std::ostream & out_;

  bool ending_;

};

}
}

#endif  // !defined _OASIS_PDL_BE_CSHARP_VAR_TYPE_GENERATOR_H_
