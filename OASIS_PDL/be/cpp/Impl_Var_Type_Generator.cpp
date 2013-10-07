// $Id: Impl_Var_Type_Generator.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "Impl_Var_Type_Generator.h"
#include "fe/PDL_Struct.h"
#include "fe/PDL_Simple_Type.h"
#include "fe/PDL_Vector_Type.h"

namespace OASIS_PDL_BE
{
namespace Cpp
{

//
// Impl_Var_Type_Generator
//
Impl_Var_Type_Generator::
Impl_Var_Type_Generator (std::ostream & out, bool ending)
: out_ (out),
  ending_ (ending)
{

}

//
// ~Impl_Var_Type_Generator
//
Impl_Var_Type_Generator::~Impl_Var_Type_Generator (void)
{

}

//
// visit_struct
//
void Impl_Var_Type_Generator::visit_struct (const OASIS_PDL_Struct & s)
{
  this->out_ << "::" << s.fq_name ("::") << "Impl";
}

//
// visit_vector_type
//
void Impl_Var_Type_Generator::visit_vector_type (const OASIS_PDL_Vector_Type & v)
{
  this->out_ << "std::vector < ";
  v.type ()->accept (*this);
  this->out_ << " >";
}

//
// visit_simple_type
//
void Impl_Var_Type_Generator::
visit_simple_type (const OASIS_PDL_Simple_Type & s)
{
  switch (s.kind ())
  {
  case OASIS_PDL_Simple_Type::tk_boolean:
    this->out_ << "bool";
    break;

  case OASIS_PDL_Simple_Type::tk_string:
    this->out_ << "ACE_CString";
    break;

  case OASIS_PDL_Simple_Type::tk_int8:
    this->out_ << "char";
    break;

  case OASIS_PDL_Simple_Type::tk_int16:
    this->out_ << "ACE_INT16";
    break;

  case OASIS_PDL_Simple_Type::tk_int32:
    this->out_ << "ACE_INT32";
    break;

  case OASIS_PDL_Simple_Type::tk_int64:
    this->out_ << "ACE_INT64";
    break;

  case OASIS_PDL_Simple_Type::tk_uint8:
    this->out_ << "unsigned char";
    break;

  case OASIS_PDL_Simple_Type::tk_uint16:
    this->out_ << "ACE_UINT16";
    break;

  case OASIS_PDL_Simple_Type::tk_uint32:
    this->out_ << "ACE_UINT32";
    break;

  case OASIS_PDL_Simple_Type::tk_uint64:
    this->out_ << "ACE_UINT64";
    break;

  case OASIS_PDL_Simple_Type::tk_real32:
    this->out_ << "double";
    break;

  case OASIS_PDL_Simple_Type::tk_real64:
    this->out_ << "long double";
    break;
  }
}

//
// visit_complex_type_member
//
void Impl_Var_Type_Generator::
visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m)
{
  if (m.type ())
    m.type ()->accept (*this);

  this->out_ << " " << m.name ();

  if (this->ending_)
    this->out_ << "_";

  this->out_ << ";" << std::endl;
}

}
}
