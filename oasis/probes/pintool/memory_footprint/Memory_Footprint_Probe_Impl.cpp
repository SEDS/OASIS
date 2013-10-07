// $Id: Memory_Footprint_Probe_Impl.cpp 2242 2013-08-22 15:38:08Z dfeiock $

#include "oasis/tools/PINtool/PINtool.h"

#include "Memory_Footprint_Probe_Impl.h"
#if !defined (__OASIS_INLINE__)
#include "Memory_Footprint_Probe_Impl.inl"
#endif  // !defined __OASIS_INLINE__

#include <fstream>

namespace OASIS
{
namespace PIN
{

OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_IMPL (create_OASIS_PIN_Memory_Footprint_Probe_Impl_Factory,
                                          Memory_Footprint_Probe_Impl_Factory);

//
// setup_trace
//
void Memory_Footprint_Probe_Impl::setup_trace (Trace_Builder & builder)
{
  ADDRINT pc = TRACE_Address (builder.trace_);
  for (BBL bbl = TRACE_BblHead (builder.trace_);
       BBL_Valid(bbl);
       bbl = BBL_Next(bbl))
  {
    const INS head = BBL_InsHead (bbl);
    if (! INS_Valid (head)) continue;
    for (INS ins = head; INS_Valid (ins); ins = INS_Next (ins))
    {
      this->builder_.ins (ins);

      // Allocate a new Code_Callback for each instruction
      // since there is state associated with them
      Code_Callback code (this->memory_, INS_Size (ins));
      this->code_callbacks_.push_back (code);
      this->builder_.insert_call <Code_Callback> (IPOINT_BEFORE, &(this->code_callbacks_.back ()));

      // Register the other callbacks
      if (INS_IsMemoryRead (ins))
        this->builder_.insert_call <MemoryReadEA_Callback> (IPOINT_BEFORE, &this->load_callback_);

      if (INS_HasMemoryRead2 (ins))
        this->builder_.insert_call <MemoryRead2EA_Callback> (IPOINT_BEFORE, &this->load2_callback_);

      if (INS_IsMemoryWrite (ins))
        this->builder_.insert_call <MemoryWriteEA_Callback> (IPOINT_BEFORE, &this->store_callback_);
    }
  }
}

//
// init
//
int Memory_Footprint_Probe_Impl::init (const char * args, const char * name)
{
  // Init base probe
  if (0 != ::OASIS::PIN::Memory_Footprint_ProbeImpl::init (args, name))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to init\n")),
                       -1);

/*  if (0 != ::OASIS::PIN::Trace_Probe::init ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to init\n")),
                       -1);
*/
  TRACE_AddInstrumentFunction (&Trace_Probe::trace, this);
  return 0;
}

//
// handle_collect_data
//
int Memory_Footprint_Probe_Impl::handle_collect_data (void)
{
  this->dump (std::cout);
  return 0;
}

} // namespace OASIS
} // namespace PIN
