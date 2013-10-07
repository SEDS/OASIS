// -*- C++ -*-

//=============================================================================
/**
 * @file      Attribute_Generator.h
 *
 *  $Id: Attribute_Generator.h 2118 2012-01-13 20:29:17Z dpuranik $
 *
 *  @author   Darshan Puranik
 */
//=============================================================================

#ifndef _OASIS_PDL_BE_CSHARP_ATTRIBUTE_GENERATOR_H_
#define _OASIS_PDL_BE_CSHARP_ATTRIBUTE_GENERATOR_H_

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
class Attribute_Generator : public OASIS_PDL_Visitor
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       out       Target output stream.
   */
  Attribute_Generator (std::ostream & csfile);

  /// Destructor.
  virtual ~Attribute_Generator (void);

  virtual void visit_probe (const OASIS_PDL_Probe & p);

  virtual void visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & );

  virtual void visit_simple_type (const OASIS_PDL_Simple_Type & s);

  virtual void visit_struct (const OASIS_PDL_Struct & s);

private:
  /// The parent probe.
  const OASIS_PDL_Probe * probe_;

  /// Target source file stream.
  std::ostream & csfile_;

  std::string member_name_;
};

}
}

#endif  // !defined _OASIS_PDL_BE_CSHARP_ATTRIBUTE_GENERATOR_H_
