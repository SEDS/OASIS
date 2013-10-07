// -*- C++ -*-

//==============================================================================
/**
 *  @file        Tao_Software_Probe_Data_Packager.h
 *
 *  $Id: Tao_Software_Probe_Data_Packager.h 2224 2012-12-10 06:35:58Z dfeiock $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_TAO_SOFTWARE_PROBE_DATA_PACKAGER_H_
#define _OASIS_TAO_SOFTWARE_PROBE_DATA_PACKAGER_H_

#include "oasis/DataChannel/Standard_Software_Probe_Data_Packager.h"

namespace OASIS
{

/**
 * @class Tao_Software_Probe_Data_Packager
 *
 * Packager for the TAO middleware
 */
class Tao_Software_Probe_Data_Packager :
  public Standard_Software_Probe_Data_Packager
{
public:
  /// Default constructor.
  Tao_Software_Probe_Data_Packager (void);

  /// Destructor.
  ~Tao_Software_Probe_Data_Packager (void);
};

} // namespace OASIS

#if defined (__OASIS_INLINE__)
#include "Tao_Software_Probe_Data_Packager.inl"
#endif  // !defined __OASIS_INLINE__

#endif  // _OASIS_TAO_SOFTWARE_PROBE_DATA_PACKAGER_H_
