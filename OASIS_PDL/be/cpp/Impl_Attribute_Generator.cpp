// $Id: Impl_Attribute_Generator.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "Impl_Attribute_Generator.h"
#include "Cpp.h"
#include "Impl_Var_Type_Generator.h"

#include "fe/PDL_Probe.h"
#include "fe/PDL_Simple_Type.h"
#include "fe/PDL_Struct.h"
#include "fe/PDL_Vector_Type.h"

#include "boost/bind.hpp"
#include <algorithm>
#include <iostream>

namespace OASIS_PDL_BE
{
namespace Cpp
{

/**
 * @struct impl_return_t
 */
struct impl_return_t
{
  impl_return_t (const OASIS_PDL_Type * type)
    : type_ (type)
  {

  }

  /// Pointer to the contained type.
  const OASIS_PDL_Type * type_;
};

/**
 * @class Impl_Return_Type_Generator
 *
 * Implementation of the visitor that generates the return type.
 */
class Impl_Return_Type_Generator : public OASIS_PDL_Visitor
{
public:
  Impl_Return_Type_Generator (std::ostream & out)
    : out_ (out)
  {

  }

  virtual void visit_struct (const OASIS_PDL_Struct & s)
  {
    this->out_ << "::" << s.fq_name ("::") << "Impl &";
  }

  virtual void visit_vector_type (const OASIS_PDL_Vector_Type & v)
  {
    this->out_ << "std::vector < ";

    Impl_Var_Type_Generator var_type (this->out_);
    v.type ()->accept (var_type);

    this->out_ << " > &";
  }

  virtual void visit_simple_type (const OASIS_PDL_Simple_Type & s)
  {
    switch (s.kind ())
    {
    case OASIS_PDL_Simple_Type::tk_boolean:
      this->out_ << "bool";
      break;

    case OASIS_PDL_Simple_Type::tk_string:
      this->out_ << "const ACE_CString &";
      break;

    case OASIS_PDL_Simple_Type::tk_int8:
      this->out_ << "ACE_INT8";
      break;

    case OASIS_PDL_Simple_Type::tk_int16:
      this->out_ << "ACE_INT16";
      break;

    case OASIS_PDL_Simple_Type::tk_int32:
      this->out_ << "ACE_INT32";
      break;

    case OASIS_PDL_Simple_Type::tk_int64:
      this->out_ << "ACE_INT64";
      break;

    case OASIS_PDL_Simple_Type::tk_uint8:
      this->out_ << "ACE_UINT8";
      break;

    case OASIS_PDL_Simple_Type::tk_uint16:
      this->out_ << "ACE_UINT16";
      break;

    case OASIS_PDL_Simple_Type::tk_uint32:
      this->out_ << "ACE_UINT32";
      break;

    case OASIS_PDL_Simple_Type::tk_uint64:
      this->out_ << "ACE_UINT64";
      break;

    case OASIS_PDL_Simple_Type::tk_real32:
      this->out_ << "double";
      break;

    case OASIS_PDL_Simple_Type::tk_real64:
      this->out_ << "long double";
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
std::ostream & operator << (std::ostream & out, const impl_return_t & r)
{
  Impl_Return_Type_Generator rtg (out);

  if (r.type_)
    r.type_->accept (rtg);

  return out;
};

/**
 * @struct impl_in_t
 */
struct impl_in_t
{
  impl_in_t (const OASIS_PDL_Type * type)
    : type_ (type)
  {

  }

  /// Pointer to the contained type.
  const OASIS_PDL_Type * type_;
};

/**
 * @class Impl_In_Type_Generator
 *
 * Implementation of the visitor that generates the return type.
 */
class Impl_In_Type_Generator : public OASIS_PDL_Visitor
{
public:
  Impl_In_Type_Generator (std::ostream & out)
    : out_ (out)
  {

  }

  virtual void visit_struct (const OASIS_PDL_Struct & s)
  {
    this->out_ << "const ::" << s.fq_name ("::") << "Impl &";
  }

  virtual void visit_vector_type (const OASIS_PDL_Vector_Type & v)
  {
    this->out_ << "const std::vector < ";

    Impl_Var_Type_Generator var_type (this->out_);
    v.type ()->accept (var_type);

    this->out_ << " > &";
  }

  virtual void visit_simple_type (const OASIS_PDL_Simple_Type & s)
  {
    switch (s.kind ())
    {
    case OASIS_PDL_Simple_Type::tk_boolean:
      this->out_ << "bool";
      break;

    case OASIS_PDL_Simple_Type::tk_string:
      this->out_ << "const ACE_CString &";
      break;

    case OASIS_PDL_Simple_Type::tk_int8:
      this->out_ << "ACE_INT8";
      break;

    case OASIS_PDL_Simple_Type::tk_int16:
      this->out_ << "ACE_INT16";
      break;

    case OASIS_PDL_Simple_Type::tk_int32:
      this->out_ << "ACE_INT32";
      break;

    case OASIS_PDL_Simple_Type::tk_int64:
      this->out_ << "ACE_INT64";
      break;

    case OASIS_PDL_Simple_Type::tk_uint8:
      this->out_ << "ACE_UINT8";
      break;

    case OASIS_PDL_Simple_Type::tk_uint16:
      this->out_ << "ACE_UINT16";
      break;

    case OASIS_PDL_Simple_Type::tk_uint32:
      this->out_ << "ACE_UINT32";
      break;

    case OASIS_PDL_Simple_Type::tk_uint64:
      this->out_ << "ACE_UINT64";
      break;

    case OASIS_PDL_Simple_Type::tk_real32:
      this->out_ << "double";
      break;

    case OASIS_PDL_Simple_Type::tk_real64:
      this->out_ << "long double";
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
std::ostream & operator << (std::ostream & out, const impl_in_t & in)
{
  Impl_In_Type_Generator itg (out);

  if (in.type_)
    in.type_->accept (itg);

  return out;
};

//
// Impl_Attribute_Generator
//
Impl_Attribute_Generator::
Impl_Attribute_Generator (std::ostream & hfile, std::ostream & cppfile)
: hfile_ (hfile),
  cppfile_ (cppfile)
{

}

//
// ~Impl_Attribute_Generator
//
Impl_Attribute_Generator::~Impl_Attribute_Generator (void)
{

}

//
// visit_probe
//
void Impl_Attribute_Generator::visit_probe (const OASIS_PDL_Probe & p)
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
void Impl_Attribute_Generator::
visit_complex_type_member (const OASIS_PDL_Complex_Type_Member & m)
{
  this->hfile_
    << std::endl
    << "// Setter and getter methods for " << m.name () << std::endl
    << "void " << m.name () << " (" << impl_in_t (m.type ()) << " " << m.name () << ");";

  this->cppfile_
    << function_header (m.name ())
    << "void " << this->probe_->name () << "Impl::"
    << m.name () << " (" << impl_in_t (m.type ()) << " " << m.name () << ")"
    << "{"
    << "this->" << m.name () << "_ = " << m.name () << ";"
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
void Impl_Attribute_Generator::visit_simple_type (const OASIS_PDL_Simple_Type & s)
{
  // Declaration and implementation of the setter/getter methods
  // specific to simple types.
  this->hfile_
    << impl_return_t (&s) << " " << this->member_name_ << " (void) const;";

  this->cppfile_
    << function_header (this->member_name_)
    << impl_return_t (&s) << " " << this->probe_->name ()
    << "Impl::" << this->member_name_ << " (void) const"
    << "{"
    << "return this->" << this->member_name_ << "_;"
    << "}";
}

//
// visit_struct
//
void Impl_Attribute_Generator::visit_struct (const OASIS_PDL_Struct & s)
{
  // Declaration and implementation of the setter/getter methods
  // specific to structure types
  this->hfile_
    << impl_return_t (&s) << " " << this->member_name_ << " (void);"
    << "const " << impl_return_t (&s) << " " << this->member_name_ << " (void) const;";

  // Implementation of the setter/getter methods for structure types.
  this->cppfile_
    << function_header (this->member_name_)
    << "const " << impl_return_t (&s) << " " << this->probe_->name ()
    << "Impl::" << this->member_name_ << " (void) const"
    << "{"
    << "return this->" << this->member_name_ << "_;"
    << "}"
    << function_header (this->member_name_)
    << impl_return_t (&s) << " " << this->probe_->name ()
    << "Impl::" << this->member_name_ << " (void)"
    << "{"
    << "return this->" << this->member_name_ << "_;"
    << "}";
}

//
// visit_vector_type
//
void Impl_Attribute_Generator::
visit_vector_type (const OASIS_PDL_Vector_Type & v)
{
  // Declaration and implementation of the setter/getter methods
  // specific to structure types
  this->hfile_
    << impl_return_t (&v) << " " << this->member_name_ << " (void);"
    << "const " << impl_return_t (&v) << " " << this->member_name_ << " (void) const;";

  // Implementation of the setter/getter methods for structure types.
  this->cppfile_
    << function_header (this->member_name_)
    << "const " << impl_return_t (&v) << " " << this->probe_->name ()
    << "Impl::" << this->member_name_ << " (void) const"
    << "{"
    << "return this->" << this->member_name_ << "_;"
    << "}"
    << function_header (this->member_name_)
    << impl_return_t (&v) << " " << this->probe_->name ()
    << "Impl::" << this->member_name_ << " (void)"
    << "{"
    << "return this->" << this->member_name_ << "_;"
    << "}";
}

}
}
