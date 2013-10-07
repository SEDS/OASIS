// -*- C++ -*-

//=============================================================================
/**
 * @file      PDL_Backend.h
 *
 *  $Id: PDL_Backend.h 1866 2011-08-22 13:06:27Z hillj $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_BACKEND_H_
#define _OASIS_PDL_BACKEND_H_

#include "PDL_BE_export.h"
#include "oasis/config.h"

// Forward decl.
class OASIS_PDL_File;

/**
 * @class OASIS_PDL_Backend
 *
 * Base class for all backend generators.
 */
class OASIS_PDL_BE_Export OASIS_PDL_Backend
{
public:
  /// Default constructor.
  OASIS_PDL_Backend (void);

  /// Destructor.
  virtual ~OASIS_PDL_Backend (void);

  /// Destroy the object.
  virtual void destroy (void);

  /// Parse the command-line arguments.
  virtual int parse_args (int argc, char * argv []);

  /// Execute generator on specified file.
  virtual int generate (const OASIS_PDL_File & file);

  /// Print the help.
  virtual void print_help (void);
};

#define OASIS_PDL_BE_DECL(EXPORT, SYMBOL) \
  extern "C" EXPORT OASIS_PDL_Backend * SYMBOL (void);

#define OASIS_PDL_BE_IMPL(SYMBOL, TYPE) \
  OASIS_PDL_Backend * SYMBOL (void) \
  { \
    return new TYPE (); \
  }

#if defined (__OASIS_INLINE__)
#include "PDL_Backend.inl"
#endif

#endif  // !defined _OASIS_PDL_BE_INIT_H_
