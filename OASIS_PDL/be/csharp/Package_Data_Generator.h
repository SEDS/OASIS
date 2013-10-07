// -*- C++ -*-

//=============================================================================
/**
 * @file      Package_Data_Generator.h
 *
 *  $Id: Package_Data_Generator.h 2118 2012-01-13 20:29:17Z dpuranik $
 *
 *  @author   Darshan Puranik
 */
//=============================================================================

#ifndef _OASIS_PDL_BE_CSHARP_PACKAGE_DATA_GENERATOR_H_
#define _OASIS_PDL_BE_CSHARP_PACKAGE_DATA_GENERATOR_H_

#include "fe/PDL_Visitor.h"
#include <ostream>

namespace OASIS_PDL_BE
{
namespace Csharp
{

/**
 * @class Package_Data_Generator
 *
 * Visitor that generates the packaging implementation.
 */
class Package_Data_Generator : public OASIS_PDL_Visitor
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       out       Target output stream.
   */
  Package_Data_Generator (std::ostream & csfile);

  /// Destructor.
  virtual ~Package_Data_Generator (void);

  virtual void visit_probe (const OASIS_PDL_Probe & p);

  virtual void visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & );

  virtual void visit_struct (const OASIS_PDL_Struct & s);

  bool find(std::string type);

private:
  /// Target source file stream.
  std::ostream & csfile_;

  /// We are generating types for probes.
  bool is_probe_;

  /// Creating this to differentiate betn struct and basic types
  static const std::string basic_types[12];
};

}
}

#endif  // !defined _OASIS_PDL_BE_CSHARP_PACKAGE_DATA_GENERATOR_H_
