// $Id: Probe_Schema_Generator_Visitor.cpp 1896 2011-09-07 14:56:19Z hillj $

#include "Probe_Schema_Generator_Visitor.h"
#include "Schema_Type_Generator.h"

#include "fe/PDL_File.h"
#include "fe/PDL_Module.h"
#include "fe/PDL_Probe.h"
#include "fe/PDL_Simple_Type.h"
#include "fe/PDL_Struct.h"
#include "fe/PDL_Vector_Type.h"

#include "boost/bind.hpp"
#include <algorithm>

//
// OASIS_PDL_Probe_Schema_Generator_Visitor
//
OASIS_PDL_Probe_Schema_Generator_Visitor::
OASIS_PDL_Probe_Schema_Generator_Visitor (std::ostream & out)
: out_ (out)
{

}

//
// ~OASIS_PDL_Probe_Schema_Generator_Visitor
//
OASIS_PDL_Probe_Schema_Generator_Visitor::
~OASIS_PDL_Probe_Schema_Generator_Visitor (void)
{

}

//
// visit_file
//
void OASIS_PDL_Probe_Schema_Generator_Visitor::
visit_file (const OASIS_PDL_File & file)
{
  // Start the schema specification.
  this->out_
    << "<?xml version='1.0' ?>" << std::endl
    << "<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema' " << std::endl
    << "            xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' " << std::endl
    << "            xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd' " << std::endl
    << "            elementFormDefault='qualified' " << std::endl
    << "            version='1.0'>" << std::endl;

  std::for_each (file.decls ().begin (),
                 file.decls ().end (),
                 boost::bind (&OASIS_PDL_Declaration::accept,
                              _1,
                              boost::ref (*this)));

  // End the schema specification.
  this->out_
    << "</xsd:schema>" << std::endl;
}

//
// visit_module
//
void OASIS_PDL_Probe_Schema_Generator_Visitor::
visit_module (const OASIS_PDL_Module & module)
{
  std::for_each (module.decls ().begin (),
                 module.decls ().end (),
                 boost::bind (&OASIS_PDL_Declaration::accept,
                              _1,
                              boost::ref (*this)));
}

//
// visit_probe
//
void OASIS_PDL_Probe_Schema_Generator_Visitor::
visit_probe (const OASIS_PDL_Probe & probe)
{
  // Start a new complex type
  this->complex_type_begin (probe);

  OASIS_PDL_Schema_Type_Generator type_gen (this->out_);
  if (probe.has_base_probe ())
  {
    // Start the extension specification.
    this->out_
      << "<xsd:complexContent>" << std::endl
      << "<xsd:extension base='";

    probe.base_probe ()->accept (type_gen);

    this->out_
      << "'>" << std::endl;
  }

  // Generate the members of the probe.
  this->visit_complex_type (probe);

  if (probe.has_base_probe ())
  {
    // End the extension specification.
    this->out_
      << "</xsd:extension>" << std::endl
      << "</xsd:complexContent>" << std::endl;
  }

  // End the complex type.
  this->complex_type_end ();

  // Next, declare a top-level element for this probe.
  this->out_
    << std::endl
    << "  <xsd:element name='";

  probe.accept (type_gen);

  this->out_
    << "Probe' type='";

  probe.accept (type_gen);

  this->out_
    << "' />" << std::endl;
}

//
// visit_struct
//
void OASIS_PDL_Probe_Schema_Generator_Visitor::
visit_struct (const OASIS_PDL_Struct & s)
{
  this->complex_type_begin (s);
  this->visit_complex_type (s);
  this->complex_type_end ();
}

//
// visit_complex_type_member
//
void OASIS_PDL_Probe_Schema_Generator_Visitor::
visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m)
{
  // Write the type information for the member.
  this->out_
    << "      <xsd:element name='" << m.name () << "' type='";

  OASIS_PDL_Schema_Type_Generator type_gen (this->out_);

  if (m.type ())
    m.type ()->accept (type_gen);

  this->out_
    << "' />" << std::endl;
}

//
// visit_complex_type
//
void OASIS_PDL_Probe_Schema_Generator_Visitor::
visit_complex_type (const OASIS_PDL_Complex_Type & t)
{
  this->out_
    << "    <xsd:sequence>" << std::endl;

  std::for_each (t.members ().begin (),
                 t.members ().end (),
                 boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                              _1,
                              boost::ref (*this)));

  // Close the structure's definition.
  this->out_
    << "    </xsd:sequence>" << std::endl;
}

//
// complex_type_begin
//
void OASIS_PDL_Probe_Schema_Generator_Visitor::
complex_type_begin (const OASIS_PDL_Complex_Type & t)
{
  this->out_
    << std::endl
    << "  <xsd:complexType name='";

  OASIS_PDL_Schema_Type_Generator type_gen (this->out_);
  t.accept (type_gen);

  this->out_
    << "'>" << std::endl;
}

//
// complex_type_end
//
void OASIS_PDL_Probe_Schema_Generator_Visitor::
complex_type_end (void)
{
  this->out_
    << "  </xsd:complexType>" << std::endl;
}

//
// visit_vector_type
//
void OASIS_PDL_Probe_Schema_Generator_Visitor::
visit_vector_type (const OASIS_PDL_Vector_Type & v)
{
  // Write the type information for the member.
  this->out_
    << "      <xsd:element name='" << v.name () << "' type='";

  OASIS_PDL_Schema_Type_Generator type_gen (this->out_);

  if (v.type ())
    v.type ()->accept (type_gen);

  this->out_
    << "' minOccurs='0' maxOccurs='unbounded' />" << std::endl;
}

