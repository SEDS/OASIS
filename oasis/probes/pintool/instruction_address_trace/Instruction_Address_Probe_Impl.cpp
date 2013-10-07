// $Id: Instruction_Address_Probe_Impl.cpp 2239 2013-08-08 15:23:33Z dfeiock $

#include "oasis/tools/PINtool/PINtool.h"

#include "Instruction_Address_Probe_Impl.h"
#if !defined (__OASIS_INLINE__)
#include "Instruction_Address_Probe_Impl.inl"
#endif  // !defined __OASIS_INLINE__

namespace OASIS
{
namespace PIN
{

OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_IMPL (create_OASIS_PIN_Instruction_Address_Probe_Impl_Factory,
                                          Instruction_Address_Probe_Impl_Factory);

//
// setup_instruction
//
void Instruction_Address_Probe_Impl::setup_instruction (Instruction_Builder & builder)
{
  builder.insert_call (IPOINT_BEFORE, &this->callback_);
}

//
// init
//
int Instruction_Address_Probe_Impl::init (const char * args, const char * name)
{
  // Init base probe
  if (0 != ::OASIS::PIN::Instruction_Address_ProbeImpl::init (args, name))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to init\n")),
                       -1);

  if (0 != ::OASIS::PIN::Instruction_Probe::init ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to init\n")),
                       -1);

  return 0;
}

//
// handle_collect_data
//
int Instruction_Address_Probe_Impl::handle_collect_data (void)
{
  return 0;
}

} // namespace OASIS
} // namespace PIN
