// $Id: Recall_Generator.cpp 2118 2012-01-13 20:29:17Z dpuranik $

#include "Recall_Generator.h"
#include "Csharp.h"

#include "fe/PDL_Probe.h"
#include "fe/PDL_Struct.h"
#include "fe/PDL_Simple_Type.h"

#include "boost/bind.hpp"
#include <algorithm>

namespace OASIS_PDL_BE
{
namespace Csharp
{

const std::string Recall_Generator::basic_types[]=
                                                  {
                                                    "boolean","string","int8","int16",
                                                    "int32","int64","uint8","uint16",
                                                    "uint32","uint64","real32","real64"
                                                  };
//
// Recall_Generator
//
Recall_Generator::
Recall_Generator (std::ostream & csfile)
:csfile_ (csfile)
{

}

//
// ~Recall_Generator
//
Recall_Generator::~Recall_Generator (void)
{

}

//
// visit_probe
//
void Recall_Generator::visit_probe (const OASIS_PDL_Probe & p)
{
  this->is_probe_ = true;

  const std::string & name = p.name ();

  this->csfile_
    << std::endl
    << "/// Recall the software probe's data." << std::endl
    << "public virtual int recall (byte[] data)"
    << std::endl
    << "{" <<std::endl
    << "CdrReader reader = new CdrReader(data);"<<std::endl
    << "return this.recall(reader);"<<std::endl
    << "}"<<std::endl;

  // Implementation of the internal recall method.
  this->csfile_
    << function_header ("recall")
    << "protected new int recall (CdrReader input)" <<std::endl
    << "{"<<std::endl
    << "base.recall(input);"
    << std::endl;

  if (!p.members ().empty ())
  {
    std::for_each (p.members ().begin (),
                   p.members ().end (),
                   boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                                _1,
                                boost::ref (*this)));
    this->csfile_
      << "return 0;";
  }
  else
  {
    this->csfile_
      << std::endl
      << "return 0;";
  }

  this->csfile_
    << "}";
}

//
// find
//
bool Recall_Generator::find(std::string type)
{
  for (int i=0;i<12;i++)
  {
    if (0 == strcmp(type.c_str(),basic_types[i].c_str()))
      return true;
  }
  return false;
}

//
// visit_complex_type_member
//
void Recall_Generator::
visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m)
{
  if (this->is_probe_ && this->find(m.type()->name()))
  {
    this->csfile_
      <<"this." << m.name () << "_ = input.Read";
    m.type()->accept(*this);

    this->csfile_<<"();"<<std::endl;
  }
  else if(this->is_probe_ && !this->find(m.type()->name()))
  {
  this->csfile_
    <<"this." << m.name () << "_.recall(input);"<<std::endl;
  }
  else
  {
    if(this->find(m.type()->name()))
    {
    this->csfile_
      <<"this."<<m.name()<<" = input.Read";
    m.type()->accept(*this);
    this->csfile_
      <<"();"<<std::endl;
    }
    else
    {
    this->csfile_
      <<"this."<<m.name()<<".recall(input);";
    }
  }
}

//
// visit_struct
//
void Recall_Generator::visit_struct (const OASIS_PDL_Struct & s)
{
  this->is_probe_ = false;

  this->csfile_
    <<"/// recall"<<std::endl
    <<"public void recall(CdrReader input)"<<std::endl
    <<"{"<<std::endl;

  std::for_each (s.members ().begin (),
                 s.members ().end (),
                 boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                              _1,
                              boost::ref (*this)));

  this->csfile_
    << "}";
}

//
// visit_simple_type
//
void Recall_Generator::visit_simple_type (const OASIS_PDL_Simple_Type & s)
{
switch (s.kind ())
  {
  case OASIS_PDL_Simple_Type::tk_boolean:
    this->csfile_ << "Boolean";
    break;

  case OASIS_PDL_Simple_Type::tk_string:
    this->csfile_ << "String";
    break;

  case OASIS_PDL_Simple_Type::tk_int8:
    this->csfile_ << "Byte";
    break;

  case OASIS_PDL_Simple_Type::tk_int16:
    this->csfile_ << "Int16";
    break;

  case OASIS_PDL_Simple_Type::tk_int32:
    this->csfile_ << "Int32";
    break;

  case OASIS_PDL_Simple_Type::tk_int64:
    this->csfile_ << "Int64";
    break;

  case OASIS_PDL_Simple_Type::tk_uint8:
    this->csfile_ << "Byte";
    break;

  case OASIS_PDL_Simple_Type::tk_uint16:
    this->csfile_ << "UInt16";
    break;

  case OASIS_PDL_Simple_Type::tk_uint32:
    this->csfile_ << "UInt32";
    break;

  case OASIS_PDL_Simple_Type::tk_uint64:
    this->csfile_ << "UInt64";
    break;

  case OASIS_PDL_Simple_Type::tk_real32:
    this->csfile_ << "float";
    break;

  case OASIS_PDL_Simple_Type::tk_real64:
    this->csfile_ << "Double";
    break;
}

}
}
}