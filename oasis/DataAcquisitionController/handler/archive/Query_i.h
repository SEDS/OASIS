// $Id: Query_i.h 2238 2013-03-08 20:50:44Z tmpeiris $

#ifndef _QUERY_I_H_
#define _QUERY_I_H_

#include "QueryS.h"
#include "QueryC.h"
#include "ace/Null_Mutex.h"
#include "tao/Valuetype/ValueFactory.h"
#include <string>


namespace OASIS
{

  class Query_Visitor;

/**
 * @class Query_i
 *
 * Standard implementation of the Query
 */
class Query_i :
  public virtual OBV_OASIS::Query,
  public virtual CORBA::DefaultValueRefCountBase
{
public:

  /// Initializing constructor
  Query_i (void);

  /// Destructor.
  virtual ~Query_i (void);

  virtual void accept (Query_Visitor & v);

};

/**
 * @class ProbeQuery_i
 *
 * Standard implementation of the ProbeQuery
 */
class ProbeQuery_i :
  public virtual OBV_OASIS::ProbeQuery,
  public virtual Query_i
{
public:
  /// Default constructor
  ProbeQuery_i (void);

  /// Inirializing constructor
  ProbeQuery_i (const char * name);

  /// Destructor.
  virtual ~ProbeQuery_i (void);

  /// The accept method
  virtual void accept (Query_Visitor & v);

};

/**
 * @class EINodeQuery_i
 *
 * Standard implementation of the EINodeQueryQuery
 */
class EINodeQuery_i :
  public virtual OBV_OASIS::EINodeQuery,
  public virtual Query_i
{
public:

  /// Default constructor
  EINodeQuery_i (void);

  /// Initializing constructor
  EINodeQuery_i (const char * name);

  /// Destructor.
  virtual ~EINodeQuery_i (void);

  /// The accept method
  virtual void accept (Query_Visitor & v);

};

/**
 * @class TimeQuery_i
 *
 * Standard implementation of the TimeQuery
 */
class TimeQuery_i :
  public virtual OBV_OASIS::TimeQuery,
  public virtual Query_i
{
public:
  /// Default constructor
  TimeQuery_i (void);

  /// Destructor.
  virtual ~TimeQuery_i (void);

  /// The accept method
  virtual void accept (Query_Visitor & v);
};

/**
 * @class TimeAfterQuery_i
 *
 * Standard implementation of the TimeAfterQuery
 */
class TimeAfterQuery_i :
  public virtual OBV_OASIS::TimeAfterQuery,
  public virtual TimeQuery_i
{
public:

  /// Default constructor
  TimeAfterQuery_i (void);

  /// Initializing constructor
  TimeAfterQuery_i (unsigned long sec, unsigned long usec);

  /// Destructor.
  virtual ~TimeAfterQuery_i (void);

  /// The accept method
  virtual void accept (Query_Visitor & v);

};


/**
 * @class TimeBeforeQuery_i
 *
 * Standard implementation of the TimeBeforeQuery
 */
class TimeBeforeQuery_i :
  public virtual OBV_OASIS::TimeBeforeQuery,
  public virtual TimeQuery_i
{
public:

  /// Default constructor
  TimeBeforeQuery_i (void);

  /// Initializing constructor
  TimeBeforeQuery_i (unsigned long sec, unsigned long usec);

  /// Destructor.
  virtual ~TimeBeforeQuery_i (void);

  /// The accept method
  virtual void accept (Query_Visitor & v);
};


/**
 * @class QueryFactory
 *
 * Standard implementation of the QueryFactory
 */
class QueryFactory : public virtual ::CORBA::ValueFactoryBase
{
public:
  /// Default constructor
  QueryFactory ();

  /// Destructor
  virtual ~QueryFactory ();

  /// Create method for the object
  virtual ::CORBA::ValueBase * create_for_unmarshal ();
};


/**
 * @class ProbeQueryFactory
 *
 * Standard implementation of the ProbeQueryFactory
 */
class ProbeQueryFactory : public virtual ::CORBA::ValueFactoryBase
{
public:
  /// Default constructor
  ProbeQueryFactory ();

  /// Destructor
  virtual ~ProbeQueryFactory ();

  /// Create method for the object
  virtual ::CORBA::ValueBase * create_for_unmarshal ();
};


/**
 * @class EINodeQueryFactory
 *
 * Standard implementation of the EINodeQueryFactory
 */
class EINodeQueryFactory : public virtual ::CORBA::ValueFactoryBase
{
public:

  /// Default constructor
  EINodeQueryFactory ();

  /// Destructor
  virtual ~EINodeQueryFactory ();

  /// Create method for the object
  virtual ::CORBA::ValueBase * create_for_unmarshal ();
};


/**
 * @class TimeQueryFactory
 *
 * Standard implementation of the TimeQueryFactory
 */
class TimeQueryFactory : public virtual ::CORBA::ValueFactoryBase
{
public:

  /// Default constructor
  TimeQueryFactory ();

  /// Destructor
  virtual ~TimeQueryFactory ();

  /// Create method for the object
  virtual ::CORBA::ValueBase * create_for_unmarshal ();
};

/**
 * @class TimeAfterQueryFactory
 *
 * Standard implementation of the TimeAfterQueryFactory
 */
class TimeAfterQueryFactory : public virtual ::CORBA::ValueFactoryBase
{
public:
  /// Default constructor
  TimeAfterQueryFactory ();

  /// Destructor
  virtual ~TimeAfterQueryFactory ();

  /// Create method for the object
  virtual ::CORBA::ValueBase * create_for_unmarshal ();
};

/**
 * @class TimeBeforeQueryFactory
 *
 * Standard implementation of the TimeBeforeQueryFactory
 */
class TimeBeforeQueryFactory : public virtual ::CORBA::ValueFactoryBase
{
public:
   /// Default constructor
  TimeBeforeQueryFactory ();

  /// Destructor
  virtual ~TimeBeforeQueryFactory ();

  /// Create method for the object
  virtual ::CORBA::ValueBase * create_for_unmarshal ();
};

}

#endif  // !defined #define _QUERY_I_H_