// $Id: Attribute_Generator.cpp 2118 2012-01-13 20:29:17Z dpuranik $

#include "Attribute_Generator.h"
#include "Csharp.h"
#include "Var_Type_Generator.h"

#include "fe/PDL_Probe.h"
#include "fe/PDL_Simple_Type.h"
#include "fe/PDL_Struct.h"
#include "fe/PDL_Vector_Type.h"

#include "boost/bind.hpp"
#include <algorithm>
#include <iostream>

namespace OASIS_PDL_BE
{
namespace Csharp
{

/**
 * @struct return_t
 */
struct return_t
{
  return_t (const OASIS_PDL_Type * type)
    : type_ (type)
  {

  }

  /// Pointer to the contained type.
  const OASIS_PDL_Type * type_;
};

/**
 * @class Return_Type_Generator
 *
 * Implementation of the visitor that generates the return type.
 */
class Return_Type_Generator : public OASIS_PDL_Visitor
{
public:
  Return_Type_Generator (std::ostream & out)
    : out_ (out)
  {

  }

  virtual void visit_struct (const OASIS_PDL_Struct & s)
  {
    this->out_ << s.name();
  }

  virtual void visit_vector_type (const OASIS_PDL_Vector_Type & v)
  {
    this->out_ << "std::vector < ";

    Var_Type_Generator var_type (this->out_);
    v.type ()->accept (var_type);

    this->out_ << " > &";
  }

  virtual void visit_simple_type (const OASIS_PDL_Simple_Type & s)
  {
    switch (s.kind ())
    {
    case OASIS_PDL_Simple_Type::tk_boolean:
      this->out_ << "Boolean";
      break;

    case OASIS_PDL_Simple_Type::tk_string:
      this->out_ << "String";
      break;

    case OASIS_PDL_Simple_Type::tk_int8:
      this->out_ << "Byte";
      break;

    case OASIS_PDL_Simple_Type::tk_int16:
      this->out_ << "Int16";
      break;

    case OASIS_PDL_Simple_Type::tk_int32:
      this->out_ << "Int32";
      break;

    case OASIS_PDL_Simple_Type::tk_int64:
      this->out_ << "Int64";
      break;

    case OASIS_PDL_Simple_Type::tk_uint8:
      this->out_ << "Byte";
      break;

    case OASIS_PDL_Simple_Type::tk_uint16:
      this->out_ << "UInt16";
      break;

    case OASIS_PDL_Simple_Type::tk_uint32:
      this->out_ << "UInt32";
      break;

    case OASIS_PDL_Simple_Type::tk_uint64:
      this->out_ << "UInt64";
      break;

    case OASIS_PDL_Simple_Type::tk_real32:
      this->out_ << "float";
      break;

    case OASIS_PDL_Simple_Type::tk_real64:
      this->out_ << "Double";
      break;
    }
  }

private:
  /// Target output stream.
  std::ostream & out_;
};

//
// operator <<
//
std::ostream & operator << (std::ostream & out, const return_t & r)
{
  Return_Type_Generator rtg (out);

  if (r.type_)
    r.type_->accept (rtg);

  return out;
};

/**
 * @struct in_t
 */
struct in_t
{
  in_t (const OASIS_PDL_Type * type)
    : type_ (type)
  {

  }

  /// Pointer to the contained type.
  const OASIS_PDL_Type * type_;
};

/**
 * @class In_Type_Generator
 *
 * Implementation of the visitor that generates the return type.
 */
class In_Type_Generator : public OASIS_PDL_Visitor
{
public:
  In_Type_Generator (std::ostream & out)
    : out_ (out)
  {

  }

  virtual void visit_struct (const OASIS_PDL_Struct & s)
  {
    this->out_ << s.name();
  }

  virtual void visit_vector_type (const OASIS_PDL_Vector_Type & v)
  {
    this->out_ << "const std::vector < ";

    Var_Type_Generator var_type (this->out_);
    v.type ()->accept (var_type);

    this->out_ << " > &";
  }

  virtual void visit_simple_type (const OASIS_PDL_Simple_Type & s)
  {
    switch (s.kind ())
    {
    case OASIS_PDL_Simple_Type::tk_boolean:
      this->out_ << "Boolean";
      break;

    case OASIS_PDL_Simple_Type::tk_string:
      this->out_ << "String";
      break;

    case OASIS_PDL_Simple_Type::tk_int8:
      this->out_ << "Byte";
      break;

    case OASIS_PDL_Simple_Type::tk_int16:
      this->out_ << "Int16";
      break;

    case OASIS_PDL_Simple_Type::tk_int32:
      this->out_ << "Int32";
      break;

    case OASIS_PDL_Simple_Type::tk_int64:
      this->out_ << "Int64";
      break;

    case OASIS_PDL_Simple_Type::tk_uint8:
      this->out_ << "Byte";
      break;

    case OASIS_PDL_Simple_Type::tk_uint16:
      this->out_ << "UInt16";
      break;

    case OASIS_PDL_Simple_Type::tk_uint32:
      this->out_ << "UInt32";
      break;

    case OASIS_PDL_Simple_Type::tk_uint64:
      this->out_ << "UInt64";
      break;

    case OASIS_PDL_Simple_Type::tk_real32:
      this->out_ << "float";
      break;

    case OASIS_PDL_Simple_Type::tk_real64:
      this->out_ << "Double";
      break;
    }
  }

private:
  /// Target output stream.
  std::ostream & out_;
};

//
// operator <<
//
std::ostream & operator << (std::ostream & out, const in_t & in)
{
  In_Type_Generator itg (out);

  if (in.type_)
    in.type_->accept (itg);

  return out;
};

//
// Attribute_Generator
//
Attribute_Generator::
Attribute_Generator (std::ostream & csfile)
: csfile_ (csfile)
{

}

//
// ~Attribute_Generator
//
Attribute_Generator::~Attribute_Generator (void)
{

}

//
// visit_probe
//
void Attribute_Generator::visit_probe (const OASIS_PDL_Probe & p)
{
  this->probe_ = &p;
  std::for_each (p.members ().begin (),
                 p.members ().end (),
                 boost::bind (&OASIS_PDL_Complex_Type_Member::accept,
                              _1,
                              boost::ref (*this)));
}

//
// visit_complex_type_member
//
void Attribute_Generator::
visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m)
{
  this->csfile_
    << std::endl
    << function_header (m.name ())
    << "// Setter and getter methods for " << m.name () << std::endl
    << "public void " << m.name () << " (" << in_t (m.type ()) << " " << m.name () << ")"<< std::endl
    << "{"
    << "this." << m.name () << "_ = " << m.name () << ";"
    << "}";

  if (m.type ())
  {
    // Save the name for later.
    this->member_name_ = m.name ();

    // Visit the actual type.
    m.type ()->accept (*this);
  }
}

//
// visit_simple_type
//
void Attribute_Generator::visit_simple_type (const OASIS_PDL_Simple_Type & s)
{
  // Declaration and implementation of the setter/getter methods
  // specific to simple types.
  this->csfile_
    << function_header (this->member_name_)
    << "public "<<return_t (&s) << " " << this->member_name_ << " ()" << std::endl
    << "{"
    << "return this." << this->member_name_ << "_;"
    << "}";
}

//
// visit_struct
//
void Attribute_Generator::visit_struct (const OASIS_PDL_Struct & s)
{
  this->csfile_
    << function_header(this->member_name_)
    << "public "<<return_t(&s)<<" "<<this->member_name_ << " ()"<< std::endl
    << "{"
    << "return this." << this->member_name_ << "_;"
    << "}";
}

}
}
