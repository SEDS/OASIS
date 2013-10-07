// $Id: Configuration.cpp 2097 2012-01-08 17:52:08Z dfeiock $

#include "Configuration.h"

#if !defined (__OASIS_INLINE__)
#include "Configuration.inl"
#endif

#define BOOST_SPIRIT_DEBUG_INDENT 2

#include "boost/config/warning_disable.hpp"
#include "boost/spirit/include/qi.hpp"
#include "boost/spirit/include/phoenix_bind.hpp"
#include "boost/spirit/include/phoenix_core.hpp"
#include "boost/spirit/include/phoenix_operator.hpp"
#include "boost/spirit/include/phoenix_fusion.hpp"
#include "boost/spirit/include/phoenix_stl.hpp"
#include "boost/spirit/include/phoenix_object.hpp"
#include "boost/fusion/include/adapt_struct.hpp"

#include "ace/Log_Msg.h"

#include <fstream>

BOOST_FUSION_ADAPT_STRUCT (
  OASIS::Einode_Configuration::Software_Probe,
    (std::string, name_)
    (std::string, location_)
    (std::string, entrypoint_)
    (std::string, params_)
)

BOOST_FUSION_ADAPT_STRUCT (
  OASIS::Einode_Configuration::Data_Channel,
    (std::string, directive_)
    (OASIS::Einode_Configuration::Software_Probe_List, probes_)
)

//
// operator <<
//
std::ostream &
operator << (std::ostream & out, const OASIS::Einode_Configuration & config)
{
  return out;
}

namespace OASIS
{
  /**
   * @struct set_uuid_node_id
   */
  struct set_uuid
  {
    template <typename ContextT>
    void operator () (const std::string & val, ContextT ctx, boost::spirit::qi::unused_type) const
    {
      namespace fusion = ::boost::fusion;
      ACE_Utils::UUID & uuid = fusion::at_c <0> (ctx.attributes);

      for (size_t i = 0; i < ACE_Utils::UUID_Node::NODE_ID_SIZE; ++ i)
        uuid.node ().node_ID ()[i] = val[i];
    }
  };

/**
 * @class Einode_Configuration_Grammar
 *
 * The grammar for parsing the DAC's configuration file.
 */
template <typename IteratorT, typename SpaceT>
class Einode_Configuration_Grammar :
  public boost::spirit::qi::grammar <IteratorT, Einode_Configuration (void), SpaceT>
{
public:
  /// Type definition of the grammar's iterator type.
  typedef IteratorT iterator_type;

  /// Type definition of the grammar's space type.
  typedef SpaceT space_type;

  /// Default constructor.
  Einode_Configuration_Grammar (void)
    : Einode_Configuration_Grammar::base_type (config_),
      config_ (std::string ("config")),
      data_channel_ (std::string ("data_channel")),
      directive_ (std::string ("directive")),
      identifier_ (std::string ("identifier")),
      params_ (std::string ("params")),
      params_no_quotes_ (std::string ("params_no_quotes")),
      uuid_ (std::string ("uuid")),
      probes_ (std::string ("probes")),
      probe_ (std::string ("probe"))
  {
    namespace qi = boost::spirit::qi;
    namespace phoenix = boost::phoenix;

    this->config_ =
      qi::lit ("Name:") >> this->identifier_[phoenix::bind (&Einode_Configuration::name_, qi::_r0) = qi::_1] >>
      qi::lit ("Uuid:") >> this->uuid_ [
        phoenix::bind (&ACE_Utils::UUID::from_string,
                       phoenix::bind (&Einode_Configuration::uuid_, qi::_r0),
                       phoenix::bind (&std::string::c_str, qi::_1))] >>
      -(qi::lit ("Reconnect-Timeout:") >> qi::double_[
        phoenix::bind (static_cast <void (ACE_Time_Value::*) (double)> (&ACE_Time_Value::set),
                       phoenix::bind (&Einode_Configuration::reconnect_timeout_, qi::_r0),
                       qi::_1)]) >>
      this->data_channel_[phoenix::bind (&Einode_Configuration::data_channel_, qi::_r0) = qi::_1];

    this->data_channel_ %=
      qi::lit ("DataChannel:") >>
      this->directive_ >>
      this->probes_;

    this->probes_ %= *this->probe_;

    this->probe_ %=
      qi::lit ("probe") >>
      this->identifier_ >>                                        // name
      this->identifier_ >> qi::lit (':') >>                       // library
      this->identifier_ >> qi::lit ('(') >> qi::lit (')') >>      // symbol
      this->params_no_quotes_;                                    // parameters

    this->directive_ %=
      qi::raw[
        qi::lit ("dynamic") >>
        this->identifier_ >>                                          // name
        qi::lit ("Service_Object") >> qi::char_ ('*') >>              // Service_Object *
        this->identifier_ >> qi::char_ (':') >>                       // library
        this->identifier_ >> qi::char_ ('(') >> qi::char_ (')') >>    // symbol
        this->params_];                                               // parameters

    this->identifier_ %=
      qi::lexeme[(qi::char_ ('_') | qi::alpha) >> *(qi::alnum | qi::char_ ('_'))];

    this->params_ %=
      qi::char_ ('"') >> *(qi::char_ - '"') >> qi::char_ ('"');

    this->params_no_quotes_ %=
      qi::lexeme[qi::lit ('"') >> *(qi::char_ - '"') >> qi::lit ('"')];

    this->uuid_ %=
      qi::repeat (8)[qi::char_ ("0-9a-fA-F")] >> qi::char_ ('-') >>
      qi::repeat (4)[qi::char_ ("0-9a-fA-F")] >> qi::char_ ('-') >>
      qi::repeat (4)[qi::char_ ("0-9a-fA-F")] >> qi::char_ ('-') >>
      qi::repeat (2)[qi::char_ ("0-9a-fA-F")] >>
      qi::repeat (2)[qi::char_ ("0-9a-fA-F")] >> qi::char_ ('-') >>
      qi::repeat (12)[qi::char_ ("0-9a-fA-F")];

    /*
    this->uuid_ =
        this->uuid_time_low_[phoenix::bind (&ACE_Utils::UUID::time_low, qi::_r0, qi::_1)] >> qi::lit ('-') >>
        this->uuid_time_mid_[phoenix::bind (&ACE_Utils::UUID::time_mid, qi::_r0, qi::_1)] >> qi::lit ('-') >>
        this->uuid_time_hi_and_version_[phoenix::bind (&ACE_Utils::UUID::time_hi_and_version, qi::_r0, qi::_1)] >> qi::lit ('-') >>
        this->uuid_clock_seq_hi_and_reserved_[phoenix::bind (&ACE_Utils::UUID::clock_seq_hi_and_reserved, qi::_r0, qi::_1)] >>
        this->uuid_clock_seq_low_[phoenix::bind (&ACE_Utils::UUID::clock_seq_low, qi::_r0, qi::_1)] >> qi::lit ('-') >>
        this->uuid_node_id_[set_uuid_node_id ()];*/

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
  boost::spirit::qi::rule <IteratorT, Einode_Configuration (void), SpaceT> config_;

  boost::spirit::qi::rule <IteratorT, Einode_Configuration::Data_Channel (void), SpaceT> data_channel_;

  boost::spirit::qi::rule <IteratorT,
                           Einode_Configuration::Software_Probe_List (void),
                           SpaceT> probes_;

  boost::spirit::qi::rule <IteratorT,
                           Einode_Configuration::Software_Probe (void),
                           SpaceT> probe_;

  boost::spirit::qi::rule <IteratorT, std::string (), SpaceT> directive_;

  boost::spirit::qi::rule <IteratorT, std::string (), SpaceT> identifier_;

  boost::spirit::qi::rule <IteratorT, std::string (), SpaceT> params_;

  boost::spirit::qi::rule <IteratorT, std::string (), SpaceT> params_no_quotes_;

  boost::spirit::qi::rule <IteratorT, std::string (), SpaceT> uuid_;
};

//
// load_file
//
bool Einode_Configuration::load_file (const char * filename)
{
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

  namespace spirit = boost::spirit;
  namespace qi = boost::spirit::qi;
  namespace phoenix = boost::phoenix;

  // Initialize the stream iterators for the file.
  spirit::istream_iterator begin (file);
  spirit::istream_iterator end;

  // Parse the contents for the file.
  Einode_Configuration_Grammar <spirit::istream_iterator,
                                spirit::ascii::space_type>
                                grammar;

  return qi::phrase_parse (begin,
                           end,
                           grammar >> qi::eoi,
                           spirit::ascii::space,
                           *this);
}

//
// validate
//
bool Einode_Configuration::validate (void) const
{
  if (this->name_.empty ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - name is not defined\n")),
                       false);

  if (this->uuid_ == ACE_Utils::UUID::NIL_UUID)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - UUID is nil\n")),
                       false);

  if (this->data_channel_.directive_.empty ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - data channel directive undefined\n")),
                       false);

  return true;
}

}
