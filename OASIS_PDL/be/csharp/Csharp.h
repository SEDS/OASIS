// -*- C++ -*-

//=============================================================================
/**
 * @file      Attribute_Generator.h
 *
 *  $Id: Csharp.h 2118 2012-01-13 20:29:17Z dpuranik $
 *
 *  @author   Darshan Puranik
 */
//=============================================================================

#ifndef _OASIS_PDL_BE_CSHARP_H_
#define _OASIS_PDL_BE_CSHARP_H_

#include <string>
#include <iosfwd>

namespace OASIS_PDL_BE
{
namespace Csharp
{

/**
 * @struct function_header_t
 *
 * Wrapper class that represents a tag to generate a function header
 * for the contained string.
 */
struct function_header_t
{
  function_header_t (const std::string & str);

  /// String for the function header.
  const std::string & str_;
};

function_header_t function_header (const std::string & str);
std::ostream & operator << (std::ostream & out, const function_header_t & fh);

/**
 * @struct single_line_comment_t
 *
 * Wrapper class that represents a tag to generate a single line
 * comment for a string.
 */
struct single_line_comment_t
{
  single_line_comment_t (const std::string & str);

  /// String for the function header.
  const std::string & str_;
};

single_line_comment_t single_line_comment (const std::string & str);
std::ostream & operator << (std::ostream & out, const single_line_comment_t & fh);

/**
 * @struct quoted_str_t
 *
 * Wrapper class that represents a tag to generate a single line
 * comment for a string.
 */
struct quoted_str_t
{
  quoted_str_t (const std::string & str);

  /// String for the function header.
  const std::string & str_;
};

quoted_str_t quoted_str (const std::string & str);
std::ostream & operator << (std::ostream & out, const quoted_str_t & q);

}
}

#endif  // !defined _OASIS_PDL_BE_CSHARP_H_
