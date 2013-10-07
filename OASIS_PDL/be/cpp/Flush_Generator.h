// -*- C++ -*-

//=============================================================================
/**
 * @file      Flush_Generator.h
 *
 *  $Id: Flush_Generator.h 1771 2011-03-02 20:56:37Z hillj $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_BE_CPP_FLUSH_GENERATOR_H_
#define _OASIS_PDL_BE_CPP_FLUSH_GENERATOR_H_

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
class Flush_Generator : public OASIS_PDL_Visitor
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]       out       Target output stream.
   */
  Flush_Generator (std::ostream & hfile, std::ostream & cppfile);

  /// Destructor.
  virtual ~Flush_Generator (void);

  virtual void visit_probe (const OASIS_PDL_Probe & p);

private:
  /// Target source file stream.
  std::ostream & hfile_;

  /// Target source file stream.
  std::ostream & cppfile_;

  /// We are generating types for probes.
  bool is_probe_;
};

}
}

#endif  // !defined _OASIS_PDL_BE_CPP_VAR_TYPE_GENERATOR_H_
