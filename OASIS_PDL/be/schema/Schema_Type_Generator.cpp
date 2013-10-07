// $Id: Schema_Type_Generator.cpp 1896 2011-09-07 14:56:19Z hillj $

#include "Schema_Type_Generator.h"

#include "fe/PDL_Probe.h"
#include "fe/PDL_Struct.h"
#include "fe/PDL_Simple_Type.h"
#include "fe/PDL_Vector_Type.h"

//
// OASIS_PDL_Schema_Type_Generator
//
OASIS_PDL_Schema_Type_Generator::
OASIS_PDL_Schema_Type_Generator (std::ostream & out)
: out_ (out)
{

}

//
// ~OASIS_PDL_Schema_Type_Generator
//
OASIS_PDL_Schema_Type_Generator::~OASIS_PDL_Schema_Type_Generator (void)
{

}

//
// visit_probe
//
void OASIS_PDL_Schema_Type_Generator::
visit_probe (const OASIS_PDL_Probe & probe)
{
  this->out_ << probe.fq_name (".");
}

//
// visit_struct
//
void OASIS_PDL_Schema_Type_Generator::
visit_struct (const OASIS_PDL_Struct & s)
{
  this->out_ << s.fq_name (".");
}

//
// visit_vector_type
//
void OASIS_PDL_Schema_Type_Generator::
visit_vector_type (const OASIS_PDL_Vector_Type & v)
{
  if (v.type ())
    v.type ()->accept (*this);
}

//
// visit_simple_type
//
void OASIS_PDL_Schema_Type_Generator::
visit_simple_type (const OASIS_PDL_Simple_Type & s)
{
  switch (s.kind ())
  {
  case OASIS_PDL_Simple_Type::tk_boolean:
    this->out_ << "xsd:boolean";
    break;

  case OASIS_PDL_Simple_Type::tk_string:
    this->out_ << "xsd:string";
    break;

  case OASIS_PDL_Simple_Type::tk_int8:
    this->out_ << "xsd:byte";
    break;

  case OASIS_PDL_Simple_Type::tk_int16:
    this->out_ << "xsd:short";
    break;

  case OASIS_PDL_Simple_Type::tk_int32:
    this->out_ << "xsd:int";
    break;

  case OASIS_PDL_Simple_Type::tk_int64:
    this->out_ << "xsd:long";
    break;

  case OASIS_PDL_Simple_Type::tk_uint8:
    this->out_ << "xsd:unsignedByte";
    break;

  case OASIS_PDL_Simple_Type::tk_uint16:
    this->out_ << "xsd:unsignedShort";
    break;

  case OASIS_PDL_Simple_Type::tk_uint32:
    this->out_ << "xsd:unsignedInt";
    break;

  case OASIS_PDL_Simple_Type::tk_uint64:
    this->out_ << "xsd:unsignedLong";
    break;

  case OASIS_PDL_Simple_Type::tk_real32:
    this->out_ << "xsd:float";
    break;

  case OASIS_PDL_Simple_Type::tk_real64:
    this->out_ << "xsd:double";
    break;
  }
}
