// -*- C++ -*-

//=============================================================================
/**
 * @file        Software_Probe_Factory.h
 *
 * $Id: Software_Probe_Factory.h 1771 2011-03-02 20:56:37Z hillj $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_SOFTWARE_PROBE_FACTORY_H_
#define _OASIS_SOFTWARE_PROBE_FACTORY_H_

namespace OASIS
{
// Forward decl.
class Software_Probe_Impl;

/**
 * @class Software_Probe_Factory
 *
 * Interface for all software probe factory objects. The software
 * probe implementer has control on how to allocate a software probe.
 */
class Software_Probe_Factory
{
public:
  /// Destructor.
  virtual ~Software_Probe_Factory (void) { }

  /// Metadata for the software probe.
  virtual Software_Probe_Impl * create (void) = 0;
};

}

#define OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_DECL(EXPORT_MACRO, SYMBOL) \
  extern "C" EXPORT_MACRO ::OASIS::Software_Probe_Factory * SYMBOL (void)

#define OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_IMPL(SYMBOL, FACTORY) \
  ::OASIS::Software_Probe_Factory * SYMBOL (void) { \
    FACTORY * factory = 0; \
    ACE_NEW_RETURN (factory, FACTORY (), factory); \
    return factory; \
  }

#endif  // !defined _EISA_SOFTWARE_PROBE_FACTORY_H_
