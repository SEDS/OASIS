// -*- C++ -*-

//=============================================================================
/**
 *  @file         Command_Injector_App.h
 *
 *  $Id: Command_Parser.h 1971 2011-10-03 20:07:30Z hillj $
 *
 *  @author       James H. Hill
 */
//=============================================================================

#ifndef _OASIS_COMMAND_PARSER_H_
#define _OASIS_COMMAND_PARSER_H_

#include <string>

namespace OASIS
{

/**
 * @struct Command_Parser_Result
 *
 * Parser the command passed into the command injector.
 */
struct Command_Parser_Result
{
  /// Name of the target DAC.
  std::string dac_name_;

  /// Name of the target EI node.
  std::string einode_name_;

  /// Command-line string for the EI node.
  std::string command_;
};

/**
 * @class Command_Parser
 *
 * Parser the command passed into the command injector.
 */
class Command_Parser
{
public:
  /// Type definition of the result type for the parser.
  typedef Command_Parser_Result result_t;

  /// Default constructor.
  Command_Parser (void);

  /// Destructor.
  ~Command_Parser (void);

  /**
   * Parse the command-line string.
   *
   * @param[in]         command       Command to parse
   * @param[out]        result        Result of the parsing
   * @return            Success status of parsing.
   */
  bool parse (const std::string & command, result_t & result);
};

}

#endif  // !defined _OASIS_COMMAND_PARSER_H_
