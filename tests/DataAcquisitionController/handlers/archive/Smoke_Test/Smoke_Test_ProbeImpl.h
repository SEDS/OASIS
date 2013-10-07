// -*- C++ -*-

//============================================================================
/**
 * @file        Smoke_Test_ProbeImpl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _SMOKE_TEST_PROBEIMPL_H_
#define _SMOKE_TEST_PROBEIMPL_H_

#include "oasis/probes/Data_Types.h"
#include "Smoke_Test_Probe_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

/**
 * @class AImpl
 */
class AImpl :
  public virtual ::OASIS::Software_Probe_Impl
{
  public:
  /// The metadata for the software probe.
  static const ::A_Metadata __metadata__;

  /// Default constructor
  AImpl (void);

  /// Destructor
  virtual ~AImpl (void);

  /// Getter for the probe's metadata
  virtual const ::A_Metadata & metadata (void) const;

  /// Package the software probe's data.
  protected:
  virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


  public:
  /// Impl_Dump the software probe's data.
  virtual void dump (std::ostream & output);


  public:
  // Setter and getter methods for a_value
  void a_value (ACE_INT32 a_value);
  ACE_INT32 a_value (void) const;

  protected:
  ACE_INT32 a_value_;
};

namespace SmokeTest
{
  /**
   * @class BImpl
   */
  class BImpl :
    public ::AImpl
  {
    public:
    /// The metadata for the software probe.
    static const ::SmokeTest::B_Metadata __metadata__;

    /// Default constructor
    BImpl (void);

    /// Destructor
    virtual ~BImpl (void);

    /// Getter for the probe's metadata
    virtual const ::SmokeTest::B_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);


    public:
    // Setter and getter methods for b_value
    void b_value (ACE_INT32 b_value);
    ACE_INT32 b_value (void) const;

    protected:
    ACE_INT32 b_value_;
  };

  /**
   * @class CImpl
   */
  class CImpl :
    public ::SmokeTest::BImpl
  {
    public:
    /// The metadata for the software probe.
    static const ::SmokeTest::C_Metadata __metadata__;

    /// Default constructor
    CImpl (void);

    /// Destructor
    virtual ~CImpl (void);

    /// Getter for the probe's metadata
    virtual const ::SmokeTest::C_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);


    public:
    // Setter and getter methods for c_value
    void c_value (ACE_INT32 c_value);
    ACE_INT32 c_value (void) const;

    protected:
    ACE_INT32 c_value_;
  };
}

#endif  // !defined __SMOKE_TEST_PROBEIMPL_H__

