// $Id: Meminfo_Parser.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "Meminfo_Parser.h"
#include "MemoryProbeImpl.h"

#include <fstream>

namespace OASIS
{
namespace System
{
namespace Memory
{
  //
  // Meminfo_Parser
  //
  Meminfo_Parser::Meminfo_Parser (void)
  {

  }

  //
  // Meminfo_Parser
  //
  Meminfo_Parser::~Meminfo_Parser (void)
  {

  }

  //
  // read_data
  //
  bool Meminfo_Parser::read_data (LinuxMemoryProbeImpl * probe)
  {
    namespace spirit = boost::spirit;

    // Open /proc/meminfo for reading.
    std::ifstream file;
    file.open (ACE_TEXT ("/proc/meminfo"));

    if (!file.is_open ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to open /proc/meminfo\n")),
                        false);

    long flags = file.flags ();
    if ((flags & std::ios::skipws))
      file.unsetf (std::ios::skipws);

    // Initialize the stream iterators for the file.
    spirit::istream_iterator begin (file);
    spirit::istream_iterator end;

    // Parse the contents for the file.
    return spirit::qi::phrase_parse (begin,
                                     end,
                                     this->grammar_ (probe),
                                     spirit::ascii::space);
  }

}
}
}
