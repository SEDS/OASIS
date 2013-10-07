// $Id: Flush_Generator.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "Flush_Generator.h"
#include "Cpp.h"

#include "fe/PDL_Probe.h"
#include "fe/PDL_Struct.h"
#include "fe/PDL_Simple_Type.h"

#include "boost/bind.hpp"
#include <algorithm>

namespace OASIS_PDL_BE
{
namespace Cpp
{
//
// Flush_Generator
//
Flush_Generator::
Flush_Generator (std::ostream & hfile, std::ostream & cppfile)
: hfile_ (hfile),
  cppfile_ (cppfile)
{

}

//
// ~Flush_Generator
//
Flush_Generator::~Flush_Generator (void)
{

}

//
// visit_probe
//
void Flush_Generator::visit_probe (const OASIS_PDL_Probe & p)
{
  const std::string name = p.name () + "Impl";
  this->is_probe_ = true;

  // Make sure we know the base probe type.
  std::string base_probe =
    p.has_base_probe () ?
    ("::" + p.base_probe ()->fq_name ("::")) : "::OASIS::Software_Probe_Impl";

  this->hfile_
    << std::endl
    << "/// Flush the contents. This method is not allowed to be overloaded" << std::endl
    << "/// past the implementation of this class." << std::endl
    << "virtual int flush (void);"
    << std::endl;

  // Implement the flush method.
  this->cppfile_
    << function_header ("flush")
    << "int " << name << "::flush (void) {"
    << "if (0 != this->package_data (this->packager_))" << std::endl
    << "  ACE_ERROR_RETURN ((LM_ERROR," << std::endl
    << "ACE_TEXT (\"%T (%t) - %M - failed to package data\\n\"))," << std::endl
    << "-1);"
    << std::endl
    << single_line_comment ("Send the data to the EINode.")
    << "return this->send_data (this->packager_);"
    << "}";
}

}
}
