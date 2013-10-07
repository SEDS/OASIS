// -*- C++ -*-
// $Id: OID.inl 2214 2012-08-10 15:00:08Z dfeiock $

namespace OASIS
{
namespace Network
{
namespace Switch
{

//
// Read_Error
//
OASIS_INLINE
Read_Error::Read_Error (void)
{

}

//
// ~Read_Error
//
OASIS_INLINE
Read_Error::~Read_Error (void) throw ()
{

}

//
// Snmp_Error
//
OASIS_INLINE
Snmp_Error::Snmp_Error (void)
{

}

//
// ~Snmp_Error
//
OASIS_INLINE
Snmp_Error::~Snmp_Error (void) throw ()
{

}

//
// OID
//
OASIS_INLINE
OID::OID (void)
{

}

//
// ~OID
//
OASIS_INLINE
OID::~OID (void)
{

}

//
// name
//
OASIS_INLINE
const char *
OID::name (void)
{
  return this->name_;
}

//
// query
//
OASIS_INLINE
oid *
OID::query (void)
{
  return this->query_;
}

//
// query_length
//
OASIS_INLINE
size_t
OID::query_length (void)
{
  return this->query_length_;
}

} // namespace OASIS
} // namespace Network
} // namespace Switch
