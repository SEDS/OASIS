// $Id: OID.cpp 2214 2012-08-10 15:00:08Z dfeiock $

#include "OID.h"

#if !defined (__OASIS_INLINE__)
#include "OID.inl"
#endif  // !defined __OASIS_INLINE__

namespace OASIS
{
namespace Network
{
namespace Switch
{

//
// OID
//
OID::OID (const char * oid)
: name_ (oid),
  query_length_ (MAX_OID_LEN)
{
  // Translate the oid string
  if (!read_objid (oid, this->query_, &this->query_length_))
  {
    snmp_perror ("get_node");
    throw Snmp_Error ();
  }
}

//
// init
//
void OID::init (const char * oid)
{
  this->name_ = oid;
  this->query_length_ = MAX_OID_LEN;

  // Translate the oid string
  if (!read_objid (oid, this->query_, &this->query_length_))
  {
    snmp_perror ("get_node");
    throw Snmp_Error ();
  }

}

//
// value
//
void
OID::value (netsnmp_variable_list & value)
{
  this->value_ = value;
}

//
// as_string
//
const char *
OID::as_string (void)
{
  if (this->value_.type != ASN_OCTET_STR)
    throw Read_Error ();

  // SNMP strings are not null terminated, have to copy the values
  char * result = (char *)ACE_OS::malloc (1 + this->value_.val_len);
  ACE_OS::memcpy (result, this->value_.val.string, this->value_.val_len);
  result [this->value_.val_len] = '\0';
  return result;
}

//
// as_long
//
long
OID::as_long (void)
{
  if (this->value_.type == ASN_INTEGER
      || this->value_.type == ASN_TIMETICKS
      || this->value_.type == ASN_GAUGE
      || this->value_.type == ASN_COUNTER)
    return *this->value_.val.integer;

  throw Read_Error ();
}

} // namespace OASIS
} // namespace Network
} // namespace Switch
