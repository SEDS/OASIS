// $Id: Var_Type_Generator.cpp 2118 2012-01-13 20:29:17Z dpuranik $

#include "Var_Type_Generator.h"
#include "fe/PDL_Struct.h"
#include "fe/PDL_Simple_Type.h"
#include "fe/PDL_Vector_Type.h"

namespace OASIS_PDL_BE
{
namespace Csharp
{

//
// Var_Type_Generator
//
Var_Type_Generator::
Var_Type_Generator (std::ostream & out, bool ending)
: out_ (out),
  ending_ (ending)
{

}

//
// ~Var_Type_Generator
//
Var_Type_Generator::~Var_Type_Generator (void)
{

}

//
// visit_struct
//
void Var_Type_Generator::visit_struct (const OASIS_PDL_Struct & s)
{
  this->out_ << s.name();
}

//
// visit_simple_type
//
void Var_Type_Generator::
visit_simple_type (const OASIS_PDL_Simple_Type & s)
{
  switch (s.kind ())
  {
  case OASIS_PDL_Simple_Type::tk_boolean:
    this->out_ << "Boolean";
    break;

  case OASIS_PDL_Simple_Type::tk_string:
    this->out_ << "String";
    break;

  case OASIS_PDL_Simple_Type::tk_int8:
    this->out_ << "Byte";
    break;

  case OASIS_PDL_Simple_Type::tk_int16:
    this->out_ << "Int16";
    break;

  case OASIS_PDL_Simple_Type::tk_int32:
    this->out_ << "Int32";
    break;

  case OASIS_PDL_Simple_Type::tk_int64:
    this->out_ << "Int64";
    break;

  case OASIS_PDL_Simple_Type::tk_uint8:
    this->out_ << "Byte";
    break;

  case OASIS_PDL_Simple_Type::tk_uint16:
    this->out_ << "UInt16";
    break;

  case OASIS_PDL_Simple_Type::tk_uint32:
    this->out_ << "UInt32";
    break;

  case OASIS_PDL_Simple_Type::tk_uint64:
    this->out_ << "UInt64";
    break;

  case OASIS_PDL_Simple_Type::tk_real32:
    this->out_ << "float";
    break;

  case OASIS_PDL_Simple_Type::tk_real64:
    this->out_ << "Bouble";
    break;
  }
}

//
// visit_complex_type_member
//
void Var_Type_Generator::
visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m)
{
  if (this->ending_)
    this->out_<<"protected ";
  else
    this->out_<<"public ";

  if (m.type ())
    m.type ()->accept (*this);

  this->out_ << " " << m.name ();

  if (this->ending_)
    this->out_ << "_";

  this->out_ << ";" << std::endl;
}

}
}
