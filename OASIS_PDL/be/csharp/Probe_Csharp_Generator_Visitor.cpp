// $Id: Probe_Csharp_Generator_Visitor.cpp 2118 2012-01-13 20:29:17Z dpuranik $

#include "Probe_Csharp_Generator_Visitor.h"
#include "Probe_Csharp_Schema_Generator.h"
#include "Package_Data_Generator.h"
#include "Attribute_Generator.h"
#include "Var_Type_Generator.h"
#include "Flush_Generator.h"
#include "Recall_Generator.h"
#include "Package_Data_Generator.h"
#include "Csharp.h"

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
// OASIS_PDL_Probe_Csharp_Generator_Visitor
//
OASIS_PDL_Probe_Csharp_Generator_Visitor::
OASIS_PDL_Probe_Csharp_Generator_Visitor (std::ostream & csfile)
: csfile_(csfile)
{

}

//
// ~OASIS_PDL_Probe_Csharp_Generator_Visitor
//
OASIS_PDL_Probe_Csharp_Generator_Visitor::
~OASIS_PDL_Probe_Csharp_Generator_Visitor (void)
{

}

//
// visit_file
//
void OASIS_PDL_Probe_Csharp_Generator_Visitor::
visit_file (const OASIS_PDL_File & file)
{
  //Write the file's preamble
  this->csfile_
    << "// -*- C# -*-" << std::endl
    << std::endl
    << std::left << std::setw (78) << std::setfill ('=') << "//" << std::endl
    << "/**" << std::endl
    << " * @file        " << file.name () << ".cs" << std::endl
    << " *" << std::endl
    << " * $" << "Id" << "$" << std::endl
    << " *" << std::endl
    << " * @author      Darshan G. Puranik (dpuranik at cs dot iupui dot edu)" << std::endl
    << " *              OASIS Software Probe Generator (C# Version)" << std::endl
    << " *              http://www.cs.iupui.edu/oasis" << std::endl
    << " */" << std::endl
    << std::left << std::setw (78) << std::setfill ('=') << "//" << std::endl
    << "using System;"<<std::endl;

    std::for_each(file.decls ().begin (),
                  file.decls ().end (),
                  boost::bind (&OASIS_PDL_Declaration::accept,
                               _1,
                               boost::ref (*this)));
}

//
// visit_module
//
void OASIS_PDL_Probe_Csharp_Generator_Visitor::
visit_module (const OASIS_PDL_Module & module)
{
  this->csfile_
    << "namespace " << module.name () << "{";

  std::for_each (module.decls ().begin (),
                 module.decls ().end (),
                 boost::bind (&OASIS_PDL_Declaration::accept,
                              _1,
                              boost::ref (*this)));

  this->csfile_ << "}";
}

//
// visit_probe
//
void OASIS_PDL_Probe_Csharp_Generator_Visitor::
visit_probe (const OASIS_PDL_Probe & probe)
{
  this->generate_stub (probe);
  this->generate_impl (probe);
}

//
// generate_stub
//
void OASIS_PDL_Probe_Csharp_Generator_Visitor::
generate_stub (const OASIS_PDL_Probe & probe)
{
  const std::string & name = probe.name ();

  // We are going to first write the stub class for this probe.
  // This stub will be use by the probe's implementation, which
  // is generated next.
  this->csfile_
    << "/**" << std::endl
    << " * @class " << name << std::endl
    << " */" << std::endl
    << "public class "<< name << " : Software_Probe_Impl"<<std::endl
    << "{"<<std::endl
    << "/// The software probe's XML Schema Definition." << std::endl
    << "public static string __schema__ ="<<std::endl;

  // Generate the schema definition for the software probe. We are going
  // to define it as a quoted string.
  OASIS_PDL_Probe_Csharp_Schema_Generator schema_gen (this->csfile_);
  probe.accept (schema_gen);

  std::string uuid (probe.attr ()->uuid_.to_string ()->c_str ());
  std::transform (uuid.begin (),
                  uuid.end (),
                  uuid.begin (),
                  &::toupper);

  // Generate the software probe's metadata.
  this->csfile_
    << std::endl
    << "public static Software_Probe_Metadata "
    << "__metadata__ = new Software_Probe_Metadata ("<<std::endl
    << "new Uuid (\""
    << uuid << "\")," << std::endl
    << "\""<<probe.fq_name (".").c_str () <<"\""<< "," << std::endl
    << "'"<<probe.attr ()->version_major_ <<"'"<< "," << std::endl
    << "'"<<probe.attr ()->version_minor_ << "'"<<"," << std::endl
    << "__schema__);"
    << std::endl;

  // We are now ready to generate the constructor and destructor
  // for the software probe's stub. Luckily, there is no logic
  // added to either method.
  this->csfile_
    << "public " << name << " ()"<< std::endl
    << "{"<<std::endl
    << "}"<<std::endl;

  // Generate the recall method for the implementation.
  OASIS_PDL_BE::Csharp::Package_Data_Generator package_gen (this->csfile_);
  probe.accept (package_gen);

  // Generate the recall method for the implementation.
  OASIS_PDL_BE::Csharp::Recall_Generator recall_gen (this->csfile_);
  probe.accept (recall_gen);

  if (!probe.members ().empty ())
  {
  OASIS_PDL_BE::Csharp::Attribute_Generator attr_gen (this->csfile_);
    probe.accept (attr_gen);

  OASIS_PDL_BE::Csharp::Var_Type_Generator variable_gen (this->csfile_, true);
    std::for_each (probe.members ().begin (),
                   probe.members ().end (),
                   boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                                _1,
                                boost::ref (variable_gen)));

  }

  this->csfile_
    <<std::endl
    <<"}";
}

//
// generate_impl
//
void OASIS_PDL_Probe_Csharp_Generator_Visitor::
generate_impl (const OASIS_PDL_Probe & probe)
{
  const std::string impl_name = probe.name () + "_Impl";

  // We are going to first write the stub class for this probe.
  // This stub will be use by the probe's implementation, which
  // is generated next.
  this->csfile_
    << "/**" << std::endl
    << " * @class " << impl_name << std::endl
    << " */" << std::endl
    << "public class "
    << impl_name << " : "
    << probe.name () << std::endl
    << "{" << std::endl
    << "/// Default constructor" << std::endl
    << "public "<<impl_name << " ()"<< std::endl
    << "{"<<std::endl
    << "this.packager_.init (" << probe.name () << ".__metadata__.uuid_);"<<std::endl
    << "}"<<std::endl;

  // Generate the flush method for the implementation.
  OASIS_PDL_BE::Csharp::Flush_Generator flush_gen (this->csfile_);
  probe.accept (flush_gen);

  this->csfile_
    << "}";
}

//
// visit_struct
//
void OASIS_PDL_Probe_Csharp_Generator_Visitor::
visit_struct (const OASIS_PDL_Struct & s)
{
  this->csfile_
    << "/**" << std::endl
    << " * @struct " << s.name () << std::endl
    << " */" << std::endl
    << "public struct "<<s.name()<<std::endl
    <<"{";

  OASIS_PDL_BE::Csharp::Var_Type_Generator variable_gen (this->csfile_, false);
  std::for_each (s.members ().begin (),
          s.members ().end (),
          boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                  _1,
                  boost::ref (variable_gen)));

  // Generate the source code for packaging the structure.
  OASIS_PDL_BE::Csharp::Package_Data_Generator package_gen (this->csfile_);
  s.accept (package_gen);

  // Generate the source code for recalling data.
  OASIS_PDL_BE::Csharp::Recall_Generator recall_gen (this->csfile_);
  s.accept (recall_gen);

  this->csfile_
    <<"}";
}