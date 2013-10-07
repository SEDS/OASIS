// -*- C++ -*-

//=============================================================================
/**
 * @file      Flush_Generator.h
 *
 *  $Id: Flush_Generator.h 2118 2012-01-13 20:29:17Z dpuranik $
 *
 *  @author   Darshan.Puranik
 */
//=============================================================================

#ifndef _OASIS_PDL_BE_CSHARP_FLUSH_GENERATOR_H_
#define _OASIS_PDL_BE_CSHARP_FLUSH_GENERATOR_H_

#include "fe/PDL_Visitor.h"
#include <ostream>

namespace OASIS_PDL_BE
{
namespace Csharp
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
  Flush_Generator (std::ostream & csfile);

  /// Destructor.
  virtual ~Flush_Generator (void);

  virtual void visit_probe (const OASIS_PDL_Probe & p);

private:
  /// Target source file stream.
  std::ostream & csfile_;

  /// We are generating types for probes.
  bool is_probe_;
};

}
}

#endif  // !defined _OASIS_PDL_BE_CSHARP_FLUSH_GENERATOR_H_
