// $Id: Impl_Probe_Cpp_Generator_Visitor.cpp 2222 2012-11-20 17:02:16Z dfeiock $

#include "Impl_Probe_Cpp_Generator_Visitor.h"
#include "Probe_Cpp_Schema_Generator.h"
#include "Package_Data_Generator.h"
#include "Impl_Attribute_Generator.h"
#include "Impl_Var_Type_Generator.h"
#include "Flush_Generator.h"
#include "Impl_Dump_Generator.h"
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
// OASIS_PDL_Impl_Probe_Cpp_Generator_Visitor
//
OASIS_PDL_Impl_Probe_Cpp_Generator_Visitor::
OASIS_PDL_Impl_Probe_Cpp_Generator_Visitor (std::ostream & hfile, std::ostream & cppfile)
: hfile_ (hfile),
  cppfile_ (cppfile)
{

}

//
// ~OASIS_PDL_Impl_Probe_Cpp_Generator_Visitor
//
OASIS_PDL_Impl_Probe_Cpp_Generator_Visitor::
~OASIS_PDL_Impl_Probe_Cpp_Generator_Visitor (void)
{

}

//
// visit_file
//
void OASIS_PDL_Impl_Probe_Cpp_Generator_Visitor::
visit_file (const OASIS_PDL_File & file)
{
  std::string hashdef (file.name () + "Impl");
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
    << " * @file        " << file.name () << "Impl.h" << std::endl
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
    << "#include \"" << file.name () << "_Metadata.h\"" << std::endl
    << "#include \"oasis/probes/Software_Probe_Impl.h\"" << std::endl
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
    << "#include \"" << file.name () << "Impl.h\"" << std::endl
    << "#include \"oasis/streams.h\"" << std::endl
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
void OASIS_PDL_Impl_Probe_Cpp_Generator_Visitor::
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
void OASIS_PDL_Impl_Probe_Cpp_Generator_Visitor::
visit_probe (const OASIS_PDL_Probe & probe)
{
  this->generate_impl (probe);
}

//
// generate_impl
//
void OASIS_PDL_Impl_Probe_Cpp_Generator_Visitor::
generate_impl (const OASIS_PDL_Probe & probe)
{
  const std::string impl_name = probe.name () + "Impl";
  const std::string metadata_name = probe.fq_name ("::") + "_Metadata";

  // Make sure we know the base probe type.
  std::string base_probe =
    probe.has_base_probe () ?
    ("::" + probe.base_probe ()->fq_name ("::") + "Impl") : "virtual ::OASIS::Software_Probe_Impl";

  // We are going to first write the stub class for this probe.
  // This stub will be use by the probe's implementation, which
  // is generated next.
  this->hfile_
    << "/**" << std::endl
    << " * @class " << impl_name << std::endl
    << " */" << std::endl
    << "class ";

  if (!OASIS_PDL_BE::Cpp::CONFIGURATION::instance ()->export_macro_.empty ())
    this->hfile_ << OASIS_PDL_BE::Cpp::CONFIGURATION::instance ()->export_macro_ << " ";

  this->hfile_
    << impl_name << " :" << std::endl
    << "  public " << base_probe << "{"
    << "public:" << std::endl
    << "/// The metadata for the software probe." << std::endl
    << "static const ::" << metadata_name << " __metadata__;"
    << std::endl
    << "/// Default constructor" << std::endl
    << impl_name << " (void);"
    << std::endl;

  // Determine if the probe has a concrete or abstract destructor
  if (probe.attr ()->is_abstract_)
  {
    this->hfile_
      << "/// Destructor" << std::endl
      << "virtual ~" << impl_name << " (void) = 0;";
  }
  else
  {
    this->hfile_
      << "/// Destructor" << std::endl
      << "virtual ~" << impl_name << " (void);";
  }

  // Generate the metadata method
  this->hfile_
    << std::endl
    << "/// Getter for the probe's metadata" << std::endl
    << "virtual const ::" << metadata_name << " & metadata (void) const;";

  using OASIS_PDL_BE::Cpp::function_header;

  // Generate the software probe's constructor
  this->cppfile_
    << std::endl
    << function_header (impl_name)
    << impl_name << "::" << impl_name << " (void) { this->uuid_ = this->metadata ().uuid_;"
    << "}";

  // Generate the metadata method
  this->cppfile_
    << function_header (impl_name + "::__metadata__")
    << "const ::" << metadata_name << " " << impl_name << "::__metadata__ =" << std::endl
    << "::" << metadata_name << " ();" << std::endl
    << std::endl
    << function_header (impl_name + "::metadata")
    << "const ::" << metadata_name << " & " << impl_name << "::"
    << "metadata (void) const {"
    << "return ::" << probe.fq_name ("::") << "Impl::__metadata__;" << std::endl
    << "}";

  // Generate the software probe's destructor
  this->cppfile_
    << function_header ("~" + impl_name)
    << impl_name << "::~" << impl_name << " (void) {"
    << "}";

  // Generate the source code for packaging the structure.
  OASIS_PDL_BE::Cpp::Package_Data_Generator package_gen (this->hfile_, this->cppfile_);
  probe.accept (package_gen);

  // Generate the dump method for the implementation
  OASIS_PDL_BE::Cpp::Impl_Dump_Generator dump_gen (this->hfile_, this->cppfile_);
  probe.accept (dump_gen);

  if (!probe.members ().empty ())
  {
    // Generate the setter/getter attributes.
    this->hfile_
      << std::endl
      << "public:";

    OASIS_PDL_BE::Cpp::Impl_Attribute_Generator attr_gen (this->hfile_, this->cppfile_);
    probe.accept (attr_gen);

    // Generate the variables for this software probe.
    this->hfile_
      << std::endl
      << "protected:" << std::endl;

    OASIS_PDL_BE::Cpp::Impl_Var_Type_Generator variable_gen (this->hfile_, true);
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
void OASIS_PDL_Impl_Probe_Cpp_Generator_Visitor::
visit_struct (const OASIS_PDL_Struct & s)
{
  const std::string impl_name = s.name () + "Impl";

  this->hfile_
    << "/**" << std::endl
    << " * @struct " << impl_name << std::endl
    << " */" << std::endl
    << "struct ";

  if (!OASIS_PDL_BE::Cpp::CONFIGURATION::instance ()->export_macro_.empty ())
    this->hfile_ << OASIS_PDL_BE::Cpp::CONFIGURATION::instance ()->export_macro_ << " ";

  this->hfile_
    << impl_name << "{";

  OASIS_PDL_BE::Cpp::Impl_Var_Type_Generator variable_gen (this->hfile_, false);
  std::for_each (s.members ().begin (),
                 s.members ().end (),
                 boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                              _1,
                              boost::ref (variable_gen)));

  // Generate the source code for dumping the structure.
  OASIS_PDL_BE::Cpp::Impl_Dump_Generator dump_gen (this->hfile_, this->cppfile_);
  s.accept (dump_gen);

  // Generate the source code for packaging the structure.
  OASIS_PDL_BE::Cpp::Package_Data_Generator package_gen (this->hfile_, this->cppfile_);
  s.accept (package_gen);

  this->hfile_
    << "};";

}


