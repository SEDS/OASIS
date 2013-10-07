// $Id: Cpp.cpp 1771 2011-03-02 20:56:37Z hillj $

#include "Cpp.h"
#include <ostream>

namespace OASIS_PDL_BE
{
namespace Cpp
{
//
// function_header_t
//
function_header_t::
function_header_t (const std::string & str)
: str_ (str)
{

}

//
// function_header
//
function_header_t function_header (const std::string & str)
{
  return function_header_t (str);
}

//
// operator <<
//
std::ostream & operator << (std::ostream & out, const function_header_t & fh)
{
  return out
    << single_line_comment ("")
    << single_line_comment (fh.str_)
    << single_line_comment ("");
}

//
// function_header_t
//
single_line_comment_t::
single_line_comment_t (const std::string & str)
: str_ (str)
{

}

//
// function_header
//
single_line_comment_t single_line_comment (const std::string & str)
{
  return single_line_comment_t (str);
}

//
// operator <<
//
std::ostream & operator << (std::ostream & out, const single_line_comment_t & slc)
{
  return out << "// " << slc.str_ << std::endl;
}

//
// quoted_str_t
//
quoted_str_t::quoted_str_t (const std::string & str)
: str_ (str)
{

}

//
// function_header
//
quoted_str_t quoted_str (const std::string & str)
{
  return quoted_str_t (str);
}

//
// operator <<
//
std::ostream & operator << (std::ostream & out, const quoted_str_t & q)
{
  return out << "\"" << q.str_ << "\"";
}

}
}
