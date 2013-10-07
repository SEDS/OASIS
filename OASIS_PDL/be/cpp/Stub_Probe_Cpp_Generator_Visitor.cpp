// $Id: Stub_Probe_Cpp_Generator_Visitor.cpp 2212 2012-07-31 18:26:22Z hillj $

#include "Stub_Probe_Cpp_Generator_Visitor.h"
#include "Probe_Cpp_Schema_Generator.h"
#include "Stub_Attribute_Generator.h"
#include "Stub_Var_Type_Generator.h"
#include "Recall_Generator.h"
#include "Stub_Dump_Generator.h"
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
// OASIS_PDL_Stub_Probe_Cpp_Generator_Visitor
//
OASIS_PDL_Stub_Probe_Cpp_Generator_Visitor::
OASIS_PDL_Stub_Probe_Cpp_Generator_Visitor (std::ostream & hfile, std::ostream & cppfile)
: hfile_ (hfile),
  cppfile_ (cppfile)
{

}

//
// ~OASIS_PDL_Stub_Probe_Cpp_Generator_Visitor
//
OASIS_PDL_Stub_Probe_Cpp_Generator_Visitor::
~OASIS_PDL_Stub_Probe_Cpp_Generator_Visitor (void)
{

}

//
// visit_file
//
void OASIS_PDL_Stub_Probe_Cpp_Generator_Visitor::
visit_file (const OASIS_PDL_File & file)
{
  std::string hashdef (file.name () + "");
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
    << " * @file        " << file.name () << ".h" << std::endl
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
    << "#include \"oasis/probes/Data_Types.h\"" << std::endl
    << "#include \"oasis/probes/Software_Probe.h\"" << std::endl
    << "#include \"" << file.name () << "_Metadata.h\"" << std::endl
    << "#include <iostream>" << std::endl
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
    << "#include \"" << file.name () << ".h\"" << std::endl
    << "#include \"oasis/streams.h\"" << std::endl
    << "#include \"oasis/probes/Software_Probe_Data_Preparer.h\"" << std::endl
    << "#include \"oasis/probes/Data_Streams_T.h\"" << std::endl
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
void OASIS_PDL_Stub_Probe_Cpp_Generator_Visitor::
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
void OASIS_PDL_Stub_Probe_Cpp_Generator_Visitor::
visit_probe (const OASIS_PDL_Probe & probe)
{
  this->generate_stub (probe);
}

//
// generate_stub
//
void OASIS_PDL_Stub_Probe_Cpp_Generator_Visitor::
generate_stub (const OASIS_PDL_Probe & probe)
{
  const std::string & name = probe.name ();
  const std::string & metadata_name = probe.fq_name ("::") + "_Metadata";

  // We are going to first write the stub class for this probe.
  // This stub will be use by the probe's implementation, which
  // is generated next.
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
    ("::" + probe.base_probe ()->fq_name ("::")) : "virtual ::OASIS::Software_Probe";

  this->hfile_
    << name << " :" << std::endl
    << "  public " << base_probe << " {"
    << "public:" << std::endl
    << "// Type definition of the software probe's metadata." << std::endl
    << "typedef ::" << metadata_name << " METADATA_TYPE;"
    << std::endl
    << "/// The metadata for the software probe." << std::endl
    << "static const METADATA_TYPE __metadata__;"
    << std::endl
    << "/// Default constructor" << std::endl
    << name << " (void);"
    << std::endl
    << "/// Destructor" << std::endl
    << "virtual ~" << name << " (void);"
    << std::endl
    << "/// Getter for the probe's metadata" << std::endl
    << "virtual const METADATA_TYPE & metadata (void) const;";

  using OASIS_PDL_BE::Cpp::function_header;

  // Generate the metadata method
  this->cppfile_
    << std::endl
    << function_header (name + "::__metadata__")
    << "const " << name << "::METADATA_TYPE " << name << "::__metadata__;"
    << std::endl
    << function_header (name + "::metadata")
    << "const " << name << "::METADATA_TYPE & " << name << "::"
    << "metadata (void) const {"
    << "return ::" << probe.fq_name ("::") << "::__metadata__;" << std::endl
    << "}";

  // We are now ready to generate the constructor and destructor
  // for the software probe's stub. Luckily, there is no logic
  // added to either method.
  this->cppfile_
    << function_header (name)
    << name << "::" << name << " (void) {"
    << "}"
    << function_header ("~" + name)
    << name << "::~" << name << " (void) {"
    << "}";

  // Generate the recall method for the implementation.
  OASIS_PDL_BE::Cpp::Recall_Generator recall_gen (this->hfile_, this->cppfile_);
  probe.accept (recall_gen);

  // Generate the dump method for the implementation
  OASIS_PDL_BE::Cpp::Stub_Dump_Generator dump_gen (this->hfile_, this->cppfile_);
  probe.accept (dump_gen);

  if (!probe.members ().empty ())
  {
    // Generate the setter/getter attributes.
    this->hfile_
      << std::endl
      << "public:";

    OASIS_PDL_BE::Cpp::Stub_Attribute_Generator attr_gen (this->hfile_, this->cppfile_);
    probe.accept (attr_gen);

    // Generate the variables for this software probe.
    this->hfile_
      << std::endl
      << "protected:" << std::endl;

    OASIS_PDL_BE::Cpp::Stub_Var_Type_Generator variable_gen (this->hfile_, true);
    std::for_each (probe.members ().begin (),
                   probe.members ().end (),
                   boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                                _1,
                                boost::ref (variable_gen)));
  }

  this->hfile_
    << "};";
}

//
// visit_struct
//
void OASIS_PDL_Stub_Probe_Cpp_Generator_Visitor::
visit_struct (const OASIS_PDL_Struct & s)
{
  this->hfile_
    << "/**" << std::endl
    << " * @struct " << s.name () << std::endl
    << " */" << std::endl
    << "struct ";

  if (!OASIS_PDL_BE::Cpp::CONFIGURATION::instance ()->export_macro_.empty ())
    this->hfile_ << OASIS_PDL_BE::Cpp::CONFIGURATION::instance ()->export_macro_ << " ";

  this->hfile_
    << s.name () << "{";

  OASIS_PDL_BE::Cpp::Stub_Var_Type_Generator variable_gen (this->hfile_, false);
  std::for_each (s.members ().begin (),
                 s.members ().end (),
                 boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                              _1,
                              boost::ref (variable_gen)));

  // Generate the source code for dumping the structure.
  OASIS_PDL_BE::Cpp::Stub_Dump_Generator dump_gen (this->hfile_, this->cppfile_);
  s.accept (dump_gen);

  this->hfile_
    << "};";

  OASIS_PDL_BE::Cpp::Recall_Generator recall_gen (this->hfile_, this->cppfile_);
  s.accept (recall_gen);
}


