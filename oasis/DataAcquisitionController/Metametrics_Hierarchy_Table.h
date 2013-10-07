// -*- C++ -*-

//=============================================================================
/**
 *  @file     Metametrics_Hierarchy_Table.h
 *
 *  $Id: Metametrics_Hierarchy_Table.h 1884 2011-08-28 20:14:39Z hillj $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DAC_METAMETRICS_HIERARCHY_TABLE_H_
#define _OASIS_DAC_METAMETRICS_HIERARCHY_TABLE_H_

#include "DAC_Core_export.h"

namespace OASIS
{
namespace DAC
{
// Forward decl.
class Database;

/**
 * @class Metametrics_Hierarchy_Table
 *
 * Wrapper class for the metametric hierarchy table. This table stores
 * the hierarchical relations of different software probes.
 */
class OASIS_DAC_CORE_Export Metametrics_Hierarchy_Table
{
public:
  /**
   * Create the metametrics hierarchy table.
   *
   * @param[in]           conn          Connection to the database.
   */
  static void _create (Database & db);

  /**
   * Initializing constructor.
   */
  Metametrics_Hierarchy_Table (Database & db);

  /// Destructor.
  ~Metametrics_Hierarchy_Table (void);

  /**
   * Insert a new hierarchy into the database.
   *
   * @param[in]           type          Parent type name
   * @param[in]           base          Base type name
   */
  void insert_hierarchy (const char * type, const char * base);

private:
  /// Connection to the target database.
  Database & db_;
};

}
}

#endif  // !defined _OASIS_DAC_METAMETRICS_HIERARCHY_TABLE_H_
