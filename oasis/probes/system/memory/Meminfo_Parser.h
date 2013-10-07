// -*- C++ -*-

//=====================================================================
/**
 * @file       Meminfo_Parser.h
 *
 * $Id: Meminfo_Parser.h 2211 2012-07-25 12:55:51Z dfeiock $
 *
 * @author     James H. Hill
 */
//=====================================================================

#ifndef _OASIS_MEMINFO_PARSER_H_
#define _OASIS_MEMINFO_PARSER_H_

#include "Meminfo_Parser_Grammar.h"
#include "oasis/config.h"

namespace OASIS
{
namespace System
{
namespace Memory
{
  /**
   * @class Meminfo_Parser
   *
   * Utility class for parsing the data in /proc/meminfo.
   */
  class Meminfo_Parser
  {
  public:
    /**
     * Initializing constructor.
     *
     * @param[in]         info       Target info structure
     */
    Meminfo_Parser (void);

    /// Destructor.
    ~Meminfo_Parser (void);

    /**
     * Read the latest values of the data.
     *
     * @param[in]         probe      Target probe for parsed data.
     * @return            Result of the read operation.
     */
    bool read_data (LinuxMemoryProbeImpl * probe);

  private:
    /// Grammar for the parser.
    Meminfo_Parser_Grammar <boost::spirit::istream_iterator,
                            boost::spirit::ascii::space_type> grammar_;
  };
}
}
}

#endif  // !defined _OASIS_MEMINFO_PARSER_H_
