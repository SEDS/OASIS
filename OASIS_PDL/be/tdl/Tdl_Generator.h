// -*- C++ -*-

//=============================================================================
/**
 * @file      Probe_Schema_Generator.h
 *
 *  $Id: Tdl_Generator.h 1866 2011-08-22 13:06:27Z hillj $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_TDL_GENERATOR_H_
#define _OASIS_PDL_TDL_GENERATOR_H_

#include "be/PDL_Backend.h"
#include "Tdl_Generator_export.h"

/**
 * @class OASIS_PDL_Tdl_Generator
 *
 * Implementation of the schema backend generator.
 */
class OASIS_PDL_TDL_GENERATOR_Export OASIS_PDL_Tdl_Generator :
  public OASIS_PDL_Backend
{
public:
  /// Default constructor.
  OASIS_PDL_Tdl_Generator (void);

  /// Destructor.
  virtual ~OASIS_PDL_Tdl_Generator (void);

  /// Parse command-line arguments for the backend.
  virtual int parse_args (int argc, char * argv []);

  /// Process the specified file.
  virtual int generate (const OASIS_PDL_File & file);
};

OASIS_PDL_BE_DECL (OASIS_PDL_TDL_GENERATOR_Export, _make_OASIS_PDL_Tdl_Generator);

#if defined (__OASIS_INLINE__)
#include "Tdl_Generator.inl"
#endif

#endif  // !defined _OASIS_PDL_TDL_GENERATOR_H_
