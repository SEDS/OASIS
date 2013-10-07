// -*- C++ -*-

//=============================================================================
/**
 * @file        Configuration.h
 *
 * $Id: Tena_Publisher_Configuration.h 2064 2011-11-23 15:25:50Z dfeiock $
 *
 * @author      Harold Owens II
 */
//=============================================================================

#ifndef _OASIS_TENA_PUBLISHER_SERVICE_CONFIGURATION_H_
#define _OASIS_TENA_PUBLISHER_SERVICE_CONFIGURATION_H_

#include <TENA/Middleware/config.h>
#include <TENA/Middleware/ApplicationConfiguration.h>

namespace OASIS
{

/**
 * @class Tena_Publisher_Configuration
 *
 * This class defines allowable settings and parses the current command line,
 * configuration file, and environment to initialize the application
 * configuration.
 */
class Tena_Publisher_Configuration :
  public TENA::Middleware::ApplicationConfiguration
{
public:
  /// Default constructor.
  Tena_Publisher_Configuration (int argc, char * argv [], const std::string & config="");

  /// Helper method to define the settings.
  void defineSettings (void);
};

}

#endif // ifndef myHelpers_ApplicationConfiguration_h
