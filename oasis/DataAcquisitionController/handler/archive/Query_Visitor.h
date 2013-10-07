#ifndef _QUERY_VISITOR_H_
#define _QUERY_VISITOR_H_

#include "Query_i.h"
#include <sstream>
#include <vector>

namespace OASIS
{

class Query_Visitor
{
public:

  /// Default Constructor
  Query_Visitor (void);

  /// Destructor
  ~Query_Visitor (void);

  /// visit a query
  virtual void visit_query (Query_i * query);

  /// visit a probe_query
  virtual void visit_probe_query (ProbeQuery_i * p_query);

  /// visit an einode query
  virtual void visit_einode_query (EINodeQuery_i * e_query);

  /// visit a time query
  virtual void visit_time_query (TimeQuery_i * t_query);

  /// visit a time after query
  virtual void visit_time_after_query (TimeAfterQuery_i * ta_query);

  /// visit a time before query
  virtual void visit_time_before_query (TimeBeforeQuery_i * tb_query);

  /// Return the sql string
  const char * sqlstr (void);

  /// Return the parameter values
  std::vector <std::string> & values (void);

private:

  /// SQL query
  std::ostringstream sqlstr_;;

  /// Parameter values
  std::vector <std::string> values_;
};

}

#endif