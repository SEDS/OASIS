/**
* @class Software_Probe_Metadata
*
* The metadata for a software probe. All the information below
* is required for each software probe.
*/

//
// Constructor
//
function Software_Probe_Metadata(uuid,
                                 type_info,
                                 version_major,
                                 version_minor,
                                 schema)
{
  /// Unique id for the software probe.
  this.uuid_ = uuid;

  /// Unique typename for the software probe.
  this.type_info_ = type_info;

  /// Version major number.
  this.version_major_ = version_major;

  /// Version minor number.
  this.version_minor_ = version_minor;

  /// Schema definition for the software probe.
  this.schema_ = schema;
} //end_of_Software_Probe_Metadata