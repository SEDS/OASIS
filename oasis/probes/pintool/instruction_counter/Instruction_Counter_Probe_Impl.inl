// -*- C++ -*-
// $Id: Instruction_Counter_Probe_Impl.inl 2242 2013-08-22 15:38:08Z dfeiock $

namespace OASIS
{
namespace PIN
{

//
// Instruction_Counter_Probe_Impl
//
OASIS_INLINE
Instruction_Counter_Probe_Impl::Instruction_Counter_Probe_Impl (void)
  : all_callback_ (this->all_),
    predicated_callback_ (this->predicated_)
{

}

//
// ~Instruction_Counter_Probe_Impl
//
OASIS_INLINE
Instruction_Counter_Probe_Impl::~Instruction_Counter_Probe_Impl (void)
{

}

//
// Instruction_Counter_Callback
//
OASIS_INLINE
Instruction_Counter_Callback::Instruction_Counter_Callback (ACE_INT32 & count)
  : count_ (count)
{

}

//
// ~Instruction_Counter_Callback
//
OASIS_INLINE
Instruction_Counter_Callback::~Instruction_Counter_Callback (void)
{

}

//
// handle_pin
//
OASIS_INLINE
void
Instruction_Counter_Callback::handle_analyze (void)
{
#ifndef OASIS_PERF_NO_PAYLOAD
  ++this->count_
#endif
}

} // namespace OASIS
} // namespace PIN
