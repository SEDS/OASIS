// -*- C++ -*-

//============================================================================
/**
 * @file        inheritance_Metadata.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _INHERITANCE_METADATA_H_
#define _INHERITANCE_METADATA_H_

#include "oasis/probes/Software_Probe_Metadata.h"

/**
 * @class A_Metadata
 */
class A_Metadata :
  public ::OASIS::Software_Probe_Metadata 
{
  public:
  /// Default constructor
  A_Metadata (void);

  /// Destructor
  virtual ~A_Metadata (void);

  protected:
  /// Initalizing constructor
  A_Metadata (const char * uuid,
              const char * type_info,
              ACE_UINT8 version_major,
              ACE_UINT8 version_minor,
              const char * schema);

  private:
  /// The metadata's schema
  static const char * __schema__;
};

namespace Test
{
  /**
   * @class B_Metadata
   */
  class B_Metadata :
    public ::A_Metadata 
  {
    public:
    /// Default constructor
    B_Metadata (void);

    /// Destructor
    virtual ~B_Metadata (void);

    protected:
    /// Initalizing constructor
    B_Metadata (const char * uuid,
                const char * type_info,
                ACE_UINT8 version_major,
                ACE_UINT8 version_minor,
                const char * schema);

    private:
    /// The metadata's schema
    static const char * __schema__;
  };

  /**
   * @class C_Metadata
   */
  class C_Metadata :
    public ::Test::B_Metadata 
  {
    public:
    /// Default constructor
    C_Metadata (void);

    /// Destructor
    virtual ~C_Metadata (void);

    protected:
    /// Initalizing constructor
    C_Metadata (const char * uuid,
                const char * type_info,
                ACE_UINT8 version_major,
                ACE_UINT8 version_minor,
                const char * schema);

    private:
    /// The metadata's schema
    static const char * __schema__;
  };
}

#endif  // !defined __INHERITANCE_METADATA_H__

