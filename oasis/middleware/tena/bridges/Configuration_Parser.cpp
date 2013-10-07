// $Id:

#include "Configuration_Parser.h"

#include <fstream>

namespace OASIS
{

  //
  // Configuration_Parser
  //
  Configuration_Parser::Configuration_Parser (void)
  {

  }

  //
  // Meminfo_Parser
  //
  Configuration_Parser::~Configuration_Parser (void)
  {

  }

  //
  // read_data
  //
  bool Configuration_Parser::read_data (std::istream & input, Configuration_Group & group)
  {
    namespace spirit = boost::spirit;

    // Adapt the iterator to support Boost backtracking.
    long flags = input.flags ();

    if ((flags & std::ios::skipws) != 0)
      input.unsetf (std::ios::skipws);

    spirit::istream_iterator begin (input);
    spirit::istream_iterator end;

    // Parse the contents for the file.
    spirit::qi::parse (begin,
                       end,
                       this->grammar_ (&group));

    if (begin == end)
      return true;

    return false;
  }
}
