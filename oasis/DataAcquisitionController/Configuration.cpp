// $Id: Configuration.cpp 2098 2012-01-08 18:58:32Z dfeiock $

#include "Configuration.h"

#include "boost/config/warning_disable.hpp"
#include "boost/spirit/include/qi.hpp"
#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/spirit/include/phoenix_bind.hpp"
#include "boost/spirit/include/phoenix_core.hpp"
#include "boost/spirit/include/phoenix_operator.hpp"
#include "boost/spirit/include/phoenix_fusion.hpp"
#include "boost/spirit/include/phoenix_stl.hpp"
#include "boost/spirit/include/phoenix_object.hpp"
#include "ace/Log_Msg.h"

#include <fstream>

BOOST_FUSION_ADAPT_STRUCT (OASIS::DAC_Service_Configuration::Directive,
                           (std::string, name_)
                           (std::string, module_)
                           (std::string, symbol_)
                           (std::string, params_));

namespace OASIS
{

/**
 * @class DAC_Configuration_Grammar
 *
 * The grammar for parsing the DAC's configuration file.
 */
template <typename IteratorT, typename SpaceT>
class DAC_Configuration_Grammar :
  public boost::spirit::qi::grammar <IteratorT, void (DAC_Service_Configuration &), SpaceT>
{
public:
  /// Type definition of the grammar's iterator type.
  typedef IteratorT iterator_type;

  /// Type definition of the grammar's space type.
  typedef SpaceT space_type;

  /// Default constructor.
  DAC_Configuration_Grammar (void)
    : DAC_Configuration_Grammar::base_type (config_),
      config_ (std::string ("config")),
      section_ (std::string ("section")),
      channels_ (std::string ("channels")),
      handlers_ (std::string ("handlers")),
      directive_ (std::string ("directive")),
      identifier_ (std::string ("identifier")),
      params_ (std::string ("params"))
  {
    namespace qi = boost::spirit::qi;
    namespace phoenix = boost::phoenix;

    this->config_ = + this->section_ (qi::_r1);

    this->section_ =
      qi::lit ("section") >>
        (this->handlers_[phoenix::bind (&DAC_Service_Configuration::insert_handlers, qi::_r1, qi::_1)] |
         this->channels_[phoenix::bind (&DAC_Service_Configuration::insert_channels, qi::_r1, qi::_1)]);

    this->handlers_ %=
      qi::lit ("DataHandlers:") >> *this->dac_directive_;

    this->channels_ %=
      qi::lit ("DataChannels:") >> *this->directive_;

    this->directive_ %=
      qi::raw[
        qi::lit ("dynamic") >>
        this->identifier_ >>                                          // name
        qi::lit ("Service_Object") >> qi::char_ ('*') >>              // Service_Object *
        this->identifier_ >> qi::char_ (':') >>                       // library
        this->identifier_ >> qi::char_ ('(') >> qi::char_ (')') >>    // symbol
        this->params_];                                               // parameters

    this->dac_directive_ %=
      qi::lit ("dynamic") >>
      this->identifier_ >>
      qi::lit ("Service_Object") >> qi::lit ('*') >>
      this->identifier_ >> qi::lit (':') >>
      this->identifier_ >> qi::lit ('(') >> qi::lit (')') >>
      this->dac_params_;

    this->identifier_ %=
      qi::lexeme[(qi::char_ ('_') | qi::alpha) >> *(qi::alnum | qi::char_ ('_'))];

    this->params_ %=
      qi::char_ ('"') >> *(qi::char_ - '"') >> qi::char_ ('"');

    this->dac_params_ %=
      qi::lexeme[qi::lit ('"') >> *(qi::char_ - '"') >> qi::lit ('"')];

    qi::on_error <qi::fail>
      (config_,
       std::cerr
                << phoenix::val ("Error! Expecting ")
                << qi::_4                               // what failed?
                << phoenix::val (" here: \"")
                << phoenix::construct <std::string> (qi::_3, qi::_2)   // iterators to error-pos, end
                << phoenix::val ("\"")
                << std::endl
        );
  }

private:
  boost::spirit::qi::rule <IteratorT, void (DAC_Service_Configuration &), SpaceT> config_;

  boost::spirit::qi::rule <IteratorT, void (DAC_Service_Configuration &), SpaceT> section_;

  boost::spirit::qi::rule <IteratorT, DAC_Service_Configuration::Data_Handler_List (), SpaceT> handlers_;

  boost::spirit::qi::rule <IteratorT, DAC_Service_Configuration::Service_List (), SpaceT> channels_;

  boost::spirit::qi::rule <IteratorT,
                           DAC_Service_Configuration::Directive (),
                           SpaceT> dac_directive_;

  boost::spirit::qi::rule <IteratorT, std::string (), SpaceT> directive_;

  boost::spirit::qi::rule <IteratorT, std::string (), SpaceT> identifier_;

  boost::spirit::qi::rule <IteratorT, std::string (), SpaceT> params_;

  boost::spirit::qi::rule <IteratorT, std::string (), SpaceT> dac_params_;
};

//
// DAC_Service_Configuration
//
DAC_Service_Configuration::DAC_Service_Configuration (void)
{

}

//
// DAC_Service_Configuration
//
DAC_Service_Configuration::~DAC_Service_Configuration (void)
{

}

//
// load_file
//
bool DAC_Service_Configuration::load_file (const char * filename)
{
  namespace spirit = boost::spirit;
  namespace qi = boost::spirit::qi;
  namespace phoenix = boost::phoenix;

  // Open the file for reading.
  std::ifstream file;
  file.open (filename);

  if (!file.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                       filename),
                       false);

  long flags = file.flags ();
  if ((flags & std::ios::skipws) != 0)
    file.unsetf (std::ios::skipws);

  // Initialize the stream iterators for the file.
  spirit::istream_iterator begin (file);
  spirit::istream_iterator end;

  // Parse the contents for the file.
  DAC_Configuration_Grammar <spirit::istream_iterator,
                             spirit::ascii::space_type>
                             grammar;

  bool retval =
    qi::phrase_parse (begin,
                      end,
                      grammar (phoenix::ref (*this)),
                      spirit::ascii::space);

  if ((flags & std::ios::skipws) != 0)
    file.setf (std::ios::skipws);

  return retval;
}

//
// handlers
//
const DAC_Service_Configuration::Data_Handler_List &
DAC_Service_Configuration::handlers (void) const
{
  return this->handlers_;
}

//
// insert_handlers
//
void DAC_Service_Configuration::insert_handlers (const Data_Handler_List & list)
{
  this->handlers_.insert (this->handlers_.end (),
                          list.begin (),
                          list.end ());
}

//
// channels
//
const DAC_Service_Configuration::Service_List &
DAC_Service_Configuration::channels (void) const
{
  return this->channels_;
}

//
// insert_channels
//
void DAC_Service_Configuration::insert_channels (const Service_List & list)
{
  this->channels_.insert (this->channels_.end (),
                          list.begin (),
                          list.end ());
}

}
