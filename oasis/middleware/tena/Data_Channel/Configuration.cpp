// $Id: Configuration.cpp 1964 2011-10-03 02:59:33Z hillj $

#include "Configuration.h"

void parseEndpointString (std::string const & endpointString,
                          TENA::Middleware::Endpoint & endpoint )
{
  endpoint = TENA::Middleware::Endpoint( endpointString );
}

//
// Configuration
//
Configuration::Configuration (void)
: TENA::Middleware::ApplicationConfiguration ("publisher.config",
                                              "",
                                              "DataChannelPublisher",
                                              "Application Options:")
{
  this->defineSettings ();
}

//
// defineSettings
//
void Configuration::defineSettings (void)
{
  // Add configuration options that this application recognizes
  this->addSettings ()
    ("emEndpoint",
     TENA::Middleware::Utils::Value< TENA::Middleware::Endpoint >().setInitializer(&parseEndpointString),
     "The endpoint(s) on which the primary executionManager (EM) and "
     "EM replicas, if any, are listening for requests e.g., "
     "-emEndpoints <hostname>:55100 to contact an EM running on the "
     "host <hostname> listening on port 55100.  "
     "Multiple EM endpoints must to be separated by commas (if using the "
     "same protocol) or semicolons.  If semicolons are used, the string "
     "may be enclosed in double quotes or the semicolon escaped with a "
     "backslash (i.e. \"\\;\") to avoid shell interpretation issues." )

    ("bestEffort",
     "Specify the use of BestEffort (UDP/IP multicast) for SDO state change "
     "updates as well as for messages." )

    ("verbosity",
     TENA::Middleware::Utils::Value< TENA::uint32 >().setDefault( 4 )
     .setInitializer(TENA::Middleware::Utils::RangeChecker< TENA::uint32 >(0,4)),
     "A verbosity level argument, ranging from 0 (least output) to 4 (most "
     "output)." )

    ( "pruneExpiredStateChange",
      "If set, prune state change callbacks that are older than the most "
      "recently received, when a subscriber is unable to processes callback as "
      "quickly as they arrive." )

    ( "sessionName",
      TENA::Middleware::Utils::Value < std::string >().setDefault("DefaultSession"),
      "If set, prune state change callbacks that are older than the most "
      "recently received, when a subscriber is unable to processes callback as "
      "quickly as they arrive." )

    ("channelName",
     TENA::Middleware::Utils::Value< std::string >().setDefault("GlobalChannel"),
     "The name of DataChannel SDO that this application wants to communicate \n\t"
     "with.");
}
