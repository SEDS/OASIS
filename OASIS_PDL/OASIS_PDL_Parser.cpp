// $Id: OASIS_PDL_Parser.cpp 1922 2011-09-19 18:49:38Z hillj $

#include "OASIS_PDL_Parser.h"
#include "boost/spirit/include/qi.hpp"
#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/include/support_istream_iterator.hpp"
#include "boost/spirit/include/phoenix_bind.hpp"
#include "boost/spirit/include/phoenix_core.hpp"
#include "boost/spirit/include/phoenix_operator.hpp"
#include "boost/spirit/include/phoenix_fusion.hpp"
#include "boost/spirit/include/phoenix_stl.hpp"
#include "boost/spirit/include/phoenix_object.hpp"

#include "fe/PDL_Module.h"
#include "fe/PDL_File.h"
#include "fe/PDL_Struct.h"
#include "fe/PDL_Probe.h"
#include "fe/PDL_Simple_Type.h"
#include "fe/PDL_Vector_Type.h"

#include "OASIS_PDL_Symbol_Table.h"

#include <fstream>
#include <iostream>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

namespace data
{
  /**
   * @class struct_member
   *
   * Data for a structure member.
   */
  struct member
  {
    OASIS_PDL_Type * type_decl_;
    std::string name_;
  };

  struct version
  {
    /// The major version number.
    int version_major_;

    /// The minor version number.
    int version_minor_;
  };
}

BOOST_FUSION_ADAPT_STRUCT (
  data::member,
  (OASIS_PDL_Type *, type_decl_)
  (std::string, name_)
);

BOOST_FUSION_ADAPT_STRUCT (
  data::version,
  (int, version_major_)
  (int, version_minor_)
);

namespace actor
{
  /**
   * @struct allocate
   *
   * Functor/actor for allocating a new object. It is assumed that the
   * element's name triggers its creation.
   */
  template <typename T>
  struct allocate
  {
    template <typename Context>
    void operator () (qi::unused_type, Context & ctx, qi::unused_type) const
    {
      // Store node as the return value (i.e., qi::_val).
      namespace fusion = ::boost::fusion;
      fusion::at_c <0> (ctx.attributes) = new T ();
    }
  };

  /**
   * @struct allocate
   *
   * Functor/actor for allocating a new object. It is assumed that the
   * element's name triggers its creation.
   */
  template <typename T>
  struct allocate_symbol
  {
    template <typename Context>
    void operator () (const std::string & name, Context & ctx, qi::unused_type) const
    {
      // Allocate a new T element and set it's name.
      T * t = 0;
      OASIS_PDL_GLOBAL_SYMBOL_TABLE::instance ()->new_symbol (name.c_str (), t);

      // Store node as the return value (i.e., qi::_val).
      namespace fusion = ::boost::fusion;
      fusion::at_c <0> (ctx.attributes) = t;

      t->parent (fusion::at_c <1> (ctx.attributes));
    }
  };

  /**
   * @struct allocate_decl
   *
   * Functor/actor for allocating a new object. It is assumed that the
   * element's name triggers its creation.
   */
  template <typename T>
  struct allocate_decl
  {
    template <typename Context>
    void operator () (const std::string & name, Context & ctx, qi::unused_type) const
    {
      namespace fusion = ::boost::fusion;

      // Allocate a new T element and set it's name.
      T * t = new T ();
      fusion::at_c <0> (ctx.attributes) = t;

      // Set the symbols name.
      t->name (name);
      t->parent (fusion::at_c <1> (ctx.attributes));
    }
  };

  /**
   * @struct add_member
   */
  struct add_member
  {
    template <typename Context>
    void operator () (const data::member & member, Context & ctx, qi::unused_type) const
    {
      // Locate the return value for this rule.
      namespace fusion = ::boost::fusion;
      OASIS_PDL_Complex_Type * t = fusion::at_c <0> (ctx.attributes);

      // Create a new complex type member.
      OASIS_PDL_Complex_Type_Member * decl = t->new_member ();
      decl->name (member.name_);
      decl->type (member.type_decl_);
    }
  };

  /**
   * @struct lookup_symbol
   */
  template <typename T>
  struct lookup_symbol
  {
    template <typename Context>
    void operator () (const std::string & name, Context & ctx, qi::unused_type) const
    {
      OASIS_PDL_Type * symbol = 0;
      OASIS_PDL_GLOBAL_SYMBOL_TABLE::instance ()->find (name.c_str (), symbol);

      T * t = dynamic_cast <T *> (symbol);

      // Set the rule's return value.
      namespace fusion = ::boost::fusion;
      fusion::at_c <0> (ctx.attributes) = t;
    }
  };

  /**
   * @struct lookup_symbol
   */
  template < >
  struct lookup_symbol <OASIS_PDL_Simple_Type>
  {
    template <typename Context>
    void operator () (const std::string & name, Context & ctx, qi::unused_type) const
    {
      OASIS_PDL_Type * symbol = 0;
      OASIS_PDL_GLOBAL_SYMBOL_TABLE::instance ()->find_builtin (name.c_str (), symbol);

      OASIS_PDL_Simple_Type * t = dynamic_cast <OASIS_PDL_Simple_Type *> (symbol);

      // Set the rule's return value.
      namespace fusion = ::boost::fusion;
      fusion::at_c <0> (ctx.attributes) = t;
    }
  };

  /**
   * @struct set_base_probe
   */
  struct set_base_probe
  {
    template <typename Context>
    void operator () (std::string const & name, Context & ctx, qi::unused_type) const
    {
      namespace fusion = ::boost::fusion;

      // Locate the base probe.
      OASIS_PDL_Type * symbol = 0;
      OASIS_PDL_GLOBAL_SYMBOL_TABLE::instance ()->find (name.c_str (), symbol);

      OASIS_PDL_Probe * base = dynamic_cast <OASIS_PDL_Probe *> (symbol);

      // Set the base probe for this probe.
      OASIS_PDL_Probe * p = fusion::at_c <0> (ctx.attributes);
      p->base_probe (base);
    }
  };

  /**
   * @struct set_file_version
   */
  struct set_file_version
  {
    template <typename Context>
    void operator () (const data::version & v, Context & ctx, qi::unused_type) const
    {
      namespace fusion = ::boost::fusion;

      // Set the UUID for the probe attribute.
      OASIS_PDL_File * file = fusion::at_c <1> (ctx.attributes);
      file->attr ().version_major_ = v.version_major_;
      file->attr ().version_minor_ = v.version_minor_;
    }
  };

  /**
   * @struct set_probe_version
   */
  struct set_probe_version
  {
    template <typename Context>
    void operator () (const data::version & v, Context & ctx, qi::unused_type) const
    {
      namespace fusion = ::boost::fusion;

      // Set the UUID for the probe attribute.
      OASIS_PDL_Probe_Attr * a = fusion::at_c <1> (ctx.attributes);
      a->version_major_ = v.version_major_;
      a->version_minor_ = v.version_minor_;
    }
  };

  /**
   * @struct set_probe_abstract
   */
  struct set_probe_abstract
  {
    template <typename Context>
    void operator () (qi::unused_type, Context & ctx, qi::unused_type) const
    {
      namespace fusion = ::boost::fusion;

      ACE_DEBUG ((LM_DEBUG, "setting the probe to abstract\n"));

      // Set the UUID for the probe attribute.
      OASIS_PDL_Probe_Attr * a = fusion::at_c <2> (ctx.attributes);
      a->is_abstract_ = true;
    }
  };

  /**
   * @struct set_probe_uuid
   */
  struct set_probe_uuid
  {
    template <typename Context>
    void operator () (const std::string & uuid, Context & ctx, qi::unused_type) const
    {
      namespace fusion = ::boost::fusion;

      // Set the UUID for the probe attribute.
      OASIS_PDL_Probe_Attr * a = fusion::at_c <1> (ctx.attributes);
      a->uuid_.from_string (uuid.c_str ());
    }
  };
}

/**
 * @class OASIS_PDL_Parser_Grammar
 *
 * Underlying grammer for the .pdl parser object.
 */
template <typename IteratorT>
struct OASIS_PDL_Parser_Grammar :
  public qi::grammar <IteratorT,
                      void (OASIS_PDL_File *),
                      qi::locals < OASIS_PDL_Probe_Attr * >,
                      ascii::space_type>
{
  OASIS_PDL_Parser_Grammar (void)
    : OASIS_PDL_Parser_Grammar::base_type (file_rule_),
      file_rule_ (std::string ("file")),
      module_ (std::string ("module")),
      struct_ (std::string ("struct")),
      probe_decl_ (std::string ("probe_decl")),
      vector_decl_ (std::string ("vector_decl")),
      simple_type_name_ (std::string ("simple_type_name")),
      named_decl_ (std::string ("named_decl")),
      type_decl_ (std::string ("type_decl")),
      struct_member_ (std::string ("struct_member")),
      probe_defn_ (std::string ("probe_defn")),
      probe_attr_ (std::string ("probe_attr")),
      ident_ (std::string ("ident")),
      scoped_name_ (std::string ("scoped_name")),
      vector_type_decl_ (std::string ("vector_type_decl"))
  {
    namespace qi = boost::spirit::qi;
    namespace phoenix = boost::phoenix;
    namespace ascii = boost::spirit::ascii;

    this->file_rule_ =
      * (this->pragma_ (qi::_r1) | this->include_stmt_ | this->comment_) >>
      + (this->decl_ (qi::_r1)[phoenix::bind (&OASIS_PDL_File::add_decl, qi::_r1, qi::_1)] | this->comment_);

    this->pragma_ =
      qi::lit ("#pragma") > this->pragma_type_ (qi::_r1);

    this->pragma_type_ =
      this->version_[actor::set_file_version ()];

    // Definition of the module.
    this->module_ =
      qi::lit ("module") >
      this->ident_[actor::allocate_decl <OASIS_PDL_Module> ()]
                  [phoenix::bind (&OASIS_PDL_Symbol_Table::push_scope, OASIS_PDL_GLOBAL_SYMBOL_TABLE::instance (), qi::_1)] >
      qi::lit ("{") >>
      * (this->decl_ (qi::_val)[phoenix::bind (&OASIS_PDL_Module::add_decl, qi::_val, qi::_1)] | this->comment_) >
      qi::lit ("}")[phoenix::bind (&OASIS_PDL_Symbol_Table::pop_scope, OASIS_PDL_GLOBAL_SYMBOL_TABLE::instance ())];

    // Definition of the struct.
    this->struct_ =
      qi::lit ("struct") > this->ident_[actor::allocate_symbol <OASIS_PDL_Struct> ()] >
      qi::lit ("{") >>
      + this->struct_member_[actor::add_member ()] >>
      qi::lit ("}") > qi::lit (";");

    this->struct_member_ %=
      this->type_decl_ > this->ident_ > ";";

    // Definition of the probe.
    this->probe_decl_ =
      this->probe_attr_[qi::_a = qi::_1] >>
      this->probe_defn_ (qi::_r1, qi::_a)[qi::_val = qi::_1];

    this->probe_attr_ =
      qi::lit ('[')[actor::allocate <OASIS_PDL_Probe_Attr> ()] >>
      this->probe_attr_defn_ (qi::_val) >>
      * (qi::lit (";") >> this->probe_attr_defn_ (qi::_val)) >>
      qi::lit (']');

    this->probe_attr_defn_ =
      this->version_[actor::set_probe_version ()] |
      this->probe_attr_uuid_[actor::set_probe_uuid ()];

    this->version_ %=
      qi::lit ("version") >
      qi::lit ("(") > qi::int_ >
      qi::lit (".") > qi::int_ > qi::lit (")");

    this->probe_attr_uuid_ %=
      qi::lit ("uuid") > qi::lit ("(") >> *(qi::char_ - ')') > qi::lit (")");

    this->probe_defn_ =
      - (qi::lit ("abstract") [actor::set_probe_abstract ()]) >>
      qi::lit ("probe") >>
      this->ident_[actor::allocate_symbol <OASIS_PDL_Probe> ()][phoenix::bind (&OASIS_PDL_Probe::attr, qi::_val, qi::_r2)] >>
      - (qi::lit (":") >> this->scoped_name_[actor::set_base_probe ()]) >
      qi::lit ("{") >
      * this->struct_member_[actor::add_member ()] >
      qi::lit ("}") > qi::lit (";");

    // Definition of a declaration.
    this->decl_ %=
      this->module_ (qi::_r1) |
      this->struct_ (qi::_r1) |
      this->probe_decl_ (qi::_r1);

    this->type_decl_ %=
      this->simple_decl_ |
      this->vector_decl_ |
      this->named_decl_;

    // Definition of the simple type.
    this->simple_decl_ =
      this->simple_type_name_[actor::lookup_symbol <OASIS_PDL_Simple_Type> ()];

    // Definition of the named type.
    this->named_decl_ =
      this->scoped_name_[actor::lookup_symbol <OASIS_PDL_Type> ()];

    this->vector_decl_ =
      qi::lit ("vector")[qi::_val = new OASIS_PDL_Vector_Type ()] >>
      qi::lit ('<') >
      this->vector_type_decl_[phoenix::bind (&OASIS_PDL_Vector_Type::type, qi::_val, qi::_1)] >
      qi::lit ('>');

    this->vector_type_decl_ %=
      this->simple_decl_ |
      this->named_decl_;

    this->scoped_name_ =
      (- ascii::string ("::")[qi::_val += qi::_1] >>
      this->ident_[qi::_val += qi::_1] >>
      *(ascii::string ("::")[qi::_val += qi::_1] >> this->ident_[qi::_val += qi::_1]));

    // Definition of the simple type name.
    this->simple_type_name_ =
      ascii::string ("int8") | ascii::string ("int16") | ascii::string ("int32") | ascii::string ("int64") |
      ascii::string ("uint8") | ascii::string ("uint16") | ascii::string ("uint32") | ascii::string ("uint64") |
      ascii::string ("real32") | ascii::string ("real64") |
      ascii::string ("string") | ascii::string ("boolean");

    // Definition of the identifier.
    this->ident_ %=
      qi::lexeme [(qi::alpha >> *(qi::alnum | qi::char_ ('_')))];

    this->comment_ %=
      this->c_comment_ |
      this->cpp_comment_;

    this->c_comment_ %=
      qi::lexeme[qi::lit("/*") > *(ascii::char_ - "*/") > qi::lit ("*/")];

    this->cpp_comment_ %=
      qi::lexeme[qi::lit ("//") > *(ascii::char_ - qi::eol) > qi::omit[qi::eol]];

    this->include_stmt_ %=
      qi::lit ("#include") > this->quoted_string_;

    this->quoted_string_ %=
      qi::lit ('"') >> *(qi::print - '"') >> qi::lit ('"');

    using phoenix::construct;
    using phoenix::val;

    // Definition of the error handler.
    qi::on_error <qi::fail>
    (
      file_rule_,
      std::cerr << phoenix::val ("*** syntax error: expecting ")
                << qi::labels::_4
                << phoenix::val(" here; \"")
                << construct <std::string> (qi::labels::_3, qi::labels::_2)
                << phoenix::val("\"")
                << std::endl
    );
  }

private:
  template <typename T>
  struct node_rule
  {
    typedef
      ::boost::spirit::qi::rule <IteratorT,
                                 T * (),
                                 ascii::space_type> type;
  };

  template <typename T>
  struct creation_rule
  {
    typedef
      ::boost::spirit::qi::rule <IteratorT,
                                 T * (OASIS_PDL_Declaration *),
                                 ascii::space_type> type;
  };

  qi::rule <IteratorT,
            void (OASIS_PDL_File *),
            qi::locals < OASIS_PDL_Probe_Attr * >,
            ascii::space_type> file_rule_;

  typename creation_rule <OASIS_PDL_Module>::type module_;

  typename creation_rule <OASIS_PDL_Declaration>::type decl_;

  typename creation_rule <OASIS_PDL_Struct>::type struct_;

  qi::rule <IteratorT,
            data::member (),
            ascii::space_type> struct_member_;

  ::boost::spirit::qi::rule <IteratorT,
                             OASIS_PDL_Probe * (OASIS_PDL_Declaration *),
                             qi::locals < OASIS_PDL_Probe_Attr * >,
                             ascii::space_type> probe_decl_;

  typename node_rule <OASIS_PDL_Probe_Attr>::type probe_attr_;

  qi::rule <IteratorT,
            void (OASIS_PDL_File *),
            ascii::space_type> pragma_;

  qi::rule <IteratorT,
            void (OASIS_PDL_File *),
            ascii::space_type> pragma_type_;

  qi::rule <IteratorT,
            void (OASIS_PDL_File *),
            ascii::space_type> pragma_file_version_;

  qi::rule <IteratorT,
            void (OASIS_PDL_Probe_Attr *),
            ascii::space_type> probe_attr_defn_;

  qi::rule <IteratorT,
            data::version (),
            ascii::space_type> version_;

  qi::rule <IteratorT,
            std::string (),
            ascii::space_type> probe_attr_uuid_;

  /// Rule for the probe's definition.
  qi::rule <IteratorT,
            OASIS_PDL_Probe * (OASIS_PDL_Declaration *, OASIS_PDL_Probe_Attr *),
            ascii::space_type> probe_defn_;

  typename node_rule <OASIS_PDL_Type>::type type_decl_;

  typename node_rule <OASIS_PDL_Type>::type named_decl_;

  typename node_rule <OASIS_PDL_Simple_Type>::type simple_decl_;

  typename node_rule <OASIS_PDL_Vector_Type>::type vector_decl_;

  typename node_rule <OASIS_PDL_Type>::type vector_type_decl_;

  qi::rule <IteratorT,
            std::string (),
            ascii::space_type> simple_type_name_;

  qi::rule <IteratorT,
            std::string (),
            ascii::space_type> ident_;

  qi::rule <IteratorT,
            std::string (),
            ascii::space_type> scoped_name_;

  qi::rule <IteratorT,
            std::string (),
            ascii::space_type> comment_;

  qi::rule <IteratorT,
            std::string (),
            ascii::space_type> c_comment_;

  qi::rule <IteratorT,
            std::string (),
            ascii::space_type> cpp_comment_;

  qi::rule <IteratorT,
            std::string (),
            ascii::space_type> include_stmt_;

  qi::rule <IteratorT,
            std::string (),
            ascii::space_type> quoted_string_;
};

///////////////////////////////////////////////////////////////////////////////
// class OASIS_PDL_Parser

//
// OASIS_PDL_Parser
//
OASIS_PDL_Parser::OASIS_PDL_Parser (void)
{

}

//
// OASIS_PDL_Parser
//
OASIS_PDL_Parser::~OASIS_PDL_Parser (void)
{

}

//
// parse_file
//
bool OASIS_PDL_Parser::
parse_file (std::istream & input, OASIS_PDL_File & file)
{
  namespace spirit = boost::spirit;

  // Adapt the iterator to support Boost backtracking.
  long flags = input.flags ();

  if ((flags & std::ios::skipws) != 0)
    input.unsetf (std::ios::skipws);

  spirit::istream_iterator begin_iter (input);
  spirit::istream_iterator end_iter;

  OASIS_PDL_Parser_Grammar <spirit::istream_iterator> g;

  bool retval = qi::phrase_parse (begin_iter,
                                  end_iter,
                                  g (&file),
                                  ascii::space);

  if ((flags & std::ios::skipws) != 0)
    input.setf (std::ios::skipws);

  return retval;
}

