// -*- C++ -*-

//=============================================================================
/**
 *  @file     Metametrics_Table.h
 *
 *  $Id: Metametrics_Table.h 2207 2012-06-08 20:02:32Z dfeiock $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DAC_METAMETRICS_TABLE_H_
#define _OASIS_DAC_METAMETRICS_TABLE_H_

#include "ace/UUID.h"

#include "DAC_Core_export.h"

namespace OASIS
{
// Forward decl.
class Software_Probe_Metadata;

namespace DAC
{
// Forward decl.
class Database;

/**
 * @class Metametrics_Table
 *
 * Wrapper class for the metametics table.
 */
class OASIS_DAC_CORE_Export Metametrics_Table
{
public:
  /// Create the table in the specified database.
  static void _create (Database & db);

  /**
   * Initializing constructor.
   */
  Metametrics_Table (Database & db);

  /// Destructor.
  ~Metametrics_Table (void);

  /**
   * Insert a software probe's metadata into the table.
   *
   * @param[in]       metadata          Software probe metadata
   */
  void insert_metadata (const Software_Probe_Metadata & metadata);

  /**
   * Insert a software probe's metadata into the table.
   *
   * @param[in]       uuid              Unique type id
   * @param[in]       name              Type name of the probe
   * @param[in]       version_major     Major version number
   * @param[in]       version_minor     Minor version number
   * @param[in]       schema            XML schema definition
   */
  void insert (const ACE_Utils::UUID & uuid,
               const char * name,
               int version_major,
               int version_minor,
               const char * schema);

  /**
   * Insert a new typename into the database. If the typename
   * already exists, then nothing happens.
   *
   * @param[in]       name              Type name
   */
  int insert_typename (const char * name);

  /**
   * Get the schema for the provided probe instance
   */
  void schema (const char * instance_name,
               const char * einode,
               ACE_CString & schema);

private:
  /// Connection to the target database.
  Database & db_;
};

}
}

#endif  // !defined _OASIS_DAC_METAMETRICS_TABLE_H_
