// -*- C++ -*-

//============================================================================
/**
 * @file        data_handlerImpl.h
 *
 * $Id$
 *
 * @author      James H. Hill (hillj at cs dot iupui dot edu)
 *              OASIS Software Probe Generator (C++ Version)
 *              http://www.cs.iupui.edu/oasis
 */
//============================================================================

#ifndef _DATA_HANDLERIMPL_H_
#define _DATA_HANDLERIMPL_H_

#include "oasis/probes/Data_Types.h"
#include "data_handler_Metadata.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include <iostream>

namespace Test
{
  /**
   * @class Byte_0Impl
   */
  class Byte_0Impl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::Test::Byte_0_Metadata __metadata__;

    /// Default constructor
    Byte_0Impl (void);

    /// Destructor
    virtual ~Byte_0Impl (void);

    /// Getter for the probe's metadata
    virtual const ::Test::Byte_0_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);
  };

  /**
   * @class Byte_8Impl
   */
  class Byte_8Impl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::Test::Byte_8_Metadata __metadata__;

    /// Default constructor
    Byte_8Impl (void);

    /// Destructor
    virtual ~Byte_8Impl (void);

    /// Getter for the probe's metadata
    virtual const ::Test::Byte_8_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);


    public:
    // Setter and getter methods for value
    void value (ACE_INT8 value);
    ACE_INT8 value (void) const;

    protected:
    char value_;
  };

  /**
   * @class Byte_16Impl
   */
  class Byte_16Impl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::Test::Byte_16_Metadata __metadata__;

    /// Default constructor
    Byte_16Impl (void);

    /// Destructor
    virtual ~Byte_16Impl (void);

    /// Getter for the probe's metadata
    virtual const ::Test::Byte_16_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);


    public:
    // Setter and getter methods for value
    void value (ACE_UINT16 value);
    ACE_UINT16 value (void) const;

    protected:
    ACE_UINT16 value_;
  };

  /**
   * @class Byte_32Impl
   */
  class Byte_32Impl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::Test::Byte_32_Metadata __metadata__;

    /// Default constructor
    Byte_32Impl (void);

    /// Destructor
    virtual ~Byte_32Impl (void);

    /// Getter for the probe's metadata
    virtual const ::Test::Byte_32_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);


    public:
    // Setter and getter methods for value
    void value (ACE_UINT32 value);
    ACE_UINT32 value (void) const;

    protected:
    ACE_UINT32 value_;
  };

  /**
   * @class Byte_64Impl
   */
  class Byte_64Impl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::Test::Byte_64_Metadata __metadata__;

    /// Default constructor
    Byte_64Impl (void);

    /// Destructor
    virtual ~Byte_64Impl (void);

    /// Getter for the probe's metadata
    virtual const ::Test::Byte_64_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);


    public:
    // Setter and getter methods for value
    void value (ACE_UINT64 value);
    ACE_UINT64 value (void) const;

    protected:
    ACE_UINT64 value_;
  };

  /**
   * @class Byte_128Impl
   */
  class Byte_128Impl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::Test::Byte_128_Metadata __metadata__;

    /// Default constructor
    Byte_128Impl (void);

    /// Destructor
    virtual ~Byte_128Impl (void);

    /// Getter for the probe's metadata
    virtual const ::Test::Byte_128_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);


    public:
    // Setter and getter methods for value_a
    void value_a (ACE_UINT64 value_a);
    ACE_UINT64 value_a (void) const;

    // Setter and getter methods for value_b
    void value_b (ACE_UINT64 value_b);
    ACE_UINT64 value_b (void) const;

    protected:
    ACE_UINT64 value_a_;

    ACE_UINT64 value_b_;
  };

  /**
   * @class Byte_256Impl
   */
  class Byte_256Impl :
    public virtual ::OASIS::Software_Probe_Impl
  {
    public:
    /// The metadata for the software probe.
    static const ::Test::Byte_256_Metadata __metadata__;

    /// Default constructor
    Byte_256Impl (void);

    /// Destructor
    virtual ~Byte_256Impl (void);

    /// Getter for the probe's metadata
    virtual const ::Test::Byte_256_Metadata & metadata (void) const;

    /// Package the software probe's data.
    protected:
    virtual int package_data (::OASIS::Software_Probe_Data_Packager & p);


    public:
    /// Impl_Dump the software probe's data.
    virtual void dump (std::ostream & output);


    public:
    // Setter and getter methods for value_a
    void value_a (ACE_UINT64 value_a);
    ACE_UINT64 value_a (void) const;

    // Setter and getter methods for value_b
    void value_b (ACE_UINT64 value_b);
    ACE_UINT64 value_b (void) const;

    // Setter and getter methods for value_c
    void value_c (ACE_UINT64 value_c);
    ACE_UINT64 value_c (void) const;

    // Setter and getter methods for value_d
    void value_d (ACE_UINT64 value_d);
    ACE_UINT64 value_d (void) const;

    protected:
    ACE_UINT64 value_a_;

    ACE_UINT64 value_b_;

    ACE_UINT64 value_c_;

    ACE_UINT64 value_d_;
  };
}

#endif  // !defined __DATA_HANDLERIMPL_H__

