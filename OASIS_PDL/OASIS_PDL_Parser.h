// -*- C++ -*-

//=============================================================================
/**
 * @file        OASIS_PDL_Parser.h
 *
 * $Id: OASIS_PDL_Parser.h 1716 2010-11-29 00:53:50Z hillj $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_PARSER_H_
#define _OASIS_PDL_PARSER_H_

#include <iosfwd>

// Forward decl.
class OASIS_PDL_File;

/**
 * @class OASIS_PDL_Parser
 *
 * Parser object for converting a .pdl file into an abstract syntax
 * tree to support code generation.
 */
class OASIS_PDL_Parser
{
public:
  /// Default constructor.
  OASIS_PDL_Parser (void);

  /// Destructor.
  ~OASIS_PDL_Parser (void);

  bool parse_file (std::istream & input, OASIS_PDL_File & file);
};

#endif  // !defined _OASIS_PDL_PARSER_H_
