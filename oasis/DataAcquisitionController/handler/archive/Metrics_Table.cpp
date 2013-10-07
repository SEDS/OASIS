// $Id: Metrics_Table.cpp 2238 2013-03-08 20:50:44Z tmpeiris $

#include "Metrics_Table.h"
#include "oasis/DataAcquisitionController/Database.h"

#include "adbc/SQLite/Connection.h"
#include "adbc/SQLite/Query.h"

#include "ace/UUID.h"
#include "ace/CORBA_macros.h"

namespace OASIS
{
//
// _create
//
void Metrics_Table::_create (DAC::Database & database)
{
  static const char * __query_str__ =
    "CREATE TABLE IF NOT EXISTS oasis_metrics ("
      "mid INTEGER PRIMARY KEY autoincrement,"
      "einode CHAR(36) NOT NULL,"
      "probe INTEGER NOT NULL,"
      "tv_sec INTEGER NOT NULL,"
      "tv_usec INTEGER NOT NULL,"
      "sequence_num INTEGER NOT NULL,"
      "state INTEGER NOT NULL,"
      "datasize INTEGER NOT NULL,"
      "data BLOB,"
      "FOREIGN KEY (probe) REFERENCES oasis_metametrics (mmid)"
    ")";

  ADBC::SQLite::Query q (database.get_connection ());
  q.execute_no_record (__query_str__);
}

//
// Metrics_Table
//
Metrics_Table::Metrics_Table (DAC::Database & database)
: database_ (database)
{
  this->prepare_insert_metrics ();
}

//
// ~Metrics_Table
//
Metrics_Table::~Metrics_Table (void)
{

}

//
// insert_metadata
//
void Metrics_Table::
insert_metrics (const ACE_Utils::UUID & einode_uuid,
                const ACE_Utils::UUID & probe_uuid,
                const ACE_Time_Value & timestamp,
                ACE_UINT32 sequence_num,
                ACE_UINT32 state,
                ACE_UINT32 datasize,
                const char * blob)
{
  // Bind the parameters for the SQL statement.
  using ADBC::SQLite::Parameter_List;
  Parameter_List & params = this->insert_stmt_->parameters ();

  ACE_INT32 tv_sec = static_cast <ACE_INT32> (timestamp.sec ());
  ACE_INT32 tv_usec = timestamp.usec ();

  params[0].bind (einode_uuid.to_string ()->c_str (), -1);
  params[1].bind (probe_uuid.to_string ()->c_str (), -1);
  params[2].bind (&tv_sec);
  params[3].bind (&tv_usec);
  params[4].bind (&sequence_num);
  params[5].bind (&state);
  params[6].bind (&datasize);
  params[7].bind (blob, datasize);

  // Execute the query.
  this->insert_stmt_->execute_no_record ();
  this->insert_stmt_->reset ();
}

//
// prepare_insert_metametrics
//
void Metrics_Table::prepare_insert_metrics (void)
{
  ADBC::SQLite::Query * q = 0;
  ACE_NEW_THROW_EX (q,
                    ADBC::SQLite::Query (this->database_.get_connection ()),
                    ACE_bad_alloc ());
  this->insert_stmt_.reset (q);

  // Prepare the SQL statement.
  static const char * __sqlstr__ =
    "INSERT INTO oasis_metrics "
    "(einode, probe, tv_sec, tv_usec, sequence_num, state, datasize, data) "
    "VALUES (?, (SELECT mmid FROM oasis_metametrics WHERE uuid = ?), ?, ?, ?, ?, ?, ?)";

  this->insert_stmt_->prepare (__sqlstr__);
}

//
// get_metric_cursor
//
#if defined (OASIS_HAS_TAO)
Metric_Cursor_i * Metrics_Table::
get_metric_cursor (const char * __sqlstr__,
                   std::vector <std::string> & values)
{
  // Prpare the query

  ADBC::SQLite::Query * q;

  ACE_NEW_THROW_EX (q,
                    ADBC::SQLite::Query (this->database_.get_connection ()),
                    ACE_bad_alloc ());

  q->prepare (__sqlstr__);

  using ::ADBC::SQLite::Parameter_List;
  Parameter_List & params = q->parameters ();

  for (size_t i = 0; i < params.size (); i++)
  {
    params[i].bind (values[i].c_str (), -1);
  }

  // Execute the query

  ADBC::SQLite::Record * record = &q->execute ();

  Metric_Cursor_i * m_cursor = 0;

  ACE_NEW_THROW_EX (m_cursor,
                    Metric_Cursor_i (q, record),
                    ACE_bad_alloc ());

  return m_cursor;
}
#endif

}
