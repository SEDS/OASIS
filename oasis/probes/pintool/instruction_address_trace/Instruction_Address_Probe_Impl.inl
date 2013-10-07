// -*- C++ -*-
// $Id: Instruction_Address_Probe_Impl.inl 2242 2013-08-22 15:38:08Z dfeiock $

namespace OASIS
{
namespace PIN
{

//
// Instruction_Address_Probe_Impl
//
OASIS_INLINE
Instruction_Address_Probe_Impl::Instruction_Address_Probe_Impl (void)
  : callback_ (this->address_)
{

}

//
// ~Instruction_Address_Probe_Impl
//
OASIS_INLINE
Instruction_Address_Probe_Impl::~Instruction_Address_Probe_Impl (void)
{

}

//
// Instruction_Address_Callback
//
OASIS_INLINE
Instruction_Address_Callback::Instruction_Address_Callback (ACE_UINT64 & address)
  : address_ (address)
{

}

//
// ~Instruction_Address_Callback
//
OASIS_INLINE
Instruction_Address_Callback::~Instruction_Address_Callback (void)
{

}

//
// handle_pin
//
OASIS_INLINE
void
Instruction_Address_Callback::handle_analyze (VOID * ip)
{
#ifndef OASIS_PERF_NO_PAYLOAD
  this->address_ = (ACE_UINT64) ip;
#endif
}

} // namespace OASIS
} // namespace PIN
