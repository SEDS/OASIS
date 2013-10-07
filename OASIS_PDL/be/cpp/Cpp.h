// -*- C++ -*-

//=============================================================================
/**
 * @file      Attribute_Generator.h
 *
 *  $Id: Cpp.h 1771 2011-03-02 20:56:37Z hillj $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_BE_CPP_H_
#define _OASIS_PDL_BE_CPP_H_

#include <string>
#include <iosfwd>

namespace OASIS_PDL_BE
{
namespace Cpp
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

#endif  // !defined _OASIS_PDL_BE_CPP_H_
