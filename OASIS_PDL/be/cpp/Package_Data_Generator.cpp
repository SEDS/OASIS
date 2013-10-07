// $Id: Package_Data_Generator.cpp 2222 2012-11-20 17:02:16Z dfeiock $

#include "Package_Data_Generator.h"
#include "Cpp.h"

#include "fe/PDL_Probe.h"
#include "fe/PDL_Struct.h"
#include "fe/PDL_Simple_Type.h"
#include "fe/PDL_Vector_Type.h"

#include "boost/bind.hpp"
#include <algorithm>

namespace OASIS_PDL_BE
{
namespace Cpp
{
/**
 * @class Package_Impl
 */
class Package_Impl : public OASIS_PDL_Visitor
{
public:
  Package_Impl (std::ostream & cppfile, const std::string & s)
  : cppfile_ (cppfile),
    var_name_ (s)
  {

  }

  void visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m)
  {
    m.type ()->accept (*this);
  }


  virtual void visit_probe (const OASIS_PDL_Probe & p)
  {
    this->cppfile_
      << "if (!(p << this->" << this->var_name_ << "))" << std::endl
      << "  ACE_ERROR_RETURN ((LM_ERROR," << std::endl
      << "ACE_TEXT (\"%T (%t) - %M - failed to package " << this->var_name_ << "\\n\"))," << std::endl
      << "-1);"
      << std::endl;
  }

  virtual void visit_struct (const OASIS_PDL_Struct & s)
  {
    this->cppfile_
      << "if (0 != this->" << this->var_name_ << ".package_data (p))" << std::endl
      << "  ACE_ERROR_RETURN ((LM_ERROR," << std::endl
      << "ACE_TEXT (\"%T (%t) - %M - failed to package " << this->var_name_ << "\\n\"))," << std::endl
      << "-1);"
      << std::endl;
  }

  virtual void visit_simple_type (const OASIS_PDL_Simple_Type & s)
  {
    std::string method;
    switch (s.kind ())
    {
      case (OASIS_PDL_Simple_Type::tk_boolean):
        method = "boolean";
        break;

      case (OASIS_PDL_Simple_Type::tk_string):
        method =  "string";
        break;

      case (OASIS_PDL_Simple_Type::tk_int8):
        method = "int8";
        break;

      case (OASIS_PDL_Simple_Type::tk_int16):
        method = "int16";
        break;

      case (OASIS_PDL_Simple_Type::tk_int32):
        method = "int32";
        break;

      case (OASIS_PDL_Simple_Type::tk_int64):
        method = "int64";
        break;

      case (OASIS_PDL_Simple_Type::tk_uint8):
        method =  "uint8";
        break;

      case (OASIS_PDL_Simple_Type::tk_uint16):
        method = "uint16";
        break;

      case (OASIS_PDL_Simple_Type::tk_uint32):
        method = "uint32";
        break;

      case (OASIS_PDL_Simple_Type::tk_uint64):
        method = "uint64";
        break;

      case (OASIS_PDL_Simple_Type::tk_real32):
        method = "real32";
        break;

      case (OASIS_PDL_Simple_Type::tk_real64):
        method = "real64";
        break;
    }

    this->cppfile_
      << "if (!(p->write_" << method << " (" << this->var_name_ << ")))" << std::endl
      << "  ACE_ERROR_RETURN ((LM_ERROR," << std::endl
      << "ACE_TEXT (\"%T (%t) - %M - failed to package " << this->var_name_ << "\\n\"))," << std::endl
      << "-1);" << std::endl;
  }

virtual void visit_vector_type (const OASIS_PDL_Vector_Type & v)
  {
    // Write size of the vector to the stream
    this->cppfile_
      << "int " << this->var_name_ << "_vector_size = this->" << this->var_name_ << ".size ();" << std::endl
      << "if (!(p->write_int32 (" << this->var_name_ << "_vector_size)))" << std::endl
      << "  ACE_ERROR_RETURN ((LM_ERROR," << std::endl
      << "ACE_TEXT (\"%T (%t) - %M - failed to package " << this->var_name_ << " size\\n\"))," << std::endl
      << "-1);" << std::endl;

    // Write members of the vector to the stream
    this->cppfile_
      << "for (int i=0; i < " << this->var_name_  << "_vector_size-1; i++)" << std::endl
      << "{";

    Package_Impl p (this->cppfile_, this->var_name_ + "[i]");
    v.type ()->accept (p);

    this->cppfile_
      << "}";
  }

private:
  std::ostream & cppfile_;
  const std::string var_name_;
};

//
// Package_Data_Generator
//
Package_Data_Generator::
Package_Data_Generator (std::ostream & hfile, std::ostream & cppfile)
: hfile_ (hfile),
  cppfile_ (cppfile)
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

  // Make sure we know the base probe type.
  std::string base_probe =
    p.has_base_probe () ?
    ("::" + p.base_probe ()->fq_name ("::") + "Impl") : "::OASIS::Software_Probe_Impl";

  this->hfile_
    << std::endl
    << "/// Package the software probe's data." << std::endl
    << "protected:" << std::endl
    << "virtual int package_data (::OASIS::Software_Probe_Data_Packager *  p);"
    << std::endl;

  // Implement the package data method.
  this->cppfile_
    << function_header ("package_data")
    << "int " << name << "Impl::package_data (::OASIS::Software_Probe_Data_Packager * p) {"
    << "if (0 != " << base_probe << "::package_data (p))" << std::endl
    << "  ACE_ERROR_RETURN ((LM_ERROR," << std::endl
    << "ACE_TEXT (\"%T (%t) - %M - failed to package data\\n\"))," << std::endl
    << "-1);";

  this->var_suffix_ = "_";

  std::for_each (p.members ().begin (),
                 p.members ().end (),
                 boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                              _1,
                              boost::ref (*this)));

  this->cppfile_
    << "return 0;"
    << "}";
}

//
// visit_complex_type_member
//
void Package_Data_Generator::
visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m)
{
  Package_Impl p (this->cppfile_, m.name () + this->var_suffix_);
  m.type ()->accept (p);
}

//
// visit_struct
//
void Package_Data_Generator::visit_struct (const OASIS_PDL_Struct & s)
{
  this->hfile_
    << "/// Package the software probe's data." << std::endl
    << "int package_data (::OASIS::Software_Probe_Data_Packager *  p);"
    << std::endl;

  this->cppfile_
    << function_header ("package_data")
    << "int " << s.fq_name ("::") << "Impl::package_data (::OASIS::Software_Probe_Data_Packager * p) {";

  this->var_suffix_ = "";

  std::for_each (s.members ().begin (),
                 s.members ().end (),
                 boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                              _1,
                              boost::ref (*this)));

  this->cppfile_
    << "return 0;"
    << "}";
}

}
}
