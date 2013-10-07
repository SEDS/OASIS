// $Id: Query_i.cpp 2238 2013-03-08 20:50:44Z tmpeiris $

#include "Query_i.h"
#include "Query_Visitor.h"

namespace OASIS
{
//
// Query_i
//
Query_i::Query_i ()
{

}

//
// ~Query_i
//
Query_i::~Query_i ()
{

}

//
// accept
//
void Query_i::accept (Query_Visitor & v)
{
  v.visit_query (this);
}

//
// ProbeQuery_i
//
ProbeQuery_i::ProbeQuery_i (void)
{
}

//
// ProbeQuery_i
//
ProbeQuery_i::ProbeQuery_i (const char * name)
{
  this->name (name);
}

//
// ~ProbeQuery_i
//
ProbeQuery_i::~ProbeQuery_i ()
{

}

//
// accept
//
void ProbeQuery_i::accept (Query_Visitor & v)
{
  v.visit_probe_query (this);
}

//
// EINodeQuery_i
//
EINodeQuery_i::EINodeQuery_i (void)
{
}

//
// EINodeQuery_i
//
EINodeQuery_i::EINodeQuery_i (const char * name)
{
  this->name (name);
}

//
// ~EINodeQuery_i
//
EINodeQuery_i::~EINodeQuery_i ()
{

}

//
// accept
//
void EINodeQuery_i::accept (Query_Visitor & v)
{
  v.visit_einode_query (this);
}

//
// TimeQuery_i
//
TimeQuery_i::TimeQuery_i ()
{

}

//
// ~TimeQuery_i
//
TimeQuery_i::~TimeQuery_i ()
{

}

//
// accept
//
void TimeQuery_i::accept (Query_Visitor & v)
{
  v.visit_time_query (this);
}

//
// TimeAfterQuery_i
//
TimeAfterQuery_i::TimeAfterQuery_i (void)
{
}

//
// ~TimeAfterQuery_i
//
TimeAfterQuery_i::~TimeAfterQuery_i ()
{

}

//
// TimeAfterQuery_i
//
TimeAfterQuery_i::TimeAfterQuery_i (unsigned long sec, unsigned long usec)
{
  this->sec (sec);
  this->usec (usec);
}

//
// accept
//
void TimeAfterQuery_i::accept (Query_Visitor & v)
{
  v.visit_time_after_query (this);
}

//
// TimeBeforeQuery_i
//
TimeBeforeQuery_i::TimeBeforeQuery_i (void)
{
}

//
// ~TimeBeforeQuery_i
//
TimeBeforeQuery_i::~TimeBeforeQuery_i ()
{

}

//
// TimeBeforeQuery_i
//
TimeBeforeQuery_i::TimeBeforeQuery_i (unsigned long sec, unsigned long usec)
{
  this->sec (sec);
  this->usec (usec);
}

//
// accept
//
void TimeBeforeQuery_i::accept (Query_Visitor & v)
{
  return v.visit_time_before_query (this);
}

//
// QueryFactory
//
QueryFactory::QueryFactory ()
{

}

//
// ~QueryFactory
//
QueryFactory::~QueryFactory ()
{

}

//
// create_for_unmarshal
//
::CORBA::ValueBase *
QueryFactory::create_for_unmarshal ()
{
  ::CORBA::ValueBase * value = 0;

  ACE_NEW_THROW_EX (value,
                    Query_i (),
                    ::CORBA::NO_MEMORY ());

  return value;
}

//
// ProbeQueryFactory
//
ProbeQueryFactory::ProbeQueryFactory (void)
{

}

//
// ProbeQueryFactory
//
ProbeQueryFactory::~ProbeQueryFactory ()
{

}

//
// create_for_unmarshal
//
::CORBA::ValueBase *
ProbeQueryFactory::create_for_unmarshal ()
{
  ::CORBA::ValueBase * value = 0;

  ACE_NEW_THROW_EX (value,
                    ProbeQuery_i (),
                    ::CORBA::NO_MEMORY ());

  return value;
}


//
// EINodeQueryFactory
//
EINodeQueryFactory::EINodeQueryFactory ()
{

}

//
// ~EINodeQueryFactory
//
EINodeQueryFactory::~EINodeQueryFactory ()
{

}

//
// create_for_unmarshal
//
::CORBA::ValueBase *
EINodeQueryFactory::create_for_unmarshal ()
{
  ::CORBA::ValueBase * value = 0;

  ACE_NEW_THROW_EX (value,
                    EINodeQuery_i (),
                    ::CORBA::NO_MEMORY ());

  return value;
}

//
// TimeQueryFactory
//
TimeQueryFactory::TimeQueryFactory ()
{

}

//
// ~TimeQueryFactory
//
TimeQueryFactory::~TimeQueryFactory ()
{

}

//
// create_for_unmarshal
//
::CORBA::ValueBase *
TimeQueryFactory::create_for_unmarshal ()
{
  ::CORBA::ValueBase * value = 0;

  ACE_NEW_THROW_EX (value,
                    TimeQuery_i (),
                    ::CORBA::NO_MEMORY ());

  return value;
}

//
// TimeAfterQueryFactory
//
TimeAfterQueryFactory::TimeAfterQueryFactory ()
{

}

//
// ~TimeAfterQueryFactory
//
TimeAfterQueryFactory::~TimeAfterQueryFactory ()
{

}

//
// create_for_unmarshal
//
::CORBA::ValueBase *
TimeAfterQueryFactory::create_for_unmarshal ()
{
  ::CORBA::ValueBase * value = 0;

  ACE_NEW_THROW_EX (value,
                    TimeAfterQuery_i (),
                    ::CORBA::NO_MEMORY ());

  return value;
}

//
// TimeBeforeQueryFactory
//
TimeBeforeQueryFactory::TimeBeforeQueryFactory ()
{

}

//
// ~TimeBeforeQueryFactory
//
TimeBeforeQueryFactory::~TimeBeforeQueryFactory ()
{

}

//
// create_for_unmarshal
//
::CORBA::ValueBase *
TimeBeforeQueryFactory::create_for_unmarshal ()
{
  ::CORBA::ValueBase * value = 0;

  ACE_NEW_THROW_EX (value,
                    TimeBeforeQuery_i (),
                    ::CORBA::NO_MEMORY ());

  return value;
}

}