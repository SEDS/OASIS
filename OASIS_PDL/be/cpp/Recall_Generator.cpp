// $Id: Recall_Generator.cpp 2213 2012-08-01 14:05:58Z dfeiock $

#include "Recall_Generator.h"
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
//
// Recall_Generator
//
Recall_Generator::
Recall_Generator (std::ostream & hfile, std::ostream & cppfile)
: hfile_ (hfile),
  cppfile_ (cppfile)
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

  // Make sure we know the base probe type.
  const std::string base_probe =
    p.has_base_probe () ?
    ("::" + p.base_probe ()->fq_name ("::")) : "::OASIS::Software_Probe";

  const std::string & name = p.name ();

  this->hfile_
    << std::endl
    << "public:" << std::endl
    << "/// Recall the software probe's data." << std::endl
    << "virtual int recall (const char * data, size_t length, int byte_order);"
    << std::endl
    << "protected:" << std::endl
    << "/// Helper method for recalling the data." << std::endl
    << "int recall (ACE_InputCDR & input);";

  // Implementation of the public recall method.
  this->cppfile_
    << function_header ("recall")
    << "int " << name << "::" << std::endl
    << "recall (const char * data, size_t length, int byte_order) {"
    << "::OASIS::Software_Probe_Data_Preparer prep (data, length);"
    << "ACE_InputCDR input (prep.message_block (), byte_order);"
    << "return ::" << p.fq_name ("::") << "::recall (input);"
    << "}"
    << std::endl;

  // Implementation of the internal recall method.
  this->cppfile_
    << function_header ("recall")
    << "int " << name << "::recall (ACE_InputCDR & in) {"
    << "if (0 != " << base_probe << "::recall (in))" << std::endl
    << "  ACE_ERROR_RETURN ((LM_ERROR," << std::endl
    << "ACE_TEXT (\"%T (%t) - %M - failed to recall \")" << std::endl
    << "ACE_TEXT (\"" << base_probe << " data\\n\"))," << std::endl
    << "-1);"
    << std::endl;

  if (!p.members ().empty ())
  {
    std::for_each (p.members ().begin (),
                   p.members ().end (),
                   boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                                _1,
                                boost::ref (*this)));
    this->cppfile_
      << "return in.good_bit () ? 0 : -1;";
  }
  else
  {
    this->cppfile_
      << std::endl
      << "return 0;";
  }

  this->cppfile_
    << "}";
}

//
// visit_complex_type_member
//
void Recall_Generator::
visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m)
{
  // Check if the member type is a vector, all other member types
  // can be handled in a generic manner
  OASIS_PDL_Vector_Type * vp = dynamic_cast <OASIS_PDL_Vector_Type *> (m.type ());
  if (vp != 0)
  {
    this->vector_name_ = m.name ();
    vp->accept (*this);
    return;
  }

  if (this->is_probe_)
  {
    this->cppfile_
      << "if (!(in >> this->" << m.name () << "_))" << std::endl
      << "  ACE_ERROR_RETURN ((LM_ERROR," << std::endl
      << "ACE_TEXT (\"%T (%t) - %M - failed to unpackage " << m.name () << "\\n\"))," << std::endl
      << "-1);"
      << std::endl;
  }
  else
  {
    this->cppfile_
      << "if (!(in >> s." << m.name () << "))" << std::endl
      << "  ACE_ERROR_RETURN ((LM_ERROR," << std::endl
      << "ACE_TEXT (\"%T (%t) - %M - failed to unpackage " << m.name () << "\\n\"))," << std::endl
      << "false);"
      << std::endl;
  }
}

//
// visit_vector_type
//
void Recall_Generator::
visit_vector_type (const OASIS_PDL_Vector_Type & v)
{
  this->cppfile_
    << "int " << this->vector_name_ << "_vector_size = 0;" << std::endl
    << "if (!(in >> " << this->vector_name_ << "_vector_size))" << std::endl
    << "  ACE_ERROR_RETURN ((LM_ERROR," << std::endl
    << "ACE_TEXT (\"%T (%t) - %M - failed to unpackage " << this->vector_name_ << " size\\n\"))," << std::endl
    << "-1);"
    << std::endl;

  if (this->is_probe_)
  {
    this->cppfile_
    <<  "this->" << this->vector_name_ << "_.resize (" << this->vector_name_ << "_vector_size);" << std::endl;
  }
  else
  {
    this->cppfile_
      <<  "s." << this->vector_name_ << ".resize (" << this->vector_name_ << "_vector_size);" << std::endl;
  }

  this->cppfile_
    << "for (int i=0; i < " << this->vector_name_  << "_vector_size-1; i++)" << std::endl
    << "{";

  if (this->is_probe_)
  {
    this->cppfile_
      << "if (!(in >> this->" << this->vector_name_ << "_[i]))" << std::endl
      << "  ACE_ERROR_RETURN ((LM_ERROR," << std::endl
      << "ACE_TEXT (\"%T (%t) - %M - failed to unpackage " << this->vector_name_ << "\\n\"))," << std::endl
      << "-1);";
  }
  else
  {
    this->cppfile_
      << "if (!(in >> s." << this->vector_name_ << "[i]))" << std::endl
      << "  ACE_ERROR_RETURN ((LM_ERROR," << std::endl
      << "ACE_TEXT (\"%T (%t) - %M - failed to unpackage " << this->vector_name_ << "\\n\"))," << std::endl
      << "-1);";
  }

  this->cppfile_
    << "}" << std::endl;
}

//
// visit_struct
//
void Recall_Generator::visit_struct (const OASIS_PDL_Struct & s)
{
  this->is_probe_ = false;

  this->hfile_
    << "/// Extraction operator for ::" << s.fq_name ("::") << std::endl
    << "bool operator >> (ACE_InputCDR &, "
    << "const ::" << s.fq_name ("::") <<  " &);"
    << std::endl;

  this->cppfile_
    << function_header ("operator >>")
    << "bool operator >> (ACE_InputCDR & in, "
    << "::" << s.fq_name ("::") <<  " & s) {";

  std::for_each (s.members ().begin (),
                 s.members ().end (),
                 boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                              _1,
                              boost::ref (*this)));

  this->cppfile_
    << "return in.good_bit ();"
    << "}";
}

//
// visit_simple_type
//
void Recall_Generator::visit_simple_type (const OASIS_PDL_Simple_Type & s)
{

}

}
}
