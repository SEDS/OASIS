// -*- C++ -*-

//=============================================================================
/**
 *  @file       Configuration.h
 *
 *  $Id: Configuration.h 2096 2012-01-06 14:02:03Z dfeiock $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _DAC_CONFIGURATION_H_
#define _DAC_CONFIGURATION_H_

#include <vector>
#include <string>

#include "ace/UUID.h"
#include "ace/Time_Value.h"
#include "oasis/config.h"

#include "EINode_Core_export.h"

namespace OASIS
{
// Forward decl.
template <typename IteratorT, typename SpaceT>
class Einode_Configuration_Grammar;

/**
 * @class Einode_Configuration
 *
 * Utility class for managing the DAC's configuration.
 */
class OASIS_EINODE_CORE_Export Einode_Configuration
{
public:
  // Friend decl.
  template <typename IteratorT, typename SpaceT>
  friend class Einode_Configuration_Grammar;

  struct Software_Probe
  {
    std::string name_;

    std::string location_;

    std::string entrypoint_;

    std::string params_;
  };

  /// Type definition for mapping services to their directives.
  typedef std::vector <Software_Probe> Software_Probe_List;

  struct Data_Channel
  {
    std::string directive_;

    Software_Probe_List probes_;
  };

  /// Default constructor.
  Einode_Configuration (void);

  /// Destructor.
  ~Einode_Configuration (void);

  /**
   * Load the configuration from a file.
   *
   * @param[in]         file        Target file to read
   */
  bool load_file (const char * file);

  /// Get the UUID.
  const ACE_Utils::UUID & uuid (void) const;

  /// Get the human readable name.
  const std::string & name (void) const;

  /// Get the reconnect timeout
  const ACE_Time_Value & reconnect_timeout (void) const;

  /// Get the collection of loaded channels.
  const Data_Channel & data_channel (void) const;

  /// Validate the configuration.
  bool validate (void) const;

private:
  /// The unique id for the Einode.
  ACE_Utils::UUID uuid_;

  /// Human readable name of the Einode.
  std::string name_;

  /// The reconnect timeout for the Einode.
  ACE_Time_Value reconnect_timeout_;

  /// The one and only channel.
  Data_Channel data_channel_;
};

}

#if defined (__OASIS_INLINE__)
#include "Configuration.inl"
#endif

#endif  // !defined _DAC_CONFIGURATION_H_
