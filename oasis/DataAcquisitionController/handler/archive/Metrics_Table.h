// -*- C++ -*-

//=============================================================================
/**
 *  @file     Metrics_Table.h
 *
 *  $Id: Metrics_Table.h 2238 2013-03-08 20:50:44Z tmpeiris $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_METRICS_TABLE_H_
#define _OASIS_METRICS_TABLE_H_

#include "ace/Auto_Ptr.h"
#include "ace/UUID.h"
#include "ace/Time_Value.h"

#if defined (OASIS_HAS_TAO)
#include "Metric_Cursor_i.h"
#endif

#include <vector>

namespace ADBC
{
namespace SQLite
{
// Forward decl.
class Query;
}
}

namespace OASIS
{
namespace DAC
{
// Forward decl.
class Database;
}

/**
 * @class Metrics_Table
 */
class Metrics_Table
{
public:
  static void _create (DAC::Database & database);

  /**
   * Initializing constructor.
   */
  Metrics_Table (DAC::Database & database);

  /// Destructor.
  ~Metrics_Table (void);

  /// Insert data
  void insert_metrics (const ACE_Utils::UUID & einode_uuid,
                       const ACE_Utils::UUID & probe_uuid,
                       const ACE_Time_Value & timestamp,
                       ACE_UINT32 sequence_num,
                       ACE_UINT32 state,
                       ACE_UINT32 datasize,
                       const char * blob);

#if defined (OASIS_HAS_TAO)
  /// Query the table and return the remote cursor
  Metric_Cursor_i * get_metric_cursor (const char * __sqlstr__,
                                       std::vector <std::string> & values);
#endif


private:
  void prepare_insert_metrics (void);

  /// Connection to the target database.
  DAC::Database & database_;

  ACE_Auto_Ptr < ::ADBC::SQLite::Query > insert_stmt_;

  char einode_uuid_[37];

  char probe_uuid_[37];

  ACE_INT32 tv_sec_;

  ACE_INT32 tv_usec_;

  ACE_UINT32 sequence_num_;

  ACE_UINT32 state_;

  ACE_UINT32 datasize_;

  /// Pointer to the data blob.
  char * blob_;
};

}

#endif  // !defined _OASIS_METRICS_METADATA_TABLE_H_
