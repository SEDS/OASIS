// -*- C++ -*-

//=============================================================================
/**
 * @file      Probe_Csharp_Generator.h
 *
 *  $Id: Probe_Csharp_Generator.h 2118 2012-01-13 20:29:17Z dpuranik $
 *
 *  @author   Darshan Puranik
 */
//=============================================================================

#ifndef _OASIS_PDL_PROBE_CSHARP_GENERATOR_H_
#define _OASIS_PDL_PROBE_CSHARP_GENERATOR_H_

#include "be/PDL_Backend.h"
#include "Probe_Csharp_Generator_export.h"

/**
 * @class OASIS_PDL_Probe_Cpp_Generator
 *
 * Implementation of the backend generator that generates a C++
 * version of a software probe.
 */
class OASIS_PDL_Csharp_Generator_Export OASIS_PDL_Probe_Csharp_Generator :
  public OASIS_PDL_Backend
{
public:
  /// Default constructor.
  OASIS_PDL_Probe_Csharp_Generator (void);

  /// Destructor.
  virtual ~OASIS_PDL_Probe_Csharp_Generator (void);

  virtual int parse_args (int argc, char * argv []);

  virtual int generate (const OASIS_PDL_File & file);
};


//OASIS_PDL_BE_DECL (OASIS_PDL_CSHARP_GENERATOR_Export, _make_PDL_Csharp_Generator);

#endif  // !defined _OASIS_PDL_PROBE_SCHEMA_GENERATOR_H_
