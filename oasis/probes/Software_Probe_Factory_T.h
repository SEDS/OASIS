// -*- C++ -*-

//=============================================================================
/**
 * @file        Software_Probe_Factory_T.h
 *
 * $Id: Software_Probe_Factory_T.h 1778 2011-03-02 23:52:49Z hillj $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_SOFTWARE_PROBE_FACTORY_T_H_
#define _OASIS_SOFTWARE_PROBE_FACTORY_T_H_

#include "Software_Probe_Factory.h"
#include "oasis/config.h"

namespace OASIS
{
/**
 * @class Software_Probe_Factory_T
 *
 * Simple version of the factory that implements the create () method. This
 * makes it easier for developers to implement the factory object that
 * a software probe must provide.
 */
template <typename T>
class Software_Probe_Factory_T :
  public Software_Probe_Factory
{
public:
  /// Default constructor
  Software_Probe_Factory_T (void);

  /// Type definition of the probe type
  typedef T probe_type;

  /// Destructor
  virtual ~Software_Probe_Factory_T (void);

  /**
   * Default factory method for creating software probes.
   *
   * @param[in]       parent          Owner of software probe
   * @return          Pointer to a software probe
   */
  virtual Software_Probe_Impl * create (void);
};

}

#if defined (__OASIS_INLINE__)
#include "Software_Probe_Factory_T.inl"
#endif

#include "Software_Probe_Factory_T.cpp"

#endif  // !defined _EISA_SOFTWARE_PROBE_FACTORY_T_H_
