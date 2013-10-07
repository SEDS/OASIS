// $Id: Probe_Csharp_Schema_Generator.cpp 2118 2012-01-13 20:29:17Z dpuranik $

#include "Probe_Csharp_Schema_Generator.h"
#include "Var_Type_Generator.h"

#include "fe/PDL_File.h"
#include "fe/PDL_Module.h"
#include "fe/PDL_Probe.h"
#include "fe/PDL_Simple_Type.h"
#include "fe/PDL_Struct.h"
#include "fe/PDL_Vector_Type.h"

#include "be/schema/Schema_Type_Generator.h"

#include "boost/bind.hpp"
#include <algorithm>
#include <set>

/**
 * @class Gather_Types
 *
 * Gather all the (complex) types defined for the software probe.
 */
class Gather_Types : public OASIS_PDL_Visitor
{
public:
  Gather_Types (std::set <const OASIS_PDL_Complex_Type *> & types)
    : types_ (types)
  {

  }

  /**
   * Destructor.
   */
  virtual ~Gather_Types (void)
  {

  }

  /// Visit a probe definition.
  virtual void visit_probe (const OASIS_PDL_Probe & p)
  {
    this->visit_complex_type (p);

    if (p.has_base_probe ())
    {
      // Save the base probe as a complex type.
      this->types_.insert (p.base_probe ());

      // Visit the base probe.
      p.base_probe ()->accept (*this);
    }
  }

  /// Visit a structure definition.
  virtual void visit_struct (const OASIS_PDL_Struct & s)
  {
    this->types_.insert (&s);
    this->visit_complex_type (s);
  }

  /// Visit the member of a complex type.
  virtual void visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m)
  {
    if (m.type ())
      m.type ()->accept (*this);
  }

private:
  void visit_complex_type (const OASIS_PDL_Complex_Type & t)
  {
    std::for_each (t.members ().begin (),
                   t.members ().end (),
                   boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                                _1,
                                boost::ref (*this)));
  }

  /// Collection of complex types.
  std::set <const OASIS_PDL_Complex_Type *> & types_;
};

/**
 * @struct quote_t
 *
 * Wrapper class for quoting a string. This class is just a placeholder
 * for the string that needs to be quoted. The actual quotation of the
 * string happens in operator <<.
 */
struct quote_t
{
  /**
   * Initializing constructor
   *
   * @param[in]       str         String to be quoted
   */
  quote_t (const std::string & str)
    : str_ (str)
  {

  }

  /// Reference to the quoted string.
  const std::string & str_;
};

//
// quote
//
quote_t quote (const std::string & str)
{
  return quote_t (str);
}

//
// operator <<
//
std::ostream & operator << (std::ostream & out, const quote_t & q)
{
  out << "\"" << q.str_ << "\"";
  return out;
}

//
// OASIS_PDL_Probe_Csharp_Schema_Generator
//
OASIS_PDL_Probe_Csharp_Schema_Generator::
OASIS_PDL_Probe_Csharp_Schema_Generator (std::ostream & csfile)
: csfile_ (csfile),
  inner_probe_ (false),
  in_complex_ (false)
{

}

//
// ~OASIS_PDL_Probe_Csharp_Schema_Generator
//
OASIS_PDL_Probe_Csharp_Schema_Generator::
~OASIS_PDL_Probe_Csharp_Schema_Generator (void)
{

}

//
// visit_probe
//
void OASIS_PDL_Probe_Csharp_Schema_Generator::
visit_probe (const OASIS_PDL_Probe & probe)
{
  OASIS_PDL_Schema_Type_Generator type_gen (this->csfile_);
  typedef std::set <const OASIS_PDL_Complex_Type *> complex_type_set_t;
  complex_type_set_t types;

  if (!this->inner_probe_)
  {
    // Start the schema specification.
    this->csfile_
      << quote ("<?xml version='1.0' encoding='UTF-8' ?>") <<"+"<< std::endl
      << quote ("<xsd:schema xmlns:xsd='http://www.w3.org/2001/XMLSchema'") << "+"<<std::endl
      << quote (" xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance'") << "+"<<std::endl
      << quote (" xsi:schemaLocation='http://www.w3.org/2001/XMLSchema XMLSchema.xsd'") << "+"<< std::endl
      << quote (" elementFormDefault='qualified'") << "+"<<std::endl
      << quote (" version='1.0'>") << "+"<<std::endl;

    this->csfile_ << "\"<xsd:element name='probeMetadata' type='";
    probe.accept (type_gen);
    this->csfile_ << "' />\"" << "+"<<std::endl;

    // Gather all the complex types defined by this probe.
    Gather_Types gather (types);
    probe.accept (gather);
  }

  // Begin the probe's XSD definition.
  this->complex_type_begin (probe);

  if (probe.has_base_probe ())
  {
    this->csfile_
      << quote ("<xsd:complexContent>") << "+"<<std::endl
      << "\"<xsd:extension base='";

    probe.base_probe ()->accept (type_gen);

    this->csfile_
      << "'>\"" << "+"<<std::endl;
  }

  this->visit_complex_type (probe);

  if (probe.has_base_probe ())
  {
    this->csfile_
      << quote ("</xsd:extension>") <<"+"<< std::endl
      << quote ("</xsd:complexContent>") << "+"<<std::endl;
  }

  // End the probe's XSD definition.
  this->complex_type_end ();

  // Now, we are going to write all the other complex types that this
  // probe uses. This will allow the schema definition to be self-containing.
  if (!this->inner_probe_)
  {
    this->inner_probe_ = true;

    std::for_each (types.begin (),
                   types.end (),
                   boost::bind (&OASIS_PDL_Complex_Type::accept,
                                _1,
                                boost::ref (*this)));

    this->inner_probe_ = false;
  }

  if (!this->inner_probe_)
    this->csfile_ << quote ("</xsd:schema>") << ";";
}

//
// visit_struct
//
void OASIS_PDL_Probe_Csharp_Schema_Generator::
visit_struct (const OASIS_PDL_Struct & s)
{
  this->complex_type_begin (s);
  this->visit_complex_type (s);
  this->complex_type_end ();
}

//
// visit_complex_type_member
//
void OASIS_PDL_Probe_Csharp_Schema_Generator::
visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m)
{
  // Write the type information for the member.
  this->csfile_
    << "\"<xsd:element name='" << m.name () << "' type='";

  OASIS_PDL_Schema_Type_Generator type_gen (this->csfile_);

  if (m.type ())
    m.type ()->accept (type_gen);

  this->csfile_
    << "' ";

  // Generate an extra information for this type.
  this->in_complex_ = true;
  if (m.type ())
    m.type ()->accept (*this);
  this->in_complex_ = false;

  this->csfile_
    << " />\"" << "+"<<std::endl;
}

//
// visit_complex_type
//
void OASIS_PDL_Probe_Csharp_Schema_Generator::
visit_complex_type (const OASIS_PDL_Complex_Type & t)
{
  if (!this->in_complex_)
  {
    // Start the structure's definition.
    this->csfile_
        << "\"<xsd:sequence>\"" << "+"<<std::endl;

    std::for_each (t.members ().begin (),
                   t.members ().end (),
                   boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                                _1,
                                boost::ref (*this)));

    // Close the structure's definition.
    this->csfile_
      << "\"</xsd:sequence>\"" << "+"<<std::endl;
  }
}

//
// complex_type_begin
//
void OASIS_PDL_Probe_Csharp_Schema_Generator::
complex_type_begin (const OASIS_PDL_Complex_Type & t)
{
  if (!this->in_complex_)
  {
    // Start the structure's definition.
    this->csfile_
      << "\"<xsd:complexType name='";

    OASIS_PDL_Schema_Type_Generator type_gen (this->csfile_);
    t.accept (type_gen);

    this->csfile_
      << "'>\"" << "+"<<std::endl;
  }
}

//
// complex_type_end
//
void OASIS_PDL_Probe_Csharp_Schema_Generator::complex_type_end (void)
{
  if (!this->in_complex_)
    this->csfile_
      << "\"</xsd:complexType>\"" << "+"<<std::endl;
}
