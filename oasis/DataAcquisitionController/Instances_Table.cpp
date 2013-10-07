// $Id: Instances_Table.cpp 2208 2012-06-15 17:51:53Z dfeiock $

#include "Instances_Table.h"
#include "Database.h"

#include "oasis/probes/Software_Probe_Metadata.h"
#include "oasis/probes/Software_Probe_Instance.h"

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
void Instances_Table::_create (Database & database)
{
  static const char * __instances_table__ =
    "CREATE TABLE IF NOT EXISTS oasis_instances ("
    "iid INTEGER PRIMARY KEY autoincrement,"
    "name INTEGER NOT NULL,"
    "metatype INTEGER NOT NULL,"
    "einode INTEGER NOT NULL,"
    "FOREIGN KEY (name) REFERENCES oasis_typenames (typeid),"
    "FOREIGN KEY (metatype) REFERENCES oasis_metametrics (mmid),"
    "FOREIGN KEY (einode) REFERENCES oasis_einodes (eid),"
    "UNIQUE (name, einode))";

  ADBC::SQLite::Query q (database.get_connection ());
  q.execute_no_record (__instances_table__);
}

//
// Instances_Table
//
Instances_Table::Instances_Table (Database & db)
: db_ (db)
{

}

//
// ~Instances_Table
//
Instances_Table::~Instances_Table (void)
{

}

//
// insert_metadata
//
void Instances_Table::
insert_instance (const std::string & name,
                 const ACE_Utils::UUID & metatype,
                 const std::string & einode)
{
  this->insert (name.c_str (),
                metatype,
                einode.c_str ());
}

//
// insert
//
void Instances_Table::
insert (const char * name,
        const ACE_Utils::UUID & type,
        const char * einode)
{
  this->insert_typename (name);
  static const char * __sqlstr__ =
  "INSERT INTO oasis_instances "
  "(name, metatype, einode) "
  "VALUES ( (SELECT typeid from oasis_typenames WHERE typename  = ?),"
    "(SELECT mmid from oasis_metametrics WHERE uuid = ?),"
    "(SELECT eid from oasis_einodes WHERE uuid = ?)"
  ")";

  ADBC::SQLite::Query q (this->db_.get_connection ());
  q.prepare (__sqlstr__);

  using ::ADBC::SQLite::Parameter_List;
  Parameter_List & params = q.parameters ();

  params[0].bind (name, -1);
  params[1].bind (type.to_string ()->c_str (), -1);
  params[2].bind (einode, -1);

  q.execute_no_record ();
}

//
// insert_typename
//
int Instances_Table::insert_typename (const char * name)
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
// probe_instances
//
void Instances_Table::
probe_instances (std::vector < Software_Probe_Instance > & instances)
{
  try
  {
    ADBC::SQLite::Query q (this->db_.get_connection ());
    q.prepare ("select tn.typename, mm.uuid, ein.name, mm_tn.typename "
               "from oasis_typenames tn, oasis_metametrics mm, oasis_instances i, oasis_einodes ein "
               "join (select tn.typename as typename, mm.mmid as mmid "
                 "from oasis_typenames tn, oasis_metametrics mm "
                 "where mm.mmid = tn.typeid) mm_tn on mm_tn.mmid = mm.mmid "
               "where i.name = tn.typeid and i.metatype = mm.mmid and i.einode = ein.eid;");

    // Get the instances
    ADBC::SQLite::Record & record = q.execute ();
    ACE_CString inst_name, inst_uuid, einode_name, inst_type_name;
    for ( ; !record.done (); record.advance ())
    {
      record.get_data (0, inst_name);
      record.get_data (1, inst_uuid);
      record.get_data (2, einode_name);
      record.get_data (3, inst_type_name);

      // Build the instance and push them on the vector
      Software_Probe_Instance instance (inst_name.c_str (),
                                        inst_uuid.c_str (),
                                        inst_type_name.c_str (),
                                        einode_name.c_str ());
      instances.push_back (instance);
    }
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
