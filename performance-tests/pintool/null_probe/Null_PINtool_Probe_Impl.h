// -*- C++ -*-

//==============================================================================
/**
 *  @file        Null_PINtool_Probe_Impl.h
 *
 *  $Id: Null_PINtool_Probe_Impl.h 2240 2013-08-13 18:13:43Z dfeiock $
 *
 *  @author      Dennis Feiock
 */
//==============================================================================

#ifndef _OASIS_PIN_NULL_PINTOOL_PROBE_IMPL_H_
#define _OASIS_PIN_NULL_PINTOOL_PROBE_IMPL_H_

#include "Null_PINtool_ProbeImpl.h"
#include "Null_PINtool_Probe_Impl_export.h"
#include "oasis/probes/Software_Probe_Factory_T.h"
#include "oasis/tools/PINtool/PINtool.h"
#include "oasis/tools/PINtool/Instruction_Probe.h"
#include "oasis/tools/PINtool/Instruction_Callback0.h"
#include "oasis/tools/PINtool/Instruction_Callback1.h"

namespace OASIS
{
namespace PIN
{

/**
 * Instruction_Callback0 which does nothing
 */
class Null_Instruction_Callback0
  : public ::OASIS::PIN::Instruction_Callback0 <Null_Instruction_Callback0>
{
public:
  /// Initializing constructor.
  Null_Instruction_Callback0 (void);

  /// Destructor
  ~Null_Instruction_Callback0 (void);

  /// analyze hook
  void handle_analyze (void);
};

/*
 * Instruction_Callback1 which does nothing
 */
class Null_Instruction_Callback1_INST_PTR
  : public ::OASIS::PIN::Instruction_Callback1 <Null_Instruction_Callback1_INST_PTR, ::IARG_INST_PTR>
{
public:
  /// Initializing constructor.
  Null_Instruction_Callback1_INST_PTR (void);

  /// Destructor
  ~Null_Instruction_Callback1_INST_PTR (void);

  /// analyze hook
  void handle_analyze (VOID * ptr);
};

/**
 * @class Null_PINtool_Probe_Impl
 *
 * Instruction Probe which does nothing
 */
class NULL_PINTOOL_PROBE_IMPL_Export Null_PINtool_Probe_Impl
  : public ::OASIS::PIN::Instruction_Probe,
    public ::OASIS::PIN::Null_PINtool_ProbeImpl
{
public:
  /// Default constructor.
  Null_PINtool_Probe_Impl (void);

  /// Destructor.
  virtual ~Null_PINtool_Probe_Impl (void);

  /// init
  virtual int init (const char * params, const char * name = 0);

  /// handle_collect_data
  virtual int handle_collect_data (void);

  /// PIN instrumentation
  void setup_instruction (Instruction_Builder & builder);

private:
  int parse_args (const char * args);

  /// The pin callback, set via init
  ::OASIS::PIN::Instruction_Callback * callback_;

  ACE_CString callback_type_;
};

/// Type definition for the software probe's factory
typedef ::OASIS::Software_Probe_Factory_T <Null_PINtool_Probe_Impl>
 Null_PINtool_Probe_Impl_Factory;

/// Export the interface for the software probe factory.
OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_DECL (NULL_PINTOOL_PROBE_IMPL_Export,
                                          create_OASIS_PIN_Null_PINtool_Probe_Impl_Factory);

} // namespace PIN
} // namespace OASIS

#if defined (__OASIS_INLINE__)
#include "Null_PINtool_Probe_Impl.inl"
#endif  // !defined __OASIS_INLINE__

#endif  // _OASIS_PIN_NULL_PINTOOL_PROBE_IMPL_H_
