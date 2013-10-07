// $Id: Metric_Cursor_i.h 2238 2013-03-08 20:50:44Z tmpeiris $

#ifndef METRIC_CURSOR_I_H_
#define METRIC_CURSOR_I_H_

#include "adbc/SQLite/Record.h"
#include "adbc/SQLite/Query.h"
#include "Archive_ServiceS.h"

namespace OASIS
{
/**
 * @class Metric_Cursor_i
 *
 * Implementation class for the Metric Cursor.
 * service.
 */
class Metric_Cursor_i :
  public POA_OASIS::MetricCursor
{
public:

  /// Initializing constructor
  Metric_Cursor_i (ADBC::SQLite::Query * query,
                   ADBC::SQLite::Record * record);

  /// Destructor.
  ~Metric_Cursor_i (void);

  /// Advance method
  virtual void advance (void);

  /// Terminating condition
  virtual bool is_done (void);

  /// Method to get the size of the data
  virtual ::CORBA::ULong get_data_size (void);

private:

  /// The internal ADBC Query object
  ADBC::SQLite::Query * query_;

  /// The internal data records
  ADBC::SQLite::Record * record_;

};

}

#endif  // !defined METRIC_CURSOR_I_H_
