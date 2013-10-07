// -*- C++ -*-

//==============================================================================
/**
 *  @file        Memory_Footprint_Probe_Impl.h
 *
 *  $Id: Memory_Footprint_Probe_Impl.h 2242 2013-08-22 15:38:08Z dfeiock $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_PIN_MEMORY_FOOTPRINT_PROBE_IMPL_H_
#define _OASIS_PIN_MEMORY_FOOTPRINT_PROBE_IMPL_H_

#include "Memory_Footprint_ProbeImpl.h"
#include "Memory_Footprint_Probe_Impl_export.h"
#include "oasis/probes/Software_Probe_Factory_T.h"
#include "oasis/tools/PINtool/PINtool.h"
#include "oasis/tools/PINtool/Trace_Probe.h"
#include "oasis/tools/PINtool/Instruction_Builder.h"
#include "oasis/tools/PINtool/Instruction_Callback2.h"
#include "oasis/tools/PINtool/Instruction_Callback3.h"
#include <list>
#include <map>

namespace OASIS
{
namespace PIN
{

/**
 * MEMORYREAD_EA Callback
 */
class MemoryReadEA_Callback
  : public ::OASIS::PIN::Instruction_Callback3 <MemoryReadEA_Callback,
                                                IARG_THREAD_ID,
                                                IARG_MEMORYREAD_EA,
                                                IARG_MEMORYREAD_SIZE>
{
public:
  static const unsigned int LOAD = 1;

  /// Initializing constructor.
  MemoryReadEA_Callback (std::map <ADDRINT, unsigned int> & memory);

  /// Destructor
  ~MemoryReadEA_Callback (void);

  /// analyze hook
  void handle_analyze (THREADID tid, ADDRINT memea, UINT32 length);

private:
  /// The memory
  std::map <ADDRINT, unsigned int> & memory_;
};

/**
 * MEMORYREAD2_EA Callback
 */
class MemoryRead2EA_Callback
  : public ::OASIS::PIN::Instruction_Callback3 <MemoryRead2EA_Callback,
                                                IARG_THREAD_ID,
                                                IARG_MEMORYREAD_EA,
                                                IARG_MEMORYREAD_SIZE>
{
public:
  static const unsigned int LOAD = 1;

  /// Initializing constructor.
  MemoryRead2EA_Callback (std::map <ADDRINT, unsigned int> & memory);

  /// Destructor
  ~MemoryRead2EA_Callback (void);

  /// analyze hook
  void handle_analyze (THREADID tid, ADDRINT memea, UINT32 length);

private:
  /// The memory
  std::map <ADDRINT, unsigned int> & memory_;
};

/**
 * MEMORYWRITE_EA Callback
 */
class MemoryWriteEA_Callback
  : public ::OASIS::PIN::Instruction_Callback3 <MemoryWriteEA_Callback,
                                                IARG_THREAD_ID,
                                                IARG_MEMORYWRITE_EA,
                                                IARG_MEMORYWRITE_SIZE>
{
public:
  static const unsigned int STORE = 2;

  /// Initializing constructor.
  MemoryWriteEA_Callback (std::map <ADDRINT, unsigned int> & memory);

  /// Destructor
  ~MemoryWriteEA_Callback (void);

  /// analyze hook
  void handle_analyze (THREADID tid, ADDRINT memea, UINT32 length);

private:
  /// The memory
  std::map <ADDRINT, unsigned int> & memory_;
};

/**
 * Code Callback
 */
class Code_Callback
  : public ::OASIS::PIN::Instruction_Callback2 <Code_Callback,
                                                IARG_THREAD_ID,
                                                IARG_INST_PTR>
{
public:
  static const unsigned int CODE = 4;

  /// Initializing constructor.
  Code_Callback (std::map <ADDRINT, unsigned int> & memory, ACE_UINT32 ins_bytes);

  /// Destructor
  ~Code_Callback (void);

  /// analyze hook
  void handle_analyze (THREADID tid, ADDRINT memea);

private:
  /// The memory
  std::map <ADDRINT, unsigned int> & memory_;

  /// Number of bytes in the instruction
  ACE_UINT32 ins_bytes_;
};


/**
 * @class Memory_Footprint_Probe_Impl
 *
 * PINtool which captures instruction addresses
 */
class MEMORY_FOOTPRINT_PROBE_IMPL_Export Memory_Footprint_Probe_Impl
  : public ::OASIS::PIN::Trace_Probe,
    public ::OASIS::PIN::Memory_Footprint_ProbeImpl
{
public:
  /// Default constructor.
  Memory_Footprint_Probe_Impl (void);

  /// Destructor.
  virtual ~Memory_Footprint_Probe_Impl (void);

  /// init
  virtual int init (const char * params, const char * name = 0);

  /// handle_collect_data
  virtual int handle_collect_data (void);

  /// PIN instrumentation
  void setup_trace (Trace_Builder & builder);

  static VOID MF_fini (VOID * obj);
  void probe_fini (void);

private:
  /// The instruction builder
  ::OASIS::PIN::Instruction_Builder builder_;

  /// The pin callbacks
  MemoryReadEA_Callback load_callback_;
  MemoryRead2EA_Callback load2_callback_;
  MemoryWriteEA_Callback store_callback_;
  std::list <Code_Callback> code_callbacks_;

  // The memory state
  std::map <ADDRINT, unsigned int> memory_;
};

/// Type definition for the software probe's factory
typedef ::OASIS::Software_Probe_Factory_T <Memory_Footprint_Probe_Impl>
 Memory_Footprint_Probe_Impl_Factory;

/// Export the interface for the software probe factory.
OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_DECL (MEMORY_FOOTPRINT_PROBE_IMPL_Export,
                                          create_OASIS_PIN_Memory_Footprint_Probe_Impl_Factory);

} // namespace PIN
} // namespace OASIS

#if defined (__OASIS_INLINE__)
#include "Memory_Footprint_Probe_Impl.inl"
#endif  // !defined __OASIS_INLINE__

#endif  // _OASIS_PIN_MEMORY_FOOTPRINT_PROBE_IMPL_H_
