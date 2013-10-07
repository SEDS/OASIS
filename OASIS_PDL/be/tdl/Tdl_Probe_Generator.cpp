// $Id: Tdl_Probe_Generator.cpp 1942 2011-09-28 18:36:18Z dfeiock $

#include "Tdl_Probe_Generator.h"
#include "Tdl_Type_Generator.h"

#include "fe/PDL_File.h"
#include "fe/PDL_Module.h"
#include "fe/PDL_Probe.h"
#include "fe/PDL_Simple_Type.h"
#include "fe/PDL_Struct.h"

#include "boost/bind.hpp"
#include <algorithm>
#include <sstream>
#include <stack>

//
// OASIS_PDL_Tdl_Probe_Generator
//
OASIS_PDL_Tdl_Probe_Generator::
OASIS_PDL_Tdl_Probe_Generator (std::ostream & out)
: tdl_ (out)
{

}

//
// ~OASIS_PDL_Tdl_Probe_Generator
//
OASIS_PDL_Tdl_Probe_Generator::~OASIS_PDL_Tdl_Probe_Generator (void)
{

}

//
// visit_file
//
void OASIS_PDL_Tdl_Probe_Generator::
visit_file (const OASIS_PDL_File & file)
{
  this->tdl_
    << "// -*- TDL -*-" << nl
    << nl
    << "//=====================================================================" << nl
    << "/**" << nl
    << " * @file" << nl
    << " *" << nl
    << " * $" << "Id" << "$" << nl
    << " *" << nl
    << " * @author  James H. Hill <hillj@cs.iupui.edu>" << nl
    << " */" << nl
    << "//=====================================================================" << nl
    << nl
    << "import <OASIS-SoftwareProbe-v0.3.tdl>" << nl
    << nl;

  std::for_each (file.decls ().begin (),
                 file.decls ().end (),
                 boost::bind (&OASIS_PDL_Declaration::accept,
                              _1,
                              boost::ref (*this)));
}

//
// visit_module
//
void OASIS_PDL_Tdl_Probe_Generator::
visit_module (const OASIS_PDL_Module & module)
{
  // Start a new package.
  this->tdl_
      << "package " << module.name () << nl
      << "{" << idt << nl;

  std::for_each (module.decls ().begin (),
                 module.decls ().end (),
                 boost::bind (&OASIS_PDL_Declaration::accept,
                              _1,
                              boost::ref (*this)));

  // End the current package.
  this->tdl_
    << uidt_nl << "};";
}

//
// visit_probe
//
void OASIS_PDL_Tdl_Probe_Generator::
visit_probe (const OASIS_PDL_Probe & probe)
{
  // Determine the correct base class.
  const std::string base_class =
    probe.has_base_probe () ? ("::" + probe.base_probe ()->scope ("::") + "::" + probe.base_probe ()->name ()) :
    "::OASIS::Middleware::SoftwareProbe";

  // Generate the class definition for the software probe.
  this->tdl_
    << "class " << probe.name () << " : extends " << base_class << nl
    << "{" << idt;

  std::for_each (probe.members ().begin (),
                 probe.members ().end (),
                 boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                              _1,
                              boost::ref (*this)));

  this->tdl_
    << uidt_nl << "};" << nl
    << nl;
}

//
// visit_complex_type_member
//
void OASIS_PDL_Tdl_Probe_Generator::
visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m)
{
  this->tdl_ << nl;

  OASIS_PDL_Tdl_Type_Generator type_gen (this->tdl_);

  if (m.type ())
    m.type ()->accept (type_gen);

  this->tdl_ << " " << m.name () << ";";
}
