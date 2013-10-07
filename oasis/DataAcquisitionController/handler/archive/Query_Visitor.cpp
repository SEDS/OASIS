#include "Query_Visitor.h"

namespace OASIS
{

//
// Query_Visitor
//
Query_Visitor::Query_Visitor (void)
{
}

//
// ~Query_Visitor
//
Query_Visitor::~Query_Visitor (void)
{

}

//
// visit_query
//
void Query_Visitor::visit_query (Query_i * query)
{
  return;
}

//
// visit_probe_query
//
void Query_Visitor::visit_probe_query (ProbeQuery_i * p_query)
{
  static const char * probe_sql =
      "SELECT datasize, data from oasis_metrics m, oasis_typenames t, oasis_instances i "
      "WHERE t.typename = ? AND t.typeid = i.name AND i.iid = m.probe;";

  std::string name (p_query->name ());
  this->values_.push_back (name);

  this->sqlstr_ << probe_sql;

  return;
}

//
// visit_einode_query
//
void Query_Visitor::visit_einode_query (EINodeQuery_i * e_query)
{
  static const char * einode_sql =
      "SELECT datasize, data from oasis_metrics m, oasis_einodes e "
      "WHERE e.uuid = m.einode AND e.name = ?;";

  std::string name (e_query->name ());
  this->values_.push_back (name);

  this->sqlstr_ << einode_sql;

  return;
}

//
// visit_time_query
//
void Query_Visitor::visit_time_query (TimeQuery_i * t_query)
{
  return;
}

//
// visit_time_after_query
//
void Query_Visitor::visit_time_after_query (TimeAfterQuery_i * ta_query)
{
  static const char * time_sql =
      "SELECT datasize, data from oasis_metrics m "
      "WHERE m.tv_sec >= ? AND m.tv_usec >= ?;";

  long time_sec = ta_query->sec ();
  long time_usec = ta_query->usec ();

  std::stringstream s1;
  s1 << time_sec;

  std::stringstream s2;
  s2 << time_usec;

  this->values_.push_back (s1.str ());
  this->values_.push_back (s2.str ());

  this->sqlstr_ << time_sql;

  return;
}

//
// visit_time_before_query
//
void Query_Visitor::visit_time_before_query (TimeBeforeQuery_i * tb_query)
{
  static const char * time_sql =
      "SELECT datasize, data from oasis_metrics m "
      "WHERE m.tv_sec <= ? AND m.tv_usec <= ?;";

  long time_sec = tb_query->sec ();
  long time_usec = tb_query->usec ();

  std::stringstream s1;
  s1 << time_sec;

  std::stringstream s2;
  s2 << time_usec;

  this->values_.push_back (s1.str ());
  this->values_.push_back (s2.str ());

  this->sqlstr_ << time_sql;

  return;
}

//
// sqlstr
//
const char * Query_Visitor::sqlstr (void)
{
  return ACE_OS::strdup (this->sqlstr_.str ().c_str ());
}

//
// values
//
std::vector <std::string> & Query_Visitor::values (void)
{
  return this->values_;
}

}