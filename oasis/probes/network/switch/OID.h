// -*- C++ -*-

//==============================================================================
/**
 *  @file        OID.h
 *
 *  $Id: OID.h 2214 2012-08-10 15:00:08Z dfeiock $
 *
 *  @author      INSERT NAME HERE
 */
//==============================================================================

#ifndef _OASIS_NETWORK_SWITCH_OID_H_
#define _OASIS_NETWORK_SWITCH_OID_H_

#include <stdexcept>
#include "oasis/config.h"
#include "SwitchProbe_stub_export.h"

#include "ace/OS.h"

#include "net-snmp/net-snmp-config.h"
#include "net-snmp/net-snmp-includes.h"

namespace OASIS
{
namespace Network
{
namespace Switch
{

/**
 * @class Read_Error
 *
 * Exception thrown when attempting to read the value incorrectly.
 */
class OASIS_SWITCHPROBE_STUB_Export Read_Error :
  public std::exception
{
public:
  /// Default Constructor
  Read_Error (void);

  /// Destructor
  virtual ~Read_Error (void) throw ();
};

/**
 * @class Snmp_Error
 *
 * Exception thrown when an SNMP call fails.
 */
class OASIS_SWITCHPROBE_STUB_Export Snmp_Error :
  public std::exception
{
public:
  /// Default Constructor
  Snmp_Error (void);

  /// Destructor
  virtual ~Snmp_Error (void) throw ();
};

/**
 * @class OID
 *
 * Class to represent a single OID to query for using SNMP
 */
class OASIS_SWITCHPROBE_STUB_Export OID
{
public:
  /// Default constructor
  OID (void);

  /// Initalizing constructor
  OID (const char * name);

  /// Destructor.
  ~OID (void);

  /// Initalize the OID
  void init (const char * name);

  /// Name getter
  const char * name (void);

  /// Internal query getter
  oid * query (void);

  /// Query length getter
  size_t query_length (void);

  /// Value setter
  void value (netsnmp_variable_list & varlist);

  /// Value getters
  const char * as_string (void);

  long as_long (void);

private:
  // The OID name
  const char * name_;

  // The translated OID
  oid query_ [MAX_OID_LEN];

  // The oid length
  size_t query_length_;

  // The queried value
  netsnmp_variable_list value_;
};

} // namespace OASIS
} // namespace Network
} // namespace Switch

#if defined (__OASIS_INLINE__)
#include "OID.inl"
#endif  // !defined __OASIS_INLINE__

#endif  // _OASIS_NETWORK_SWITCH_OID_H_
