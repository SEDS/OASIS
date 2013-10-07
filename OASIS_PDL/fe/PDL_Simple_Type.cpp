// $Id: PDL_Simple_Type.cpp 1768 2011-03-01 01:04:39Z hillj $

#include "PDL_Simple_Type.h"

#if !defined (__OASIS_INLINE__)
#include "PDL_Simple_Type.inl"
#endif

#include "PDL_Visitor.h"

//
// accept
//
void OASIS_PDL_Simple_Type::accept (OASIS_PDL_Visitor & v) const
{
  v.visit_simple_type (*this);
}

//
// fq_name
//
std::string
OASIS_PDL_Simple_Type::fq_name (const std::string & separator) const
{
  switch (this->kind_)
  {
  case tk_boolean:
    return "boolean";

  case tk_string:
    return "string";

  case tk_int8:
    return "int8";

  case tk_int16:
    return "int16";

  case tk_int32:
    return "int32";

  case tk_int64:
    return "int64";

  case tk_uint8:
    return "uint8";

  case tk_uint16:
    return "uint16";

  case tk_uint32:
    return "uint32";

  case tk_uint64:
    return "uint64";

  case tk_real32:
    return "real32";

  case tk_real64:
    return "real64";

  default:
    return "";
  }
}
