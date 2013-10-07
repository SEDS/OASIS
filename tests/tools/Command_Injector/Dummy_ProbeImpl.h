// -*- C++ -*-

//============================================================================
/**
 * @file        Dummy_ProbeImpl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _DUMMY_PROBEIMPL_H_
#define _DUMMY_PROBEIMPL_H_

#include "oasis/probes/Data_Types.h"
#include "Dummy_Probe_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

/**
 * @class Dummy_ProbeImpl
 */
class Dummy_ProbeImpl :
  public virtual ::OASIS::Software_Probe_Impl
{
  public:
  /// The metadata for the software probe.
  static const ::Dummy_Probe_Metadata __metadata__;

  /// Default constructor
  Dummy_ProbeImpl (void);

  /// Destructor
  virtual ~Dummy_ProbeImpl (void);

  /// Getter for the probe's metadata
  virtual const ::Dummy_Probe_Metadata & metadata (void) const;

  /// Package the software probe's data.
  protected:
  virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


  public:
  /// Impl_Dump the software probe's data.
  virtual void dump (std::ostream & output);
};

#endif  // !defined __DUMMY_PROBEIMPL_H__

