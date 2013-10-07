// -*- C++ -*-

//=============================================================================
/**
 * @file        Configuration.h
 *
 * $Id: Configuration.h 1964 2011-10-03 02:59:33Z hillj $
 *
 * @author      Harold Owens II
 */
//=============================================================================

#ifndef _OASIS_DATA_CHANNEL_SUBSCRIBER_CONFIGURATION_H_
#define _OASIS_DATA_CHANNEL_SUBSCRIBER_CONFIGURATION_H_

#include <TENA/Middleware/config.h>
#include <TENA/Middleware/ApplicationConfiguration.h>

/**
 * @class Application_Configuration
 *
 * This class defines allowable settings and parses the current command line,
 * configuration file, and environment to initialize the application
 * configuration.
 */
class Configuration : public TENA::Middleware::ApplicationConfiguration
{
public:
  /**
   * Constructor
   *
   * @param[in,out]       argc          Number of command-line arguments
   * @param[in,out]       argv          The actual command-line arguments
   * @param[in]           file_name     Pathname of the configuration file.
   * @param[in]           file_prefix   Prefix of configuration file options to parse.
   * @param[in]           env_prefix    Prefix of environment variables to apply for this
   *                                    application
   */
  Configuration (void);

private:
  /// Helper method that defines the settings.
  void defineSettings (void);
};

#endif // ifndef myHelpers_ApplicationConfiguration_h
