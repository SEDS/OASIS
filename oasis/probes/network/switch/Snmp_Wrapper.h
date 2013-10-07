// -*- C++ -*-

//==============================================================================
/**
 *  @file        Snmp_Wrapper.h
 *
 *  $Id: Snmp_Wrapper.h 2214 2012-08-10 15:00:08Z dfeiock $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_NETWORK_SWITCH_SNMP_WRAPPER_H_
#define _OASIS_NETWORK_SWITCH_SNMP_WRAPPER_H_

#include "oasis/config.h"

#include "ace/OS.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/Thread_Mutex.h"

#include "OID.h"
#include "SwitchProbe_stub_export.h"

#include "net-snmp/net-snmp-config.h"
#include "net-snmp/net-snmp-includes.h"

namespace OASIS
{
namespace Network
{
namespace Switch
{

/**
 * @class Snmp_Wrapper
 *
 * Basic wrapper class for net-snmp related operations
 */
class OASIS_SWITCHPROBE_STUB_Export Snmp_Wrapper
{
public:
  /// OID storage typedef
  typedef
    ACE_Hash_Map_Manager <ACE_CString,
                          OID *,
                          ACE_Thread_Mutex> OIDs;

  /// Default constructor.
  Snmp_Wrapper (void);

  /// Destructor.
  ~Snmp_Wrapper (void);

  /// Initalize the object
  int init (const char * host, const char * community);

  /// Add OID to request
  int add_oid (OID & oid);

  /// Run the query
  int query (void);

private:
  // Helper method for stringifying an oid
  void stringify_oid (oid * src, size_t src_len, ACE_CString & dest);

  // Session the snmp queries
  netsnmp_session session_config_;

  // Opened session for snmp
  netsnmp_session * session_;

  // Request PDU (used for cloning)
  netsnmp_pdu * request_config_;

  // Request PDU (used for execution)
  netsnmp_pdu * request_;

  // Response PDU
  netsnmp_pdu * response_;

  // OIDs to query for
  OIDs oids_;
};

} // namespace OASIS
} // namespace Network
} // namespace Switch

#if defined (__OASIS_INLINE__)
#include "Snmp_Wrapper.inl"
#endif  // !defined __OASIS_INLINE__

#endif  // _OASIS_NETWORK_SWITCH_SNMP_WRAPPER_H_
