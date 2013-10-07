// -*- C++ -*-

//=============================================================================
/**
 *  @file     Instances_Table.h
 *
 *  $Id: Instances_Table.h 2197 2012-06-04 20:12:04Z dfeiock $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DAC_INSTANCES_TABLE_H_
#define _OASIS_DAC_INSTANCES_TABLE_H_

#include "ace/UUID.h"
#include <string>
#include <vector>

#include "DAC_Core_export.h"

namespace OASIS
{
// Forward decl.
class Software_Probe_Metadata;
class Software_Probe_Instance;

namespace DAC
{
// Forward decl.
class Database;

/**
 * @class Instances_Table
 *
 * Wrapper class for the instances table.
 */
class OASIS_DAC_CORE_Export Instances_Table
{
public:
  /// Create the table in the specified database.
  static void _create (Database & db);

  /**
   * Initializing constructor.
   */
  Instances_Table (Database & db);

  /// Destructor.
  ~Instances_Table (void);

  /**
   * Insert a software probe instance into the table.
   *
   * @param[in]       name              Instance's name
   * @param[in]       metatype          Software probe type's uuid
   * @param[in]       einode            Parent EINode's uuid
   */
  void insert_instance (const std::string & name,
                        const ACE_Utils::UUID & metatype,
                        const std::string & einode);

  /**
   * Insert a software probe instance into the table.
   *
   * @param[in]       name              Probe's name
   * @param[in]       type              Probe's type
   * @param[in]       einode            Parent EINode's uuid
   */
  void insert (const char * name,
               const ACE_Utils::UUID & type,
               const char * einode);

  /**
   * Insert a new typename into the database. If the typename
   * already exists, then nothing happens.
   *
   * @param[in]       name              Type name
   */
  int insert_typename (const char * name);

  /**
   * Get the probe instances from the database.
   */
  void probe_instances (std::vector < Software_Probe_Instance > & instances);

private:
  /// Connection to the target database.
  Database & db_;
};

}
}

#endif  // !defined _OASIS_DAC_INSTANCES_TABLE_H_
