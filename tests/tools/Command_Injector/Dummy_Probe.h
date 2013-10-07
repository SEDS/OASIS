// -*- C++ -*-

//============================================================================
/**
 * @file        Dummy_Probe.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _DUMMY_PROBE_H_
#define _DUMMY_PROBE_H_

#include "oasis/probes/Data_Types.h"
#include "oasis/probes/Software_Probe.h"
#include "Dummy_Probe_Metadata.h"
#include <iostream>

/**
 * @class Dummy_Probe
 */
class Dummy_Probe :
  public virtual ::OASIS::Software_Probe 
{
  public:
  // Type definition of the software probe's metadata.
  typedef ::Dummy_Probe_Metadata METADATA_TYPE;

  /// The metadata for the software probe.
  static const METADATA_TYPE __metadata__;

  /// Default constructor
  Dummy_Probe (void);

  /// Destructor
  virtual ~Dummy_Probe (void);

  /// Getter for the probe's metadata
  virtual const METADATA_TYPE & metadata (void) const;

  public:
  /// Recall the software probe's data.
  virtual int recall (const char * data, size_t length, int byte_order);

  protected:
  /// Helper method for recalling the data.
  int recall (ACE_InputCDR & input);

  public:
  /// Stub_Dump the software probe's data.
  virtual void dump (std::ostream & output);
};

#endif  // !defined __DUMMY_PROBE_H__

