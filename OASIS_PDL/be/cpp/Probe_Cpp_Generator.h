// -*- C++ -*-

//=============================================================================
/**
 * @file      Probe_Cpp_Generator.h
 *
 *  $Id: Probe_Cpp_Generator.h 2211 2012-07-25 12:55:51Z dfeiock $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_PROBE_CPP_GENERATOR_H_
#define _OASIS_PDL_PROBE_CPP_GENERATOR_H_

#include "be/PDL_Backend.h"
#include "Probe_Cpp_Generator_export.h"

/**
 * @class OASIS_PDL_Probe_Cpp_Generator
 *
 * Implementation of the backend generator that generates a C++
 * version of a software probe.
 */
class OASIS_PDL_CPP_GENERATOR_Export OASIS_PDL_Probe_Cpp_Generator :
  public OASIS_PDL_Backend
{
public:
  /// Default constructor.
  OASIS_PDL_Probe_Cpp_Generator (void);

  /// Destructor.
  virtual ~OASIS_PDL_Probe_Cpp_Generator (void);

  virtual int parse_args (int argc, char * argv []);

  virtual int generate (const OASIS_PDL_File & file);

protected:
  /// Helper method for generating stub files
  int generate_stub (const OASIS_PDL_File & file);

  /// Helper method for generating impl files
  int generate_impl (const OASIS_PDL_File & file);

  /// Helper method for gernerating metadata files
  int generate_metadata (const OASIS_PDL_File & file);
};


OASIS_PDL_BE_DECL (OASIS_PDL_CPP_GENERATOR_Export, _make_PDL_Cpp_Generator);

#endif  // !defined _OASIS_PDL_PROBE_SCHEMA_GENERATOR_H_
