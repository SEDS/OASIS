// -*- C++ -*-

//=============================================================================
/**
 * @file        Initial_Value_T.h
 *
 * $Id: Initial_Value_T.h 2135 2012-02-16 15:39:18Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TENA_INITIAL_VALUE_T_H_
#define _OASIS_TENA_INITIAL_VALUE_T_H_

#include "TENA/types.h"
#include <string>
#include "Configuration_Member_Container.h"
#include "Configuration_Member.h"
#include "Dereference_Var_T.h"

#include "Tena_Software_Probe_export.h"

namespace OASIS
{
  /**
   * @struct initialize_t
   */
  template <typename T, typename P1>
  struct initialize_t
  {
    /// Type definition of the setter method.
    typedef void (T::*FUNC_PTR) (P1);

    /**
     * Initializing constructor.
     *
     * @param[in]       funcptr       Pointer to setter method
     */
    initialize_t (FUNC_PTR funcptr);

    /**
     * Functor for updating the target value.
     *
     * @param[in]       t             Target initializer object
     */
    bool operator () (T & t);

    /**
     * Functor for updating the target value with default lookup.
     *
     * @param[in]       t             Target initializer object
     * @param[in]       value_id      Value identifier to look for
     * @param[in]       container     Container to look in for the value_id
     */
    bool operator () (T & t,
                      const std::string & value_id,
                      Configuration_Member_Container * container);

  private:
    /// Pointer to the setter method.
    FUNC_PTR funcptr_;
  };

  /**
   * @struct initialize_t
   * Specialized for std::string
   */
  template <typename T>
  struct initialize_t <T, const ::std::string &>
  {
    /// Type definition of the setter method.
    typedef void (T::*FUNC_PTR) (const ::std::string &);

    /**
     * Initializing constructor.
     *
     * @param[in]       funcptr       Pointer to setter method
     */
    initialize_t (FUNC_PTR funcptr);

    /**
     * Functor for updating the target value.
     *
     * @param[in]       t             Target initializer object
     */
    bool operator () (T & t);

    /**
     * Functor for updating the target value with default lookup.
     *
     * @param[in]       t             Target initializer object
     * @param[in]       value_id      Value identifier to look for
     * @param[in]       container     Container to look in for the value_id
     */
    bool operator () (T & t,
                      const std::string & value_id,
                      Configuration_Member_Container * container);

  private:
    /// Pointer to the setter method.
    FUNC_PTR funcptr_;
  };

  /**
   * Function that creates the updater_t functor.
   */
  template <typename T, typename P1>
  initialize_t <T, P1> initialize (void (T::*func) (P1));

  /**
   * Function that creates the updater_t functor.
   * Specialized for ::std::String
   */
  template <typename T>
  initialize_t <T, const ::std::string &> initialize (void (T::*func) (const ::std::string &));

  /**
   * @struct oasis_initial_value_t
   *
   * Defines the initial value for different value types.
   */
  template <typename T>
  struct oasis_initial_value_t;

  template < >
  struct OASIS_TENA_SOFTWARE_PROBE_Export oasis_initial_value_t < ::TENA::float32 >
  {
    static const ::TENA::float32 result_type;
  };

  template < >
  struct OASIS_TENA_SOFTWARE_PROBE_Export oasis_initial_value_t < ::TENA::float64 >
  {
    static const ::TENA::float64 result_type;
  };

  template < >
  struct OASIS_TENA_SOFTWARE_PROBE_Export oasis_initial_value_t < ::TENA::int8 const & >
  {
    static const ::TENA::int8 result_type = 0;
  };

  template < >
  struct OASIS_TENA_SOFTWARE_PROBE_Export oasis_initial_value_t < ::TENA::int16 const & >
  {
    static const ::TENA::int16 result_type = 0;
  };

  template < >
  struct OASIS_TENA_SOFTWARE_PROBE_Export oasis_initial_value_t < ::TENA::int32 const & >
  {
    static const ::TENA::int32 result_type = 0;
  };

  template < >
  struct oasis_initial_value_t < ::TENA::int64 const & >
  {
    static const ::TENA::int64 result_type = 0;
  };

  template < >
  struct OASIS_TENA_SOFTWARE_PROBE_Export oasis_initial_value_t < ::TENA::uint8 const & >
  {
    static const ::TENA::uint8 result_type = 0;
  };

  template < >
  struct OASIS_TENA_SOFTWARE_PROBE_Export oasis_initial_value_t < ::TENA::uint16 const & >
  {
    static const ::TENA::uint16 result_type = 0;
  };

  template < >
  struct OASIS_TENA_SOFTWARE_PROBE_Export oasis_initial_value_t < ::TENA::uint32 const & >
  {
    static const ::TENA::uint32 result_type = 0;
  };

  template < >
  struct OASIS_TENA_SOFTWARE_PROBE_Export oasis_initial_value_t < ::TENA::uint64 const & >
  {
    static const ::TENA::uint64 result_type = 0;
  };

  template < >
  struct OASIS_TENA_SOFTWARE_PROBE_Export oasis_initial_value_t < ::std::string const & >
  {
    static const ::std::string result_type;
  };
}

#endif  // !defined _OASIS_TENA_INITIAL_VALUE_T_H_
