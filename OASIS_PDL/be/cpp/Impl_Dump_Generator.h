// -*- C++ -*-

//=============================================================================
/**
 * @file      Impl_Dump_Generator.h
 *
 *  $Id: Impl_Dump_Generator.h 2214 2012-08-10 15:00:08Z dfeiock $
 *
 *  @author   Dennis Feiock
 */
//=============================================================================

#ifndef _OASIS_PDL_BE_CPP_IMPL_DUMP_GENERATOR_H_
#define _OASIS_PDL_BE_CPP_IMPL_DUMP_GENERATOR_H_

#include "fe/PDL_Visitor.h"
#include <ostream>

namespace OASIS_PDL_BE
{
namespace Cpp
{

/**
 * @class Impl_Dump_Generator
 *
 * Visitor that generates the dump implementation.
 */
class Impl_Dump_Generator : public OASIS_PDL_Visitor
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       out       Target output stream.
   */
  Impl_Dump_Generator (std::ostream & hfile, std::ostream & cppfile);

  /// Destructor.
  virtual ~Impl_Dump_Generator (void);

  virtual void visit_probe (const OASIS_PDL_Probe & p);

  virtual void visit_struct (const OASIS_PDL_Struct & s);

private:
  /// Target source file stream.
  std::ostream & hfile_;

  /// Target source file stream.
  std::ostream & cppfile_;
};

/**
 * @class Impl_Dump_Variable_Generator
 *
 * Visitor that generates the dump implementation based
 * on its type.
 */
class Impl_Dump_Variable_Generator : public OASIS_PDL_Visitor
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       out       Target output stream.
   */
  Impl_Dump_Variable_Generator (std::ostream & hfile, std::ostream & cppfile);

  /// Destructor.
  virtual ~Impl_Dump_Variable_Generator (void);

  virtual void visit_probe (const OASIS_PDL_Probe & p);

  virtual void visit_struct (const OASIS_PDL_Struct & s);

  virtual void visit_simple_type (const OASIS_PDL_Simple_Type & s);

  virtual void visit_vector_type (const OASIS_PDL_Vector_Type & v);

  /// Setter for the name of the variable which needs generated
  void name (const std::string & name);

  /// Setter for if the parent is a probe
  void parent_is_probe (const bool & probe);

private:
  /// Target source file stream.
  std::ostream & hfile_;

  /// Target source file stream.
  std::ostream & cppfile_;

  /// Name of the variable to write
  std::string name_;

  /// Whether or not the parent is a probe
  bool parent_is_probe_;
};

}
}

#endif  // !defined _OASIS_PDL_BE_CPP_VAR_TYPE_GENERATOR_H_
