// $Id:

#ifndef _OASIS_CONFIGURATION_PARSER_H_
#define _OASIS_CONFIGURATION_PARSER_H_

#include "Configuration_Parser_Grammar.h"
#include "Configuration_Group.h"
#include "oasis/config.h"

namespace OASIS
{
  /**
   * @class Configuration_Parser
   *
   * Parser for Tena probe static value configurations
   */
  class Configuration_Parser
  {
  public:
    /**
     * Initializing constructor.
     */
    Configuration_Parser (void);

    /// Destructor.
    ~Configuration_Parser (void);

    /**
     * Read the latest values of the data.
     *
     * @param[in]         input  Input to read
     * @param[in]         group  Target for parsed data.
     * @return            Result of the read operation.
     */
    bool read_data (std::istream & input, Configuration_Group & group);

  private:
    /// Grammar for the parser.
    Configuration_Parser_Grammar <boost::spirit::istream_iterator> grammar_;
  };
}

#endif // !defined _OASIS_CONFIGURATION_PARSER_H_
