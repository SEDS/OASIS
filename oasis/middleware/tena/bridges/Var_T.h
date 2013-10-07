// -*- C++ -*-

//=============================================================================
/**
 * @file        Var_T.h
 *
 * $Id: Var_T.h 2135 2012-02-16 15:39:18Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TENA_VAR_T_H_
#define _OASIS_TENA_VAR_T_H_

#include "TENA/types.h"

namespace OASIS
{

/**
 * @struct oasis_var_t
 *
 * Functor that converts a TENA built-in type to an OASIS type.
 */
template <typename T>
struct oasis_var_t;

template < >
struct oasis_var_t < ::TENA::float32 >
{
  typedef ACE_CDR::Double result_type;
};

template < >
struct oasis_var_t < ::TENA::float64 >
{
  typedef ACE_CDR::LongDouble result_type;
};

template < >
struct oasis_var_t < ::TENA::int8 const & >
{
  typedef ACE_CDR::Char result_type;
};

template < >
struct oasis_var_t < ::TENA::int16 const & >
{
  typedef ACE_CDR::Short result_type;
};

template < >
struct oasis_var_t < ::TENA::int32 const & >
{
  typedef ACE_CDR::Long result_type;
};

template < >
struct oasis_var_t < ::TENA::int64 const & >
{
  typedef ACE_CDR::LongLong result_type;
};

template < >
struct oasis_var_t < ::TENA::uint8 const & >
{
  typedef ACE_CDR::Octet result_type;
};

template < >
struct oasis_var_t < ::TENA::uint16 const & >
{
  typedef ACE_CDR::UShort result_type;
};

template < >
struct oasis_var_t < ::TENA::uint32 const & >
{
  typedef ACE_CDR::ULong result_type;
};

template < >
struct oasis_var_t < ::TENA::uint64 const & >
{
  typedef ACE_CDR::ULongLong result_type;
};

}

#endif // !defined _OASIS_TENA_VAR_T_H_
