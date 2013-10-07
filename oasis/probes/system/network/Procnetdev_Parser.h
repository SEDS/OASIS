// -*- C++ -*-

//=====================================================================
/**
 * @file       Procnetdev_Parser.h
 *
 * $Id: Procnetdev_Parser.h 2211 2012-07-25 12:55:51Z dfeiock $
 *
 * @author James H. Hill
 *         Harold Owens II
 */
//=====================================================================

#ifndef _OASIS_PROCNETDEV_PARSER_H_
#define _OASIS_PROCNETDEV_PARSER_H_

#include "oasis/config.h"
#include "NetworkProbe_Impl.h"

namespace OASIS
{
namespace System
{
namespace Network
{
  /**
   * @class Procnetdev_Parser
   *
   * Utility class for parsing the data in /proc/net/dev.
   */
  class Procnetdev_Parser
  {
  public:
    /**
     * Initializing constructor.
     *
     * @param[in]         stat       Target stat structure
     */
    Procnetdev_Parser (void);

    /// Destructor.
    ~Procnetdev_Parser (void);

    /**
     * Read the latest values of the data.
     *
     * @param[in]         probe      Target probe for parsed data.
     * @return            Result of the read operation.
     */
    bool read_data (LinuxNetworkProbeImpl * probe);
  };
}
}
}

#endif  // !defined _OASIS_PROCNETDEV_PARSER_H_
