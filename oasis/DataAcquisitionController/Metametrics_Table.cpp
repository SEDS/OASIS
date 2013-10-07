// $Id: Metametrics_Table.cpp 2207 2012-06-08 20:02:32Z dfeiock $

#include "Metametrics_Table.h"
#include "Database.h"

#include "oasis/probes/Software_Probe_Metadata.h"

#include "adbc/SQLite/Connection.h"
#include "adbc/SQLite/Exception.h"
#include "adbc/SQLite/Query.h"

#include "ace/UUID.h"
#include "ace/CORBA_macros.h"

namespace OASIS
{
namespace DAC
{

//
// _create
//
void Metametrics_Table::_create (Database & database)
{
  static const char * __typename_table__ =
    "CREATE TABLE IF NOT EXISTS oasis_typenames ("
    "typeid INTEGER PRIMARY KEY autoincrement,"
    "typename VARCHAR UNIQUE NOT NULL)";

  static const char * __metametrics_table__ =
    "CREATE TABLE IF NOT EXISTS oasis_metametrics ("
    "mmid INTEGER PRIMARY KEY autoincrement,"
    "uuid CHAR(36) UNIQUE NOT NULL,"
    "name INTEGER NOT NULL,"
    "version_major INTEGER DEFAULT 1,"
    "version_minor INTEGER DEFAULT 0,"
    "schema VARCHAR NOT NULL,"
    "FOREIGN KEY (name) REFERENCES oasis_typenames (typeid))";

  ADBC::SQLite::Query q (database.get_connection ());
  q.execute_no_record (__typename_table__);
  q.execute_no_record (__metametrics_table__);
}

//
// Metametrics_Table
//
Metametrics_Table::Metametrics_Table (Database & db)
: db_ (db)
{

}

//
// ~Metametrics_Table
//
Metametrics_Table::~Metametrics_Table (void)
{

}

//
// insert_metadata
//
void Metametrics_Table::
insert_metadata (const Software_Probe_Metadata & metadata)
{
  this->insert (metadata.uuid_,
                metadata.type_info_.c_str (),
                metadata.version_major_,
                metadata.version_minor_,
                metadata.schema_.c_str ());
}

//
// insert
//
void Metametrics_Table::
insert (const ACE_Utils::UUID & uuid,
        const char * name,
        int version_major,
        int version_minor,
        const char * schema)
{
  // First, let's make sure the typename is already in the database.
  this->insert_typename (name);

  // Now, let's insert the metametrics into the database.
  static const char * __sqlstr__ =
    "INSERT INTO oasis_metametrics "
    "(uuid, name, version_major, version_minor, schema) "
    "VALUES (?, (SELECT typeid FROM oasis_typenames WHERE typename = ?), ?, ?, ?)";

  ADBC::SQLite::Query q (this->db_.get_connection ());
  q.prepare (__sqlstr__);

  using ::ADBC::SQLite::Parameter_List;
  Parameter_List & params = q.parameters ();

  params[0].bind (uuid.to_string ()->c_str (), -1);
  params[1].bind (name, -1);
  params[2].bind (&version_major);
  params[3].bind (&version_minor);
  params[4].bind (schema, -1);

  // Execute the query.
  q.execute_no_record ();
}

//
// insert_typename
//
int Metametrics_Table::insert_typename (const char * name)
{
  try
  {
    ADBC::SQLite::Query q (this->db_.get_connection ());
    q.prepare ("INSERT INTO oasis_typenames (typename) VALUES (?)");
    q.parameters ()[0].bind (name, -1);
    q.execute_no_record ();

    return 0;
  }
  catch (const ADBC::SQLite::Exception & ex)
  {
    // We only accept the constraint violation error since it
    // typically means the name was already present in the database.
    if (SQLITE_CONSTRAINT != ex.native ())
      throw;
  }

  return 1;
}

//
// schema
//
void Metametrics_Table::
schema (const char * instance_name,
        const char * einode,
        ACE_CString & schema)
{
  static const char * __sqlstr__ =
    "SELECT m.schema "
    "FROM oasis_metametrics m, oasis_instances i, oasis_einodes e, oasis_typenames t "
    "WHERE t.typename = ? AND e.name = ? "
    "AND t.typeid = i.name AND e.eid = i.einode AND m.mmid = i.metatype";

  try
  {
    ADBC::SQLite::Query q (this->db_.get_connection ());
    q.prepare (__sqlstr__);
    q.parameters ()[0].bind (instance_name, -1);
    q.parameters ()[1].bind (einode, -1);

    ADBC::SQLite::Record & record = q.execute ();
    record.get_data (0, schema);
  }
  catch (const ADBC::SQLite::Exception & ex)
  {
    // We only accept the constraint violation error since it
    // typically means the name was already present in the database.
    if (SQLITE_CONSTRAINT != ex.native ())
      throw;
  }
}

}
}
