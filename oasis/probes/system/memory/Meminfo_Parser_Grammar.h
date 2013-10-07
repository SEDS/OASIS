// -*- C++ -*-

//=====================================================================
/**
 * @file       Meminfo_Parser_Grammar.h
 *
 * $Id: Meminfo_Parser_Grammar.h 2211 2012-07-25 12:55:51Z dfeiock $
 *
 * @author     James H. Hill
 */
//=====================================================================

#ifndef _OASIS_MEMINFO_PARSER_GRAMMAR_H_
#define _OASIS_MEMINFO_PARSER_GRAMMAR_H_

#include "boost/config/warning_disable.hpp"
#include "boost/spirit/include/qi.hpp"
#include "ace/Basic_Types.h"

namespace OASIS
{
namespace System
{
namespace Memory
{
  // Forward decl.
  class LinuxMemoryProbeImpl;

  /**
   * @class Meminfo_Parser_Grammar
   *
   * Grammar for parsing the data in /proc/meminfo.
   */
  template <typename IteratorT, typename SpaceT>
  class Meminfo_Parser_Grammar :
    public boost::spirit::qi::grammar <IteratorT, void (LinuxMemoryProbeImpl *), SpaceT>
  {
  public:
    /// Type definition of the grammar's iterator type.
    typedef IteratorT iterator_type;

    /// Type definition of the grammar's space type.
    typedef SpaceT space_type;

    /// Default constructor.
    Meminfo_Parser_Grammar (void);

  private:
    /// Definition of the main rule.
    boost::spirit::qi::rule <IteratorT, void (LinuxMemoryProbeImpl *), SpaceT> spec_;

    /// Rule for parsing a metric.
    boost::spirit::qi::rule <IteratorT, void (LinuxMemoryProbeImpl *), SpaceT> metric_;

    /// Rule for parsing a bare value.
    boost::spirit::qi::rule <IteratorT, ACE_UINT64 (void), SpaceT> value_;

    /// Rule for parsing the kilobytes for a value.
    boost::spirit::qi::rule <IteratorT, ACE_UINT64 (void), SpaceT> kilobytes_;
  };

}
}
}

#include "Meminfo_Parser_Grammar.cpp"

#endif
