// $Id: EINodes_Table.cpp 2086 2011-12-31 07:55:38Z hillj $

#include "EINodes_Table.h"
#include "Database.h"

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
void EINodes_Table::_create (Database & database)
{
  static const char * __einodes_table__ =
    "CREATE TABLE IF NOT EXISTS oasis_einodes ("
    "eid INTEGER PRIMARY KEY autoincrement,"
    "uuid CHAR(36) UNIQUE NOT NULL,"
    "name VARCHAR UNIQUE NOT NULL)";

  ADBC::SQLite::Query q (database.get_connection ());
  q.execute_no_record (__einodes_table__);
}

//
// EINodes_Table
//
EINodes_Table::EINodes_Table (Database & db)
: db_ (db)
{

}

//
// ~EINodes_Table
//
EINodes_Table::~EINodes_Table (void)
{

}

//
// insert_metadata
//
void EINodes_Table::
insert_einode (const std::string & uuid, const std::string & name)
{
  this->insert (uuid.c_str (),
                name.c_str ());
}

//
// insert
//
void EINodes_Table::
insert (const char * uuid, const char * name)
{
  static const char * __sqlstr__ =
    "INSERT INTO oasis_einodes "
    "(uuid, name) "
    "VALUES (?, ?)";

  ADBC::SQLite::Query q (this->db_.get_connection ());
  q.prepare (__sqlstr__);

  using ::ADBC::SQLite::Parameter_List;
  Parameter_List & params = q.parameters ();

  params[0].bind (uuid, -1);
  params[1].bind (name, -1);

  q.execute_no_record ();
}

//
// name
//
void EINodes_Table::
einode_name (const ACE_Utils::UUID & uuid, ACE_CString & name)
{
  static const char * __sqlstr__ =
    "SELECT name FROM oasis_einodes "
    "WHERE uuid = ?";

  ADBC::SQLite::Query q (this->db_.get_connection ());
  q.prepare (__sqlstr__);

  using ::ADBC::SQLite::Parameter_List;
  Parameter_List & params = q.parameters ();
  params[0].bind (uuid.to_string ()->c_str (), -1);

  ::ADBC::SQLite::Record & record = q.execute ();
  record.get_data (0, name);
}

//
// instances
//
void EINodes_Table::
einode_probes (const ACE_Utils::UUID & uuid,
               std::vector <std::pair
                 <ACE_CString, ACE_CString > > & instances)
{
  static const char * __instances_sql__ =
    "SELECT i.iid FROM oasis_instances i, oasis_einodes e "
    "WHERE e.uuid = ? and i.einode = e.eid";

  static const char * __probe_name_sql__ =
    "SELECT t.typename FROM oasis_typenames t, "
    "oasis_instances i WHERE i.iid = ? AND "
    "i.name = t.typeid";

  static const char * __probe_uuid_sql__ =
    "SELECT m.uuid FROM oasis_instances i, "
    "oasis_metametrics m WHERE i.iid = ? AND "
    "i.metatype = m.mmid";

  ADBC::SQLite::Query q (this->db_.get_connection ());
  q.prepare (__instances_sql__);

  using ::ADBC::SQLite::Parameter_List;
  Parameter_List & params = q.parameters ();
  params[0].bind (uuid.to_string ()->c_str (), -1);

  // Get the instance ids
  ADBC::SQLite::Record & record = q.execute ();
  ACE_CString name, type, iid;
  ADBC::SQLite::Query subq (this->db_.get_connection ());

  for ( ; !record.done (); record.advance ())
  {
    record.get_data (0, iid);

    // Get the probe name
    subq.prepare (__probe_name_sql__);
    Parameter_List & name_params = subq.parameters ();
    name_params[0].bind (iid.c_str (), -1);
    ADBC::SQLite::Record & name_record = subq.execute ();
    name_record.get_data (0, name);
    subq.reset ();

    // Get the probe type
    subq.prepare (__probe_uuid_sql__);
    Parameter_List & type_params = subq.parameters ();
    type_params[0].bind (iid.c_str (), -1);
    ADBC::SQLite::Record & type_record = subq.execute ();
    type_record.get_data (0, type);
    subq.reset ();

    // Build the pair and push them on the vector
    instances.push_back (std::pair <ACE_CString, ACE_CString> (type, name));
  }
}

}
}
