// -*- C++ -*-

//=============================================================================
/**
 * @file      Probe_Schema_Generator.h
 *
 *  $Id: Probe_Schema_Generator.h 1866 2011-08-22 13:06:27Z hillj $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_PROBE_SCHEMA_GENERATOR_H_
#define _OASIS_PDL_PROBE_SCHEMA_GENERATOR_H_

#include "be/PDL_Backend.h"
#include "Probe_Schema_Generator_export.h"

/**
 * @class OASIS_PDL_Probe_Schema_Generator
 *
 * Implementation of the schema backend generator.
 */
class OASIS_PDL_SCHEMA_GENERATOR_Export OASIS_PDL_Probe_Schema_Generator :
  public OASIS_PDL_Backend
{
public:
  /// Default constructor.
  OASIS_PDL_Probe_Schema_Generator (void);

  /// Destructor.
  virtual ~OASIS_PDL_Probe_Schema_Generator (void);

  virtual int parse_args (int argc, char * argv []);

  virtual int generate (const OASIS_PDL_File & file);
};


OASIS_PDL_BE_DECL (OASIS_PDL_SCHEMA_GENERATOR_Export, _make_PDL_Schema_Generator);

#endif  // !defined _OASIS_PDL_PROBE_SCHEMA_GENERATOR_H_
