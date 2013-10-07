// -*- C++ -*-

//=============================================================================
/**
 *  @file       Configuration.h
 *
 *  $Id: Configuration.h 1991 2011-10-10 02:05:19Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _DAC_CONFIGURATION_H_
#define _DAC_CONFIGURATION_H_

#include "ace/SString.h"
#include <vector>

namespace OASIS
{
/**
 * @class DAC_Service_Configuration
 *
 * Utility class for managing the DAC's configuration.
 */
class DAC_Service_Configuration
{
public:
  /**
   * @struct Data_Handler_Directive
   */
  struct Directive
  {
    /// Name of the data handler.
    std::string name_;

    /// Module where data handler is located.
    std::string module_;

    /// Symbol for importing data handler.
    std::string symbol_;

    /// Parameters for initializing data handler.
    std::string params_;
  };

  /// Type definition for mapping services to their directives.
  typedef std::vector <std::string> Service_List;

  /// Type definition for the list of data handlers.
  typedef std::vector <Directive> Data_Handler_List;

  /// Default constructor.
  DAC_Service_Configuration (void);

  /// Destructor.
  ~DAC_Service_Configuration (void);

  /**
   * Load the configuration from a file.
   *
   * @param[in]         file        Target file to read
   */
  bool load_file (const char * file);

  /// Get the collection of loaded handlers.
  const Data_Handler_List & handlers (void) const;

  /// Insert a new set of handlers.
  void insert_handlers (const Data_Handler_List & list);

  /// Get the collection of loaded channels.
  const Service_List & channels (void) const;

  /// Insert a new set of channels.
  void insert_channels (const Service_List & list);

private:
  /// Handlers in the configuration.
  Data_Handler_List handlers_;

  /// Channels in the configuration.
  Service_List channels_;
};

}

#endif  // !defined _DAC_CONFIGURATION_H_
