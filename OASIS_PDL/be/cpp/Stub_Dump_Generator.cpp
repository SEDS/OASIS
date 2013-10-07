// $Id: Stub_Dump_Generator.cpp 2214 2012-08-10 15:00:08Z dfeiock $

#include "Stub_Dump_Generator.h"
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
// Stub_Dump_Generator
//
Stub_Dump_Generator::
Stub_Dump_Generator (std::ostream & hfile, std::ostream & cppfile)
: hfile_ (hfile),
  cppfile_ (cppfile)
{

}

//
// Stub_Dump_Variable_Generator
//
Stub_Dump_Variable_Generator::
Stub_Dump_Variable_Generator (std::ostream & hfile, std::ostream & cppfile)
: hfile_ (hfile),
  cppfile_ (cppfile),
  name_ (),
  parent_is_probe_ (false)
{

}

//
// ~Stub_Dump_Generator
//
Stub_Dump_Generator::~Stub_Dump_Generator (void)
{

}

//
// ~Stub_Dump_Variable_Generator
//
Stub_Dump_Variable_Generator::~Stub_Dump_Variable_Generator (void)
{

}

//
// name
//
void Stub_Dump_Variable_Generator::name (const ::std::string & name)
{
  this->name_ = name;
}

//
// parent_is_probe
//
void Stub_Dump_Variable_Generator::parent_is_probe (const bool & parent)
{
  this->parent_is_probe_ = parent;
}

//
// visit_probe
//
void Stub_Dump_Generator::visit_probe (const OASIS_PDL_Probe & p)
{

  // Make sure we know the base probe type.
  const std::string base_probe =
    p.has_base_probe () ?
    ("::" + p.base_probe ()->fq_name ("::")) : "::OASIS::Software_Probe";

  const std::string & name = p.name ();

  this->hfile_
    << std::endl
    << "public:" << std::endl
    << "/// Stub_Dump the software probe's data." << std::endl
    << "virtual void dump (std::ostream & output);" << std::endl;

  // Implementation of the dump method.
  this->cppfile_
    << function_header ("dump")
    << "void " << name << "::"
    << "dump (std::ostream & output) {"
    << base_probe << "::dump (output);";

    if (!p.members ().empty ())
    {
      Stub_Dump_Variable_Generator var_gen (this->hfile_, this->cppfile_);
      var_gen.parent_is_probe (true);

      std::vector <OASIS_PDL_Complex_Type_Member *>::const_iterator
      iter = p.members ().begin (), iter_end = p.members ().end ();

      for (; iter != iter_end; ++ iter)
      {
        var_gen.name ((*iter)->name ());
        // Call accept on the actual child type
        (*iter)->type ()->accept (var_gen);
      }
    }

  this->cppfile_
    << "}";
}

//
// visit_struct
//
void Stub_Dump_Generator::visit_struct (const OASIS_PDL_Struct & s)
{
  this->hfile_
    << "/// Stub_Dump method for for ::" << s.fq_name ("::") << std::endl
    << "void dump (std::ostream & output);" << std::endl;

  this->cppfile_
    << function_header ("dump")
    << "void ::" << s.fq_name ("::") << "::"
    << "dump (std::ostream & output) {" << std::endl;

  Stub_Dump_Variable_Generator var_gen (this->hfile_, this->cppfile_);
  var_gen.parent_is_probe (false);

  std::vector <OASIS_PDL_Complex_Type_Member *>::const_iterator
  iter = s.members ().begin (), iter_end = s.members ().end ();

  for (; iter != iter_end; ++ iter)
  {
    var_gen.name ((*iter)->name ());
    // Call accept on the actual child type
    (*iter)->type ()->accept (var_gen);
  }

  this->cppfile_
    << "}";
}

//
// visit_probe
//
void Stub_Dump_Variable_Generator::visit_probe (const OASIS_PDL_Probe & p)
{
  if (this->parent_is_probe_)
  {
    this->cppfile_
      << "output << \"  " << this->name_ << ": \";"
      << "this->" << this->name_ << "_.dump (output);"
      << "output << std::endl;";
  }
  else
  {
    this->cppfile_
      << "output << \"  " << this->name_ << ": \";"
      << "this->" << this->name_ << ".dump (output);"
      << "output << std::endl;";
  }
}

//
// visit_struct
//
void Stub_Dump_Variable_Generator::visit_struct (const OASIS_PDL_Struct & s)
{
  if (this->parent_is_probe_)
  {
    this->cppfile_
      << "output << \"  " << this->name_ << ": \";"
      << "this->" << this->name_ << "_.dump (output);"
      << "output << std::endl;";
  }
  else
  {
    this->cppfile_
      << "output << \"  " << this->name_ << ": \";"
      << "this->" << this->name_ << ".dump (output);"
      << "output << std::endl;";
  }
}

//
// visit_simple_type
//
void Stub_Dump_Variable_Generator::visit_simple_type (const OASIS_PDL_Simple_Type & s)
{
  if (this->parent_is_probe_)
  {
    this->cppfile_
        << "output << \"  " << this->name_ << ": \" << this->" << this->name_ << "_"
        << " << std::endl;";
  }
  else
  {
    this->cppfile_
        << "output << \"  " << this->name_ << ": \" << this->" << this->name_
        << " << std::endl;";
  }
}

//
// visit_vector_type
//
void Stub_Dump_Variable_Generator::visit_vector_type (const OASIS_PDL_Vector_Type & v)
{
  const char * suffix;
  if (this->parent_is_probe_)
    suffix = "_";
  else
    suffix = "";

  this->cppfile_
    << "for (size_t i = 0; i < this->" << this->name_ << suffix << ".size (); i++)" << std::endl
    << "{"
    << "  output << \"  start ports[\" << i << \"]:\" << std::endl;";

  // Check the vector's type.  Simple types can be pushed to the stream directly,
  // complex types must call dump.
  OASIS_PDL_Simple_Type * tp = dynamic_cast <OASIS_PDL_Simple_Type *> (v.type ());
  if (tp != 0)
  {
    this->cppfile_
      << "  output << this->" << this->name_ << suffix << "[i] << std::endl;";
  }
  else
  {
    this->cppfile_
      << "  this->" << this->name_ << suffix << "[i].dump (output);";
  }

  this->cppfile_
    << "  output << \"  end ports[\" << i << \"]:\" << std::endl;"
    << "}";
}

}
}
