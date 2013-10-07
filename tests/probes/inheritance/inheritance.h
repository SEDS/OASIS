// -*- C++ -*-

//============================================================================
/**
 * @file        inheritance.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _INHERITANCE_H_
#define _INHERITANCE_H_

#include "oasis/probes/Data_Types.h"
#include "oasis/probes/Software_Probe.h"
#include "inheritance_Metadata.h"
#include <iostream>

/**
 * @class A
 */
class A :
  public virtual ::OASIS::Software_Probe 
{
  public:
  // Type definition of the software probe's metadata.
  typedef ::A_Metadata METADATA_TYPE;

  /// The metadata for the software probe.
  static const METADATA_TYPE __metadata__;

  /// Default constructor
  A (void);

  /// Destructor
  virtual ~A (void);

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


  public:
  // Getter method for a_value
  ACE_INT32 a_value (void) const;

  protected:
  ACE_INT32 a_value_;
};

namespace Test
{
  /**
   * @class B
   */
  class B :
    public ::A 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::Test::B_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    B (void);

    /// Destructor
    virtual ~B (void);

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


    public:
    // Getter method for b_value
    ACE_INT32 b_value (void) const;

    protected:
    ACE_INT32 b_value_;
  };

  /**
   * @class C
   */
  class C :
    public ::Test::B 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::Test::C_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    C (void);

    /// Destructor
    virtual ~C (void);

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


    public:
    // Getter method for c_value
    ACE_INT32 c_value (void) const;

    protected:
    ACE_INT32 c_value_;
  };
}

#endif  // !defined __INHERITANCE_H__

