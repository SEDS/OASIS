// -*- C++ -*-

//=============================================================================
/**
 * @file          Database.h
 *
 * $Id: Database.h 2207 2012-06-08 20:02:32Z dfeiock $
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DAC_DATABASE_H_
#define _OASIS_DAC_DATABASE_H_

#include "ace/Auto_Ptr.h"
#include "ace/UUID.h"
#include "adbc/SQLite/Connection.h"

#include "DAC_Core_export.h"
#include "oasis/config.h"
#include <vector>

namespace OASIS
{
// Forward decl.
class Software_Probe_Metadata;
class Software_Probe_Instance;

namespace DAC
{

/**
 * @class Database
 *
 * Main database for the DAC.
 */
class OASIS_DAC_CORE_Export Database
{
public:
  /// Default constructor.
  Database (void);

  /// Destructor.
  ~Database (void);

  /// Get the underlying connection.
  ADBC::SQLite::Connection & get_connection (void);

  /// Get the underlying connection.
  ADBC::SQLite::Connection * operator -> (void);

  /// Create the database.
  void create (void);

  /**
   * Insert metadata for a software probe into the database.
   *
   * @param[in]         metadata        Software probe metadata
   */
  int insert_metadata (const Software_Probe_Metadata & metadata);

  /**
   * Register the XML Schema Definition (XSD) that is defined in
   * the software probe's metadata.
   *
   * @param[in]         metadata        Software probe metadata
   */
  int register_schema (const Software_Probe_Metadata & metadata);

  /**
   * Insert an einode into the database.
   *
   * @param[in]       uuid        EINode's uuid
   * @param[in]       name        EINode's name
   */
  int insert_einode (const std::string & uuid,
                     const std::string & name);


  /**
   * Insert a software probe instance into the database.
   *
   * @param[in]       name              Instance's name
   * @param[in]       metadata          Software probe metadata
   * @param[in]       einode            Parent EINode's uuid
   */
  int insert_instance (const std::string & name,
                       const Software_Probe_Metadata & metadata,
                       const std::string & einode);

  /**
   * Get the einode name for the provided uuid
   *
   * @param[in]       uuid              EINode's uuid
   */
  void einode_name (const ACE_Utils::UUID & uuid, ACE_CString & name);

  /**
   * Get the probe instances which belong to
   * the specified einode.
   */
  int einode_probes (const ACE_Utils::UUID & uuid,
                     std::vector < std::pair <ACE_CString, ACE_CString > > & instances);

  /**
   * Get all the probe instances in the database
   */
  void probe_instances (std::vector < Software_Probe_Instance > & instances);

  /**
   * Get the schema for the specific probe instance
   */
  void schema (const char * instance_name,
               const char * einode,
               ACE_CString & schema);

private:
  /// The connection to the database.
  ADBC::SQLite::Connection conn_;
};

}
}

#endif  // !defined _OASIS_DAC_DATABASE_H_
