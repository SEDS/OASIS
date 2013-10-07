// -*- C++ -*-
// $Id: Memory_Footprint_Probe_Impl.inl 2242 2013-08-22 15:38:08Z dfeiock $

namespace OASIS
{
namespace PIN
{

//
// Memory_Footprint_Probe_Impl
//
OASIS_INLINE
Memory_Footprint_Probe_Impl::Memory_Footprint_Probe_Impl (void)
  : builder_ (),
    load_callback_ (this->memory_),
    load2_callback_ (this->memory_),
    store_callback_ (this->memory_)
{

}

//
// ~Memory_Footprint_Probe_Impl
//
OASIS_INLINE
Memory_Footprint_Probe_Impl::~Memory_Footprint_Probe_Impl (void)
{

}

//
// Memory_Footprint_Callback
//
OASIS_INLINE
MemoryReadEA_Callback::
MemoryReadEA_Callback (std::map <ADDRINT, unsigned int> & memory)
  : memory_ (memory)
{

}

//
// ~Memory_Footprint_Callback
//
OASIS_INLINE
MemoryReadEA_Callback::~MemoryReadEA_Callback (void)
{

}

//
// handle_analyze
//
OASIS_INLINE
void
MemoryReadEA_Callback::handle_analyze (THREADID tid, ADDRINT memea, UINT32 length)
{
#ifndef OASIS_PERF_NO_PAYLOAD
  ADDRINT start = ~static_cast<ADDRINT>(15) & memea;
  ADDRINT end = ~static_cast<ADDRINT>(15) & (memea + length - 1);
  for (ADDRINT addr = start; addr <= end; addr += 16)
  {
    map <ADDRINT, unsigned int>::iterator it = this->memory_.find (addr);
    if (it == this->memory_.end ())
      this->memory_[addr] = LOAD;
    else
      this->memory_[addr] = it->second | LOAD;
  }
#endif
}

//
// Memory_Footprint_Callback
//
OASIS_INLINE
MemoryRead2EA_Callback::
MemoryRead2EA_Callback (std::map <ADDRINT, unsigned int> & memory)
  : memory_ (memory)
{

}

//
// ~Memory_Footprint_Callback
//
OASIS_INLINE
MemoryRead2EA_Callback::~MemoryRead2EA_Callback (void)
{

}

//
// handle_analyze
//
OASIS_INLINE
void
MemoryRead2EA_Callback::handle_analyze (THREADID tid, ADDRINT memea, UINT32 length)
{
#ifndef OASIS_PERF_NO_PAYLOAD
  ADDRINT start = ~static_cast<ADDRINT>(15) & memea;
  ADDRINT end = ~static_cast<ADDRINT>(15) & (memea + length - 1);
  for (ADDRINT addr = start; addr <= end; addr += 16)
  {
    map <ADDRINT, unsigned int>::iterator it = this->memory_.find (addr);
    if (it == this->memory_.end ())
      this->memory_[addr] = LOAD;
    else
      this->memory_[addr] = it->second | LOAD;
  }
#endif
}

//
// Memory_Footprint_Callback
//
OASIS_INLINE
MemoryWriteEA_Callback::
MemoryWriteEA_Callback (std::map <ADDRINT, unsigned int> & memory)
  : memory_ (memory)
{

}

//
// ~Memory_Footprint_Callback
//
OASIS_INLINE
MemoryWriteEA_Callback::~MemoryWriteEA_Callback (void)
{

}

//
// handle_analyze
//
OASIS_INLINE
void
MemoryWriteEA_Callback::handle_analyze (THREADID tid, ADDRINT memea, UINT32 length)
{
#ifndef OASIS_PERF_NO_PAYLOAD
  ADDRINT start = ~static_cast<ADDRINT>(15) & memea;
  ADDRINT end = ~static_cast<ADDRINT>(15) & (memea + length - 1);
  for (ADDRINT addr = start; addr <= end; addr += 16)
  {
    map <ADDRINT, unsigned int>::iterator it = this->memory_.find (addr);
    if (it == this->memory_.end ())
      this->memory_[addr] = STORE;
    else
      this->memory_[addr] = it->second | STORE;
  }
#endif
}

//
// Memory_Footprint_Callback
//
OASIS_INLINE
Code_Callback::
Code_Callback (std::map <ADDRINT, unsigned int> & memory,
               ACE_UINT32 ins_bytes)
  : memory_ (memory),
    ins_bytes_ (ins_bytes)
{

}

//
// ~Memory_Footprint_Callback
//
OASIS_INLINE
Code_Callback::~Code_Callback (void)
{

}

//
// handle_analyze
//
OASIS_INLINE
void
Code_Callback::handle_analyze (THREADID tid, ADDRINT memea)
{
#ifndef OASIS_PERF_NO_PAYLOAD
  ADDRINT start = ~static_cast<ADDRINT>(15) & memea;
  ADDRINT end = ~static_cast<ADDRINT>(15) & (memea + this->ins_bytes_ - 1);
  for (ADDRINT addr = start; addr <= end; addr += 16)
  {
    map <ADDRINT, unsigned int>::iterator it = this->memory_.find (addr);
    if (it == this->memory_.end ())
      this->memory_[addr] = CODE;
    else
      this->memory_[addr] = it->second | CODE;
  }
#endif
}


} // namespace OASIS
} // namespace PIN
