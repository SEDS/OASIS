// -*- C++ -*-

//=============================================================================
/**
 * @file        Dereference_Var_T.h
 *
 * $Id: Dereference_Var_T.h 2135 2012-02-16 15:39:18Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TENA_DEREFERENCE_VAR_T_H_
#define _OASIS_TENA_DEREFERENCE_VAR_T_H_

#include "TENA/types.h"
#include <string>

namespace OASIS
{

/**
 * @struct oasis_dereference_var_t
 *
 * Functor that converts a TENA built-in type to an OASIS type.
 */
template <typename T>
struct oasis_dereference_var_t;

template < >
struct oasis_dereference_var_t < ::TENA::float32 >
{
  typedef ::TENA::float32 result_type;
};

template < >
struct oasis_dereference_var_t < ::TENA::float64 >
{
  typedef ::TENA::float64 result_type;
};

template < >
struct oasis_dereference_var_t < ::TENA::int8 const & >
{
  typedef ::TENA::int8 result_type;
};

template < >
struct oasis_dereference_var_t < ::TENA::int16 const & >
{
  typedef ::TENA::int16 result_type;
};

template < >
struct oasis_dereference_var_t < ::TENA::int32 const & >
{
  typedef ::TENA::int32 result_type;
};

template < >
struct oasis_dereference_var_t < ::TENA::int64 const & >
{
  typedef ::TENA::int64 result_type;
};

template < >
struct oasis_dereference_var_t < ::TENA::uint8 const & >
{
  typedef ::TENA::uint8 result_type;
};

template < >
struct oasis_dereference_var_t < ::TENA::uint16 const & >
{
  typedef ::TENA::uint16 result_type;
};

template < >
struct oasis_dereference_var_t < ::TENA::uint32 const & >
{
  typedef ::TENA::uint32 result_type;
};

template < >
struct oasis_dereference_var_t < ::TENA::uint64 const & >
{
  typedef ::TENA::uint64 result_type;
};

template < >
struct oasis_dereference_var_t < ::std::string const & >
{
  typedef ::std::string result_type;
};

template < >
struct oasis_dereference_var_t < bool const & >
{
  typedef bool result_type;
};

}

#endif // !defined _OASIS_TENA_DEREFERENCE_VAR_T_H_
