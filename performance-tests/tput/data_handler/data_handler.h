// -*- C++ -*-

//============================================================================
/**
 * @file        data_handler.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _DATA_HANDLER_H_
#define _DATA_HANDLER_H_

#include "oasis/probes/Data_Types.h"
#include "oasis/probes/Software_Probe.h"
#include "data_handler_Metadata.h"
#include <iostream>

namespace Test
{
  /**
   * @class Byte_0
   */
  class Byte_0 :
    public virtual ::OASIS::Software_Probe 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::Test::Byte_0_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    Byte_0 (void);

    /// Destructor
    virtual ~Byte_0 (void);

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

  /**
   * @class Byte_8
   */
  class Byte_8 :
    public virtual ::OASIS::Software_Probe 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::Test::Byte_8_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    Byte_8 (void);

    /// Destructor
    virtual ~Byte_8 (void);

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
    // Getter method for value
    ACE_INT8 value (void) const;

    protected:
    char value_;
  };

  /**
   * @class Byte_16
   */
  class Byte_16 :
    public virtual ::OASIS::Software_Probe 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::Test::Byte_16_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    Byte_16 (void);

    /// Destructor
    virtual ~Byte_16 (void);

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
    // Getter method for value
    ACE_UINT16 value (void) const;

    protected:
    ACE_UINT16 value_;
  };

  /**
   * @class Byte_32
   */
  class Byte_32 :
    public virtual ::OASIS::Software_Probe 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::Test::Byte_32_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    Byte_32 (void);

    /// Destructor
    virtual ~Byte_32 (void);

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
    // Getter method for value
    ACE_UINT32 value (void) const;

    protected:
    ACE_UINT32 value_;
  };

  /**
   * @class Byte_64
   */
  class Byte_64 :
    public virtual ::OASIS::Software_Probe 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::Test::Byte_64_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    Byte_64 (void);

    /// Destructor
    virtual ~Byte_64 (void);

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
    // Getter method for value
    ACE_UINT64 value (void) const;

    protected:
    ACE_UINT64 value_;
  };

  /**
   * @class Byte_128
   */
  class Byte_128 :
    public virtual ::OASIS::Software_Probe 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::Test::Byte_128_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    Byte_128 (void);

    /// Destructor
    virtual ~Byte_128 (void);

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
    // Getter method for value_a
    ACE_UINT64 value_a (void) const;

    // Getter method for value_b
    ACE_UINT64 value_b (void) const;

    protected:
    ACE_UINT64 value_a_;

    ACE_UINT64 value_b_;
  };

  /**
   * @class Byte_256
   */
  class Byte_256 :
    public virtual ::OASIS::Software_Probe 
  {
    public:
    // Type definition of the software probe's metadata.
    typedef ::Test::Byte_256_Metadata METADATA_TYPE;

    /// The metadata for the software probe.
    static const METADATA_TYPE __metadata__;

    /// Default constructor
    Byte_256 (void);

    /// Destructor
    virtual ~Byte_256 (void);

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
    // Getter method for value_a
    ACE_UINT64 value_a (void) const;

    // Getter method for value_b
    ACE_UINT64 value_b (void) const;

    // Getter method for value_c
    ACE_UINT64 value_c (void) const;

    // Getter method for value_d
    ACE_UINT64 value_d (void) const;

    protected:
    ACE_UINT64 value_a_;

    ACE_UINT64 value_b_;

    ACE_UINT64 value_c_;

    ACE_UINT64 value_d_;
  };
}

#endif  // !defined __DATA_HANDLER_H__

