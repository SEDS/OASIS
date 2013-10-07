// -*- C++ -*-

//==============================================================================
/**
 *  @file        Instruction_Address_Probe_Impl.h
 *
 *  $Id: Instruction_Address_Probe_Impl.h 2239 2013-08-08 15:23:33Z dfeiock $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_INSTRUCTION_ADDRESS_PROBE_IMPL_H_
#define _OASIS_PIN_INSTRUCTION_ADDRESS_PROBE_IMPL_H_

#include "Instruction_Address_ProbeImpl.h"
#include "Instruction_Address_Probe_Impl_export.h"
#include "oasis/probes/Software_Probe_Factory_T.h"
#include "oasis/tools/PINtool/PINtool.h"
#include "oasis/tools/PINtool/Instruction_Probe.h"
#include "oasis/tools/PINtool/Instruction_Callback1.h"

namespace OASIS
{
namespace PIN
{

/**
 * Callback which increments the count
 */
class Instruction_Address_Callback
  : public ::OASIS::PIN::Instruction_Callback1 <Instruction_Address_Callback, ::IARG_INST_PTR>
{
public:
  /// Initializing constructor.
  Instruction_Address_Callback (ACE_UINT64 & address);

  /// Destructor
  ~Instruction_Address_Callback (void);

  /// analyze hook
  void handle_analyze (VOID * ip);

private:
  /// The counter
  ACE_UINT64 & address_;
};

/**
 * @class Instruction_Address_Probe_Impl
 *
 * PINtool which captures instruction addresses
 */
class INSTRUCTION_ADDRESS_PROBE_IMPL_Export Instruction_Address_Probe_Impl
  : public ::OASIS::PIN::Instruction_Probe,
    public ::OASIS::PIN::Instruction_Address_ProbeImpl
{
public:
  /// Default constructor.
  Instruction_Address_Probe_Impl (void);

  /// Destructor.
  virtual ~Instruction_Address_Probe_Impl (void);

  /// init
  virtual int init (const char * params, const char * name = 0);

  /// handle_collect_data
  virtual int handle_collect_data (void);

  /// PIN instrumentation
  void setup_instruction (Instruction_Builder & builder);

private:
  /// The pin callback
  Instruction_Address_Callback callback_;
};

/// Type definition for the software probe's factory
typedef ::OASIS::Software_Probe_Factory_T <Instruction_Address_Probe_Impl>
 Instruction_Address_Probe_Impl_Factory;

/// Export the interface for the software probe factory.
OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_DECL (INSTRUCTION_ADDRESS_PROBE_IMPL_Export,
                                          create_OASIS_PIN_Instruction_Address_Probe_Impl_Factory);

} // namespace PIN
} // namespace OASIS

#if defined (__OASIS_INLINE__)
#include "Instruction_Address_Probe_Impl.inl"
#endif  // !defined __OASIS_INLINE__

#endif  // _OASIS_PIN_INSTRUCTION_ADDRESS_PROBE_IMPL_H_
