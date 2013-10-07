// $Id: Tdl_Type_Generator.cpp 1768 2011-03-01 01:04:39Z hillj $

#include "Tdl_Type_Generator.h"

#include "fe/PDL_Probe.h"
#include "fe/PDL_Struct.h"
#include "fe/PDL_Simple_Type.h"

//
// OASIS_PDL_Tdl_Type_Generator
//
OASIS_PDL_Tdl_Type_Generator::
OASIS_PDL_Tdl_Type_Generator (Tdl_Stream & tdl)
: tdl_ (tdl)
{

}

//
// ~OASIS_PDL_Tdl_Type_Generator
//
OASIS_PDL_Tdl_Type_Generator::~OASIS_PDL_Tdl_Type_Generator (void)
{

}

//
// visit_probe
//
void OASIS_PDL_Tdl_Type_Generator::
visit_probe (const OASIS_PDL_Probe & probe)
{
  this->tdl_ << "::" << probe.fq_name ("::");
}

//
// visit_struct
//
void OASIS_PDL_Tdl_Type_Generator::
visit_struct (const OASIS_PDL_Struct & s)
{
  this->tdl_ << "::" << s.fq_name ("::");
}

//
// visit_simple_type
//
void OASIS_PDL_Tdl_Type_Generator::
visit_simple_type (const OASIS_PDL_Simple_Type & s)
{
  switch (s.kind ())
  {
  case OASIS_PDL_Simple_Type::tk_boolean:
    this->tdl_ << "boolean";
    break;

  case OASIS_PDL_Simple_Type::tk_string:
    this->tdl_ << "string";
    break;

  case OASIS_PDL_Simple_Type::tk_int8:
    this->tdl_ << "int8";
    break;

  case OASIS_PDL_Simple_Type::tk_int16:
    this->tdl_ << "int16";
    break;

  case OASIS_PDL_Simple_Type::tk_int32:
    this->tdl_ << "int32";
    break;

  case OASIS_PDL_Simple_Type::tk_int64:
    this->tdl_ << "int64";
    break;

  case OASIS_PDL_Simple_Type::tk_uint8:
    this->tdl_ << "uint8";
    break;

  case OASIS_PDL_Simple_Type::tk_uint16:
    this->tdl_ << "uint16";
    break;

  case OASIS_PDL_Simple_Type::tk_uint32:
    this->tdl_ << "uint32";
    break;

  case OASIS_PDL_Simple_Type::tk_uint64:
    this->tdl_ << "uint64";
    break;

  case OASIS_PDL_Simple_Type::tk_real32:
    this->tdl_ << "real32";
    break;

  case OASIS_PDL_Simple_Type::tk_real64:
    this->tdl_ << "real64";
    break;
  }
}
