// $Id: Metametrics_Hierarchy_Table.cpp 1884 2011-08-28 20:14:39Z hillj $

#include "Metametrics_Hierarchy_Table.h"
#include "Metametrics_Table.h"
#include "Database.h"

#include "adbc/SQLite/Connection.h"
#include "adbc/SQLite/Query.h"

namespace OASIS
{
namespace DAC
{

//
// _create
//
void Metametrics_Hierarchy_Table::_create (Database & database)
{
  static const char * __query_str__ =
    "CREATE TABLE IF NOT EXISTS oasis_metametrics_hierarchy ("
      "mhid INTEGER PRIMARY KEY autoincrement,"
      "probe INTEGER NOT NULL,"
      "base_probe INTEGER NOT NULL,"
      "FOREIGN KEY (probe) REFERENCES oasis_metametrics (mmid),"
      "FOREIGN KEY (base_probe) REFERENCES oasis_metametrics (mmid),"
      "UNIQUE (probe, base_probe)"
    ")";

  ADBC::SQLite::Query q (database.get_connection ());
  q.execute_no_record (__query_str__);
}

//
// Metametrics_Hierarchy_Table
//
Metametrics_Hierarchy_Table::
Metametrics_Hierarchy_Table (Database & db)
: db_ (db)
{

}

//
// ~Metametrics_Hierarchy_Table
//
Metametrics_Hierarchy_Table::~Metametrics_Hierarchy_Table (void)
{

}

//
// insert_hierarchy
//
void Metametrics_Hierarchy_Table::
insert_hierarchy (const char * type, const char * base)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - inserting %s : %s into hierarchy table\n"),
              type,
              base));

  // First, let's make sure both the typenames are in the database.
  Metametrics_Table metametrics (this->db_);
  metametrics.insert_typename (type);
  metametrics.insert_typename (base);

  // This is a really slow implementation for inserting values into the
  // database. Eventually, we need to convert this to a stored procedure
  // so its easier to interact with the database.
  static const char * __sqlstr__ =
    "INSERT INTO oasis_metametrics_hierarchy (probe, base_probe) "
    "VALUES ((SELECT typeid FROM oasis_typenames WHERE typename = ?), "
    "(SELECT typeid FROM oasis_typenames WHERE typename = ?))";

  ADBC::SQLite::Query insert_stmt (this->db_.get_connection ());
  insert_stmt.prepare (__sqlstr__);

  // Set the parameters for the insert statement.
  using ADBC::SQLite::Parameter_List;
  Parameter_List & params = insert_stmt.parameters ();

  params[0].bind (type, -1);
  params[1].bind (base, -1);

  // Execute the SQL statement.
  insert_stmt.execute_no_record ();
}

}
}
