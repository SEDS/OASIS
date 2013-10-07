// $Id: Package_Data_Generator.cpp 2118 2012-01-13 20:29:17Z dpuranik $

#include "Package_Data_Generator.h"
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
const std::string Package_Data_Generator::basic_types[]={
                                                          "boolean","string","int8","int16",
                                                          "int32","int64","uint8","uint16",
                                                          "uint32","uint64","real32","real64"
                                                         };

//
// Package_Data_Generator
//
Package_Data_Generator::
Package_Data_Generator (std::ostream & csfile)
: csfile_(csfile)
{
}

//
// ~Package_Data_Generator
//
Package_Data_Generator::~Package_Data_Generator (void)
{

}

//
// visit_probe
//
void Package_Data_Generator::visit_probe (const OASIS_PDL_Probe & p)
{
  const std::string name = p.name ();
  this->is_probe_ = true;

  // Make sure we know the base probe type.
  std::string base_probe =
    p.has_base_probe () ?
    ( p.base_probe ()->fq_name (".")) : "Software_Probe";

  // Implement the package data method.
  this->csfile_
    << function_header ("package_data")
    << "protected virtual new int " << "package_data (Software_Probe_Data_Packager p) {"<<std::endl
    << "base.package_data (p);" << std::endl;

  std::for_each (p.members ().begin (),
                 p.members ().end (),
                 boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                              _1,
                              boost::ref (*this)));

  this->csfile_
    << "return 0;"
    << "}";
}

//
// find
//
bool Package_Data_Generator::find(std::string type)
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
void Package_Data_Generator::
visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m)
{
  if (this->is_probe_ && this->find(m.type()->name()))
  {
    this->csfile_
      << "p.data_stream ().Write(this." << m.name () << "_);" << std::endl;
  }
  else if (this->is_probe_ && !this->find(m.type()->name()))
  {
    this->csfile_
      <<"this."<<m.name()<<"_.package_data(p.data_stream());"<< std::endl;
  }
  else
  {
  if (this->find(m.type()->name()))
  {
    // This is a non-vector type. So, we can just write it to the stream.
    this->csfile_
      <<"stream.Write(this." << m.name () << ");" << std::endl;
  }
  else
  {
    this->csfile_
      <<"this."<<m.name()<<".package_data(stream);"<< std::endl;
  }
  }
}

//
// visit_struct
//
void Package_Data_Generator::visit_struct (const OASIS_PDL_Struct & s)
{
  this->is_probe_ = false;

  this->csfile_
    <<std::endl
    <<"/// package_data"<<std::endl
    <<"public void package_data(CdrWriter stream)"<<std::endl
    <<"{"<<std::endl;

  std::for_each (s.members ().begin (),
                 s.members ().end (),
                 boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                              _1,
                              boost::ref (*this)));

  this->csfile_
    << "}";
}

}
}
