// $Id

#ifndef _OASIS_CONFIGURATION_PARSER_GRAMMAR_H_
#define _OASIS_CONFIGURATION_PARSER_GRAMMAR_H_

#include "boost/config/warning_disable.hpp"
#include "boost/spirit/include/qi.hpp"
#include "ace/Basic_Types.h"

#include "Configuration_Member.h"
#include "Configuration_Value.h"
#include "Configuration_Instance.h"
#include "Configuration_Group.h"

namespace OASIS
{
  /**
   * @class Configuration_Parser_Grammar
   *
   * Grammar for parsing static probe configuration data
   */
  template <typename IteratorT>
  class Configuration_Parser_Grammar :
    public boost::spirit::qi::grammar <IteratorT, void (Configuration_Group *)>
  {
  public:
    /// Type definition of the grammar's iterator type.
    typedef IteratorT iterator_type;

    /// Default constructor.
    Configuration_Parser_Grammar (void);

  private:

    /// Definition of the main rule.
    boost::spirit::qi::rule <IteratorT, void (Configuration_Group *)> spec_;

    /// Definition for parsing a config
    boost::spirit::qi::rule <IteratorT, void (Configuration_Group *),
                             boost::spirit::qi::locals <Configuration_Member *> > config_;

    /// Definition for parsing a collection of names.
    /// Sets Configuration_Member * * to the last Configuration_Member found
    boost::spirit::qi::rule <IteratorT, Configuration_Instance * (Configuration_Group *, Configuration_Member **)> propname_;

    /// Definition for parsing a config's property value
    boost::spirit::qi::rule <IteratorT, Configuration_Value * ()> propvalue_;

    /// Definition for parsing a property name's identifiers
    boost::spirit::qi::rule <IteratorT, std::string ()> ident_;

    /// Definition for parsing a string up to a newline character
    boost::spirit::qi::rule <IteratorT, std::string ()> no_newline_;
  };

}

#include "Configuration_Parser_Grammar.cpp"

#endif // !defined _OASIS_CONFIGURATION_PARSER_GRAMMAR_H_

