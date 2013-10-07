// -*- C++ -*-

//=============================================================================
/**
 *  @file     EINodes_Table_Table.h
 *
 *  $Id: EINodes_Table.h 2086 2011-12-31 07:55:38Z hillj $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DAC_EINODE_TABLE_H_
#define _OASIS_DAC_EINODE_TABLE_H_

#include "ace/UUID.h"
#include <vector>

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
 * @class EINodes_Table
 *
 * Wrapper class for the einodes table.
 */
class OASIS_DAC_CORE_Export EINodes_Table
{
public:
  /// Create the table in the specified database.
  static void _create (Database & db);

  /**
   * Initializing constructor.
   */
  EINodes_Table (Database & db);

  /// Destructor.
  ~EINodes_Table (void);

  /**
   * Insert an einode into the table.
   *
   * @param[in]       uuid        EINode's uuid
   * @param[in]       name        EINode's name
   */
  void insert_einode (const std::string & uuid,
                      const std::string & name);

  /**
   * Insert an einode into the table.
   *
   * @param[in]       uuid        EINode's uuid
   * @param[in]       name        EINode's name
   */
  void insert (const char * uuid, const char * name);

  /**
   * Get the einode's name for the specified UUID.
   *
   * @param[in]       uuid        EINode's uuid
   */
  void einode_name (const ACE_Utils::UUID & uuid,
                    ACE_CString & name);

  /**
   * Get the probe instances which belong to
   * the specified einode.
   */
  void einode_probes (const ACE_Utils::UUID & uuid,
                      std::vector <std::pair
                      <ACE_CString, ACE_CString > > & instances);

private:
  /// Connection to the target database.
  Database & db_;
};

}
}

#endif  // !defined _OASIS_DAC_EINODE_TABLE_H_
