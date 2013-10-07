// -*- C++ -*-

//=====================================================================
/**
 * @file       Procstat_Parser.h
 *
 * $Id: Procstat_Parser.h 2211 2012-07-25 12:55:51Z dfeiock $
 *
 * @author James H. Hill
 *         Harold Owens II
 */
//=====================================================================

#ifndef _OASIS_PROCSTAT_PARSER_H_
#define _OASIS_PROCSTAT_PARSER_H_

#include "oasis/config.h"

namespace OASIS
{
namespace System
{
namespace Processor
{
  // Forward decl.
  class LinuxProcessorProbeImpl;

  /**
   * @class Procstat_Parser
   *
   * Utility class for parsing the data in /proc/stat.
   */
  class Procstat_Parser
  {
  public:
    /**
     * Initializing constructor.
     *
     * @param[in]         stat       Target stat structure
     */
    Procstat_Parser (void);

    /// Destructor.
    ~Procstat_Parser (void);

    /**
     * Read the latest values of the data.
     *
     * @param[in]         probe      Target probe for parsed data.
     * @return            Result of the read operation.
     */
    bool read_data (LinuxProcessorProbeImpl * probe);
  };
}
}
}

#endif  // !defined _OASIS_PROCSTAT_PARSER_H_
