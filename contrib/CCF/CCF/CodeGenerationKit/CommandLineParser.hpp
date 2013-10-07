// file      : CCF/CodeGenerationKit/CommandLineParser.hpp
// author    : Boris Kolpackov <boris@dre.vanderbilt.edu>
// cvs-id    : $Id: CommandLineParser.hpp 73838 2006-08-02 19:12:47Z boris $

#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H

#include "CCF/CodeGenerationKit/CommandLine.hpp"
#include "CCF/CodeGenerationKit/CommandLineDescriptor.hpp"

bool
parse (int argc, char* argv[], CL::Description const&, CommandLine&);

#endif  // COMMAND_LINE_PARSER_H
