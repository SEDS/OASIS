// $Id: Database.cpp 2207 2012-06-08 20:02:32Z dfeiock $

#include "Database.h"
#include "Metametrics_Table.h"
#include "Metametrics_Hierarchy_Table.h"
#include "EINodes_Table.h"
#include "Instances_Table.h"
#include "Xml_Error_Handler.h"
#include "Xml_String.h"

#include "adbc/SQLite/Exception.h"

#include "oasis/probes/Software_Probe_Metadata.h"

#include "ace/CORBA_macros.h"

#include "xercesc/framework/MemBufInputSource.hpp"
#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/util/PlatformUtils.hpp"
#include "xercesc/dom/DOM.hpp"

XERCES_CPP_NAMESPACE_USE

namespace OASIS
{
namespace DAC
{
//
// Database
//
Database::Database (void)
{
  XMLPlatformUtils::Initialize ();
}

//
// ~Database
//
Database::~Database (void)
{
  XMLPlatformUtils::Terminate ();
}

//
// get_connection
//
ADBC::SQLite::Connection & Database::get_connection (void)
{
  return this->conn_;
}

//
// operator ->
//
ADBC::SQLite::Connection * Database::operator -> (void)
{
  return &this->conn_;
}

//
// create
//
void Database::create (void)
{
  Metametrics_Table::_create (*this);
  Metametrics_Hierarchy_Table::_create (*this);
  EINodes_Table::_create (*this);
  Instances_Table::_create (*this);
}

//
// insert_metadata
//
int Database::
insert_metadata (const Software_Probe_Metadata & metadata)
{
  try
  {
    // Insert each software probe's metadata into the database.
    Metametrics_Table table (*this);
    table.insert_metadata (metadata);

    return 0;
  }
  catch (const ADBC::SQLite::Exception & ex)
  {
    if (SQLITE_CONSTRAINT != ex.native ())
      throw;
  }

  return 1;
}

//
// insert_einode
//
int Database::
insert_einode (const std::string & uuid,
               const std::string & name)
{
  try
  {
    // Insert each software probe's metadata into the database.
    EINodes_Table table (*this);
    table.insert_einode (uuid, name);

    return 0;
  }
  catch (const ADBC::SQLite::Exception & ex)
  {
    if (SQLITE_CONSTRAINT != ex.native ())
      throw;
  }

  return 1;
}

//
// insert_instance
//
int Database::
insert_instance (const std::string & name,
                 const Software_Probe_Metadata & metadata,
                 const std::string & einode)
{
  try
  {
    // Insert each software probe's metadata into the database.
    Instances_Table table (*this);
    table.insert_instance (name, metadata.uuid_, einode);

    return 0;
  }
  catch (const ADBC::SQLite::Exception & ex)
  {
    if (SQLITE_CONSTRAINT != ex.native ())
      throw;
  }

  return 1;
}

//
// einode_name
//
void Database::
einode_name (const ACE_Utils::UUID & uuid, ACE_CString & name)
{
  try
  {
    EINodes_Table table (*this);
    table.einode_name (uuid, name);
  }
  catch (const ADBC::SQLite::Exception & ex)
  {
    if (SQLITE_CONSTRAINT != ex.native ())
      throw;
  }
}

//
// einode_probes
//
int Database::
einode_probes (const ACE_Utils::UUID & uuid,
               std::vector <std::pair <ACE_CString, ACE_CString > > & instances)
{
  try
  {
    EINodes_Table table (*this);
    table.einode_probes (uuid, instances);
    return 0;
  }
  catch (const ADBC::SQLite::Exception & ex)
  {
    if (SQLITE_CONSTRAINT != ex.native ())
      throw;
  }
  return 1;
}

//
// probe_instances
//
void Database::
probe_instances (std::vector < Software_Probe_Instance > & instances)
{
  try
  {
    Instances_Table table (*this);
    table.probe_instances (instances);
  }
  catch (const ADBC::SQLite::Exception & ex)
  {
    if (SQLITE_CONSTRAINT != ex.native ())
      throw;
  }
}

//
// schema
//
void Database::
schema (const char * instance_name,
        const char * einode_name,
        ACE_CString & schema)
{
  try
  {
    Metametrics_Table table (*this);
    table.schema (instance_name, einode_name, schema);
  }
  catch (const ADBC::SQLite::Exception & ex)
  {
    if (SQLITE_CONSTRAINT != ex.native ())
      throw;
  }
}

//
// register_schema
//
int Database::
register_schema (const Software_Probe_Metadata & metadata)
{
  try
  {
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - registering schema for %s:%d.%d\n"),
                metadata.type_info_.c_str (),
                metadata.version_major_,
                metadata.version_minor_));

    // Parse the software probe's XML schema definition, which is
    // located in memory buffer.
    MemBufInputSource buf ((const XMLByte *)metadata.schema_.c_str (),
                           metadata.schema_.length (),
                           Xml_String ("XMLSchema"));

    XercesDOMParser parser;

    Xml_Error_Handler error_handler;
    parser.setErrorHandler (&error_handler);

    parser.parse (buf);

    using xercesc::DOMNodeList;
    using xercesc::DOMElement;

    // Locate the probe definition.
    DOMNodeList * list = parser.getDocument ()->getElementsByTagName (Xml_String ("xsd:element"));
    DOMElement * probe = dynamic_cast <DOMElement *> (list->item (0));

    // Locate all the complex type definitions.
    DOMNodeList * types = parser.getDocument ()->getElementsByTagName (Xml_String ("xsd:complexType"));
    XMLSize_t items = types->getLength ();

    for (XMLSize_t i = 0; i < items; ++ i)
    {
      try
      {
        // There is no need to continue if this complex type is not derived
        // from any other complex type (i.e., does not have a base type).
        DOMNode * node = types->item (i);
        DOMNode * complexContent = node->getFirstChild ();
        Xml_String node_name = complexContent->getNodeName ();

        if (node_name != Xml_String ("xsd:complexContent"))
          continue;

        // Get the name of this complex type since we are going to store
        // its inheritance information in the database.
        DOMElement * e = dynamic_cast <DOMElement *> (node);
        Xml_String name (e->getAttribute (Xml_String ("name")));

        // Get the base class of this complex type.
        DOMNode * extension = complexContent->getFirstChild ();
        e = dynamic_cast <DOMElement *> (extension);
        Xml_String base (e->getAttribute (Xml_String ("base")));

        //// Insert the hierarchy information into the database.
        Metametrics_Hierarchy_Table table (*this);
        table.insert_hierarchy (name.c_str (), base.c_str ());
      }
      catch (const ADBC::SQLite::Exception & ex)
      {
        if (SQLITE_CONSTRAINT != ex.native ())
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("%T (%t) - %M - %s\n"),
                      ex.message ().c_str ()));
      }
    }
  }
  catch (const XMLException & ex)
  {
    Xml_String message (ex.getMessage ());

    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                message.c_str ()));
  }

  return 0;
}

}
}

