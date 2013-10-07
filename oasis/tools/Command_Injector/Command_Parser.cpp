// $Id: Command_Parser.cpp 1976 2011-10-05 20:13:03Z dfeiock $

#include "Command_Parser.h"

#include "boost/spirit/include/qi.hpp"
#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/include/phoenix_core.hpp"
#include "boost/spirit/include/phoenix_operator.hpp"
#include "boost/spirit/include/phoenix_fusion.hpp"
#include "boost/spirit/include/phoenix_stl.hpp"
#include "boost/spirit/include/phoenix_object.hpp"

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

BOOST_FUSION_ADAPT_STRUCT (
  OASIS::Command_Parser_Result,
  (std::string, dac_name_)
  (std::string, einode_name_)
  (std::string, command_)
);

/**
 * @class Command_Parser_Grammar
 *
 * Underlying grammar for the command parser.
 */
template <typename IteratorT>
struct Command_Parser_Grammar :
  public qi::grammar <IteratorT,
                      ::OASIS::Command_Parser_Result (),
                      ascii::space_type>
{
  Command_Parser_Grammar (void)
    : Command_Parser_Grammar::base_type (command_)
  {
    namespace qi = boost::spirit::qi;
    namespace phoenix = boost::phoenix;
    namespace ascii = boost::spirit::ascii;

    this->command_ %=
      this->ident_ > qi::lit ('.') >        // DAC's name
      this->ident_ > qi::lit ('.') >        // EI node's name
      qi::lexeme[*qi::char_];               // Rest of command

    // Definition of the identifier.
    this->ident_ %=
      qi::lexeme [(qi::alpha >> *(qi::alnum | qi::char_ ('_')))];

    using phoenix::construct;
    using phoenix::val;

    // Definition of the error handler.
    qi::on_error <qi::fail>
    (
      command_,
      std::cerr << phoenix::val ("*** syntax error: expecting ")
                << qi::labels::_4
                << phoenix::val(" here; \"")
                << construct <std::string> (qi::labels::_3, qi::labels::_2)
                << phoenix::val("\"")
                << std::endl
    );
  }

private:
  qi::rule <IteratorT,
            ::OASIS::Command_Parser_Result (),
            ascii::space_type> command_;

  qi::rule <IteratorT,
            std::string (),
            ascii::space_type> ident_;
};


namespace OASIS
{

//
// Command_Parser
//
Command_Parser::Command_Parser (void)
{

}

//
// ~Command_Parser
//
Command_Parser::~Command_Parser (void)
{

}

//
// parse
//
bool Command_Parser::
parse (const std::string & command, result_t & result)
{
  namespace spirit = boost::spirit;

  Command_Parser_Grammar <std::string::const_iterator> g;
  std::string::const_iterator
    begin = command.begin (), end = command.end ();

  return qi::phrase_parse (begin,
                           end,
                           g,
                           ascii::space,
                           result);
}

}
