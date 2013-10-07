// -*- C++ -*-

//============================================================================
/**
 * @file        data_handler_Metadata.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _DATA_HANDLER_METADATA_H_
#define _DATA_HANDLER_METADATA_H_

#include "oasis/probes/Software_Probe_Metadata.h"

namespace Test
{
  /**
   * @class Byte_0_Metadata
   */
  class Byte_0_Metadata :
    public ::OASIS::Software_Probe_Metadata 
  {
    public:
    /// Default constructor
    Byte_0_Metadata (void);

    /// Destructor
    virtual ~Byte_0_Metadata (void);

    protected:
    /// Initalizing constructor
    Byte_0_Metadata (const char * uuid,
                     const char * type_info,
                     ACE_UINT8 version_major,
                     ACE_UINT8 version_minor,
                     const char * schema);

    private:
    /// The metadata's schema
    static const char * __schema__;
  };

  /**
   * @class Byte_8_Metadata
   */
  class Byte_8_Metadata :
    public ::OASIS::Software_Probe_Metadata 
  {
    public:
    /// Default constructor
    Byte_8_Metadata (void);

    /// Destructor
    virtual ~Byte_8_Metadata (void);

    protected:
    /// Initalizing constructor
    Byte_8_Metadata (const char * uuid,
                     const char * type_info,
                     ACE_UINT8 version_major,
                     ACE_UINT8 version_minor,
                     const char * schema);

    private:
    /// The metadata's schema
    static const char * __schema__;
  };

  /**
   * @class Byte_16_Metadata
   */
  class Byte_16_Metadata :
    public ::OASIS::Software_Probe_Metadata 
  {
    public:
    /// Default constructor
    Byte_16_Metadata (void);

    /// Destructor
    virtual ~Byte_16_Metadata (void);

    protected:
    /// Initalizing constructor
    Byte_16_Metadata (const char * uuid,
                      const char * type_info,
                      ACE_UINT8 version_major,
                      ACE_UINT8 version_minor,
                      const char * schema);

    private:
    /// The metadata's schema
    static const char * __schema__;
  };

  /**
   * @class Byte_32_Metadata
   */
  class Byte_32_Metadata :
    public ::OASIS::Software_Probe_Metadata 
  {
    public:
    /// Default constructor
    Byte_32_Metadata (void);

    /// Destructor
    virtual ~Byte_32_Metadata (void);

    protected:
    /// Initalizing constructor
    Byte_32_Metadata (const char * uuid,
                      const char * type_info,
                      ACE_UINT8 version_major,
                      ACE_UINT8 version_minor,
                      const char * schema);

    private:
    /// The metadata's schema
    static const char * __schema__;
  };

  /**
   * @class Byte_64_Metadata
   */
  class Byte_64_Metadata :
    public ::OASIS::Software_Probe_Metadata 
  {
    public:
    /// Default constructor
    Byte_64_Metadata (void);

    /// Destructor
    virtual ~Byte_64_Metadata (void);

    protected:
    /// Initalizing constructor
    Byte_64_Metadata (const char * uuid,
                      const char * type_info,
                      ACE_UINT8 version_major,
                      ACE_UINT8 version_minor,
                      const char * schema);

    private:
    /// The metadata's schema
    static const char * __schema__;
  };

  /**
   * @class Byte_128_Metadata
   */
  class Byte_128_Metadata :
    public ::OASIS::Software_Probe_Metadata 
  {
    public:
    /// Default constructor
    Byte_128_Metadata (void);

    /// Destructor
    virtual ~Byte_128_Metadata (void);

    protected:
    /// Initalizing constructor
    Byte_128_Metadata (const char * uuid,
                       const char * type_info,
                       ACE_UINT8 version_major,
                       ACE_UINT8 version_minor,
                       const char * schema);

    private:
    /// The metadata's schema
    static const char * __schema__;
  };

  /**
   * @class Byte_256_Metadata
   */
  class Byte_256_Metadata :
    public ::OASIS::Software_Probe_Metadata 
  {
    public:
    /// Default constructor
    Byte_256_Metadata (void);

    /// Destructor
    virtual ~Byte_256_Metadata (void);

    protected:
    /// Initalizing constructor
    Byte_256_Metadata (const char * uuid,
                       const char * type_info,
                       ACE_UINT8 version_major,
                       ACE_UINT8 version_minor,
                       const char * schema);

    private:
    /// The metadata's schema
    static const char * __schema__;
  };
}

#endif  // !defined __DATA_HANDLER_METADATA_H__

