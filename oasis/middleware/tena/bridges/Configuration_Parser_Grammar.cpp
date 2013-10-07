// $Id:

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include "boost/spirit/include/phoenix_fusion.hpp"
#include "boost/spirit/include/phoenix_bind.hpp"

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/qi_char_class.hpp>

namespace OASIS
{

  namespace actor
  {
    /**
     * @struct allocate
     *
     * Functor/actor for allocating a new value. It is assumed that the
     * element's name triggers its creation.
     */
    template <typename T>
    struct allocate
    {
      template <typename Context>
      void operator () (boost::spirit::qi::unused_type, Context & ctx, boost::spirit::qi::unused_type) const
      {
        // Store node as the return value (i.e., qi::_val).
        namespace fusion = ::boost::fusion;
        fusion::at_c <0> (ctx.attributes) = new T();
      }
    };
  }

  //
  // Configuration_Parser_Grammar
  //
  template <typename IteratorT>
  Configuration_Parser_Grammar <IteratorT>::Configuration_Parser_Grammar (void)
    : Configuration_Parser_Grammar::base_type (this->spec_)
  {
    namespace qi = boost::spirit::qi;
    namespace phoenix = boost::phoenix;

    this->ident_ %= (qi::char_ ('_') | qi::alpha) >> *(qi::char_ ('_') | qi::alnum);

    this->no_newline_ %= *(qi::char_ - qi::char_ ('\n'));

    this->propvalue_ = this->no_newline_[actor::allocate <Configuration_Value> ()]
                                        [phoenix::bind (&Configuration_Value::value, qi::_val, qi::_1)];


    this->propname_ = this->ident_[phoenix::bind (&Configuration_Group::find_instance, qi::_r1, qi::_1, &qi::_val)] >>
                      qi::char_ ('.') >>
                      this->ident_[phoenix::bind (&Configuration_Instance::find_member, qi::_val, qi::_1, qi::_r2)] >>
                      *(qi::char_ ('.') >>
                        this->ident_[phoenix::bind (&Configuration_Member::find_member, *qi::_r2, qi::_1, qi::_r2)]);

    this->config_ = this->propname_ (qi::_r1, &qi::_a) >>
                    *qi::ascii::space >>
                    qi::char_ ('=') >>
                    *qi::ascii::space >>
                    this->propvalue_[phoenix::bind (&Configuration_Member::value, qi::_a, qi::_1)];

    this->spec_ = *(this->config_(qi::_r1) >> *qi::lit('\n'));

  }

}
