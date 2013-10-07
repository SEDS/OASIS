// -*- C++ -*-

//=============================================================================
/**
 *  @file       PDL_Configuration.h
 *
 *  $Id: PDL_Configuration.h 1866 2011-08-22 13:06:27Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_CONFIGURATION_H_
#define _OASIS_PDL_CONFIGURATION_H_

#include <string>
#include <set>

#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"
#include "ace/Unbounded_Set.h"

#include "PDL_FE_export.h"

/**
 * @class Configuration
 *
 * The configuration for the OASIS probe definition language.
 */
class OASIS_PDL_FE_Export OASIS_PDL_Configuration
{
public:
  /// Default constructor.
  OASIS_PDL_Configuration (void);

  /// Destructor.
  ~OASIS_PDL_Configuration (void);

  /// The target output directory.
  std::string outdir_;
};

#define OASIS_PDL_CONFIGURATION \
  ACE_Singleton <OASIS_PDL_Configuration, ACE_Null_Mutex>

OASIS_PDL_FE_SINGLETON_DECLARE (ACE_Singleton,
                                OASIS_PDL_Configuration,
                                ACE_Null_Mutex)

#endif  // !defined _OASIS_PDL_CONFIGURATION_H_
