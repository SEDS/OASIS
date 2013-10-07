// -*- C++ -*-
// $Id: Snmp_Wrapper.inl 2214 2012-08-10 15:00:08Z dfeiock $

namespace OASIS
{
namespace Network
{
namespace Switch
{

//
// Snmp_Wrapper
//
OASIS_INLINE
Snmp_Wrapper::Snmp_Wrapper (void)
: session_ (0),
  request_ (0),
  response_ (0)
{

}

} // namespace OASIS
} // namespace Network
} // namespace Switch
