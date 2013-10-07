// -*- C++ -*-

//=============================================================================
/**
 * @file      Package_Data_Generator.h
 *
 *  $Id: Package_Data_Generator.h 2222 2012-11-20 17:02:16Z dfeiock $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_BE_CPP_PACKAGE_DATA_GENERATOR_H_
#define _OASIS_PDL_BE_CPP_PACKAGE_DATA_GENERATOR_H_

#include "fe/PDL_Visitor.h"
#include <ostream>

namespace OASIS_PDL_BE
{
namespace Cpp
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
  Package_Data_Generator (std::ostream & hfile, std::ostream & cppfile);

  /// Destructor.
  virtual ~Package_Data_Generator (void);

  virtual void visit_probe (const OASIS_PDL_Probe & p);

  virtual void visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & );

  virtual void visit_struct (const OASIS_PDL_Struct & s);

private:
  /// Target source file stream.
  std::ostream & hfile_;

  /// Target source file stream.
  std::ostream & cppfile_;

  /// Suffix to append to variable names
  std::string var_suffix_;
};

}
}

#endif  // !defined _OASIS_PDL_BE_CPP_VAR_TYPE_GENERATOR_H_
