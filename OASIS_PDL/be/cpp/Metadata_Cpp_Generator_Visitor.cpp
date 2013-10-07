// $Id: Metadata_Cpp_Generator_Visitor.cpp 2250 2013-09-07 19:38:37Z hillj $

#include "Metadata_Cpp_Generator_Visitor.h"
#include "Probe_Cpp_Schema_Generator.h"
#include "Cpp.h"
#include "Configuration.h"

#include "fe/PDL_Configuration.h"
#include "fe/PDL_File.h"
#include "fe/PDL_Module.h"
#include "fe/PDL_Probe.h"
#include "fe/PDL_Simple_Type.h"
#include "fe/PDL_Struct.h"

#include "boost/bind.hpp"
#include <algorithm>
#include <iomanip>
#include <ostream>

//
// OASIS_PDL_Metadata_Cpp_Generator_Visitor
//
OASIS_PDL_Metadata_Cpp_Generator_Visitor::
OASIS_PDL_Metadata_Cpp_Generator_Visitor (std::ostream & hfile, std::ostream & cppfile)
: hfile_ (hfile),
  cppfile_ (cppfile)
{

}

//
// ~OASIS_PDL_Metadata_Cpp_Generator_Visitor
//
OASIS_PDL_Metadata_Cpp_Generator_Visitor::
~OASIS_PDL_Metadata_Cpp_Generator_Visitor (void)
{

}

//
// visit_file
//
void OASIS_PDL_Metadata_Cpp_Generator_Visitor::
visit_file (const OASIS_PDL_File & file)
{
  std::string hashdef (file.name () + "_Metadata");
  std::transform (hashdef.begin (),
                  hashdef.end (),
                  hashdef.begin (),
                  &::toupper);

  std::replace (hashdef.begin (), hashdef.end (), '-', '_');
  hashdef = "_" + hashdef + "_H_";

  // Write the file's preable.
  this->hfile_
    << "// -*- C++ -*-" << std::endl
    << std::endl
    << std::left << std::setw (78) << std::setfill ('=') << "//" << std::endl
    << "/**" << std::endl
    << " * @file        " << file.name () << "_Metadata.h" << std::endl
    << " *" << std::endl
    << " * $" << "Id" << "$" << std::endl
    << " *" << std::endl
    << " * @author      James H. Hill (hillj at cs dot iupui dot edu)" << std::endl
    << " *              OASIS Software Probe Generator (C++ Version)" << std::endl
    << " *              http://www.cs.iupui.edu/oasis" << std::endl
    << " */" << std::endl
    << std::left << std::setw (78) << std::setfill ('=') << "//" << std::endl
    << std::endl
    << "#ifndef " << hashdef << std::endl
    << "#define " << hashdef << std::endl
    << std::endl
    << "#include \"oasis/probes/Software_Probe_Metadata.h\"" << std::endl
    << std::endl;

  if (!OASIS_PDL_BE::Cpp::CONFIGURATION::instance ()->export_file_.empty ())
  {
    this->hfile_
      << "#include \""
      << OASIS_PDL_BE::Cpp::CONFIGURATION::instance ()->export_file_
      << "\"" << std::endl
      << std::endl;
  }

  // Write the preamble for the source file.
  this->cppfile_
    << "// $" << "Id" << "$" << std::endl
    << std::endl
    << "#include \"" << file.name () << "_Metadata.h\"" << std::endl
    << std::endl;

  std::for_each (file.decls ().begin (),
                 file.decls ().end (),
                 boost::bind (&OASIS_PDL_Declaration::accept,
                              _1,
                              boost::ref (*this)));

  // Write the postamble for the header file.
  this->hfile_
    << "#endif  // !defined _" << hashdef << "_" << std::endl
    << std::endl;
}

//
// visit_module
//
void OASIS_PDL_Metadata_Cpp_Generator_Visitor::
visit_module (const OASIS_PDL_Module & module)
{
  this->hfile_
    << "namespace " << module.name () << "{";

  this->cppfile_
    << "namespace " << module.name () << "{";

  std::for_each (module.decls ().begin (),
                 module.decls ().end (),
                 boost::bind (&OASIS_PDL_Declaration::accept,
                              _1,
                              boost::ref (*this)));

  this->hfile_ << "}";
  this->cppfile_ << "}";
}

//
// visit_probe
//
void OASIS_PDL_Metadata_Cpp_Generator_Visitor::
visit_probe (const OASIS_PDL_Probe & probe)
{
  const std::string & name = probe.name () + "_Metadata";

  this->hfile_
    << "/**" << std::endl
    << " * @class " << name << std::endl
    << " */" << std::endl
    << "class ";

  if (!OASIS_PDL_BE::Cpp::CONFIGURATION::instance ()->export_macro_.empty ())
    this->hfile_ << OASIS_PDL_BE::Cpp::CONFIGURATION::instance ()->export_macro_ << " ";

  // Make sure we know the base probe type.
  std::string base_probe =
    probe.has_base_probe () ?
    ("::" + probe.base_probe ()->fq_name ("::") + "_Metadata") : "::OASIS::Software_Probe_Metadata";

  this->hfile_
    << name << " :" << std::endl
    << "  public " << base_probe << " {"
    << "public:" << std::endl
    << "/// Default constructor" << std::endl
    << name << " (void);"
    << std::endl
    << "/// Destructor" << std::endl
    << "virtual ~" << name << " (void);"
    << std::endl
    << "protected:" << std::endl
    << "/// Initalizing constructor" << std::endl
    << name << " (const char * uuid," << std::endl
    << "const char * type_info," << std::endl
    << "ACE_UINT8 version_major," << std::endl
    << "ACE_UINT8 version_minor," << std::endl
    << "const char * schema);" << std::endl
    << "private:" << std::endl
    << "/// The metadata's schema" << std::endl
    << "static const char * __schema__;";

  using OASIS_PDL_BE::Cpp::function_header;
  using OASIS_PDL_BE::Cpp::quoted_str;

  // Get the UUID in the correct format
  std::string uuid (probe.attr ()->uuid_.to_string ()->c_str ());
  std::transform (uuid.begin (),
                  uuid.end (),
                  uuid.begin (),
                  &::toupper);

  // Generate the schema definition for the software probe. We are going
  // to define it as a quoted string.
  this->cppfile_
    << function_header (name + "::__schema__")
    << "const char * " << name << "::__schema__ =" << std::endl;

  OASIS_PDL_Probe_Cpp_Schema_Generator schema_gen (this->cppfile_);
  probe.accept (schema_gen);

  this->cppfile_
    << std::endl;

  // We are now ready to generate the constructor and destructor implementations
  this->cppfile_
    << function_header (name)
    << name << "::" << name << " (void)" << std::endl
    << ": " << base_probe << " (" << std::endl
    << quoted_str (uuid) << "," << std::endl
    << quoted_str (probe.fq_name (".").c_str ()) << "," << std::endl
    << probe.attr ()->version_major_ << "," << std::endl
    << probe.attr ()->version_minor_ << "," << std::endl
    << "__schema__)" << std::endl
    << "{" << std::endl
    << std::endl
    << "}" << std::endl
    << function_header (name)
    << name << "::" << name << " (const char * uuid," << std::endl
    << "const char * type_info," << std::endl
    << "ACE_UINT8 version_major," << std::endl
    << "ACE_UINT8 version_minor," << std::endl
    << "const char * schema)" << std::endl
    << ": " << base_probe << " (uuid, type_info, version_major, version_minor, schema)" << std::endl
    << "{" << std::endl
    << std::endl
    << "}" << std::endl
    << function_header ("~" + name)
    << name << "::~" << name << " (void) {"
    << "}";

  // Close out the class
  this->hfile_
    << "};";
}
