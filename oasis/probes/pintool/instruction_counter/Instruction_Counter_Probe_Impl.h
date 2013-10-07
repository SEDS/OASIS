// -*- C++ -*-

//==============================================================================
/**
 *  @file        Instruction_Counter_Probe_Impl.h
 *
 *  $Id: Instruction_Counter_Probe_Impl.h 2237 2013-02-14 18:16:58Z dfeiock $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_INSTRUCTION_COUNTER_PROBE_IMPL_H_
#define _OASIS_PIN_INSTRUCTION_COUNTER_PROBE_IMPL_H_

#include "Instruction_Counter_ProbeImpl.h"
#include "Instruction_Counter_Probe_Impl_export.h"
#include "oasis/probes/Software_Probe_Factory_T.h"
#include "oasis/tools/PINtool/PINtool.h"
#include "oasis/tools/PINtool/Instruction_Probe.h"
#include "oasis/tools/PINtool/Instruction_Callback0.h"

namespace OASIS
{
namespace PIN
{

/**
 * Callback which increments the count
 */
class Instruction_Counter_Callback
  : public ::OASIS::PIN::Instruction_Callback0 <Instruction_Counter_Callback>
{
public:
  /// Initializing constructor.
  Instruction_Counter_Callback (ACE_INT32 & count);

  /// Destructor
  ~Instruction_Counter_Callback (void);

  /// analyze hook
  void handle_analyze (void);

private:
  /// The counter
  ACE_INT32 & count_;
};

/**
 * @class Instruction_Counter_Probe_Impl
 *
 * PINtool which counts instructions
 */
class INSTRUCTION_COUNTER_PROBE_IMPL_Export Instruction_Counter_Probe_Impl
  : public ::OASIS::PIN::Instruction_Probe,
    public ::OASIS::PIN::Instruction_Counter_ProbeImpl
{
public:
  /// Default constructor.
  Instruction_Counter_Probe_Impl (void);

  /// Destructor.
  virtual ~Instruction_Counter_Probe_Impl (void);

  /// init
  virtual int init (const char * params, const char * name = 0);

  /// handle_collect_data
  virtual int handle_collect_data (void);

  /// PIN instrumentation
  void setup_instruction (Instruction_Builder & builder);

private:
  /// The pin callback
  Instruction_Counter_Callback all_callback_;
  Instruction_Counter_Callback predicated_callback_;
};

/// Type definition for the software probe's factory
typedef ::OASIS::Software_Probe_Factory_T <Instruction_Counter_Probe_Impl>
 Instruction_Counter_Probe_Impl_Factory;

/// Export the interface for the software probe factory.
OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_DECL (INSTRUCTION_COUNTER_PROBE_IMPL_Export,
                                          create_OASIS_PIN_Instruction_Counter_Probe_Impl_Factory);

} // namespace PIN
} // namespace OASIS

#if defined (__OASIS_INLINE__)
#include "Instruction_Counter_Probe_Impl.inl"
#endif  // !defined __OASIS_INLINE__

#endif  // _OASIS_PIN_INSTRUCTION_COUNTER_PROBE_IMPL_H_
