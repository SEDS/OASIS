// -*- C++ -*-

//=============================================================================
/**
 * @file        Servant_Traits_T.h
 *
 * $Id: Servant_Traits_T.h 1934 2011-09-28 14:56:30Z hillj $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_SERVANT_TRAITS_T_H_
#define _OASIS_SERVANT_TRAITS_T_H_

#include "oasis/config.h"

#include "OASIS_Tao_export.h"

namespace OASIS
{
// Forward decl.
struct NIL;

/**
 * @class Servant_Trait_T
 */
template <typename T, typename NEXT = NIL>
class Servant_Trait_T
{
public:
  /// Default constructor.
  Servant_Trait_T (void);

  /// Destructor.
  ~Servant_Trait_T (void);

  /**
   * Activate the specified object.
   *
   * @param[in]       obj         Object to activate
   */
  int handle_activate (::CORBA::Object_ptr obj);

  /**
   * Deactivate the specified object.
   *
   * @param[in]       obj         Object to deactivate
   */
  int handle_deactivate (::CORBA::Object_ptr obj);

  int set_value (int id, const ACE_CString & value);

  int get_value (int id, ACE_CString & value);

  /**
   * Test if the trait has been set.
   */
  bool is_set (void) const;

private:
  /// The next trait.
  NEXT next_;

  // The value of the trait.
  ACE_CString trait_value_;
};

/**
 * @class Servant_Trait_T
 */
template <typename T>
class Servant_Trait_T <T, NIL>
{
public:
  /// Default constructor.
  Servant_Trait_T (void);

  /// Destructor.
  ~Servant_Trait_T (void);

  /**
   * Activate the specified object.
   *
   * @param[in]       obj         Object to activate
   */
  int handle_activate (::CORBA::Object_ptr obj);

  /**
   * Deactivate the specified object.
   *
   * @param[in]       obj         Object to deactivate
   */
  int handle_deactivate (::CORBA::Object_ptr obj);

  int set_value (int id, const ACE_CString & value);

  int get_value (int id, ACE_CString & value);

  /**
   * Test if the trait has been set.
   */
  bool is_set (void) const;

private:
  /// The value of the trait.
  ACE_CString trait_value_;
};

}

#if defined (__OASIS_INLINE__)
#include "Servant_Traits_T.inl"
#endif

#include "Servant_Traits_T.cpp"

#endif  // !defined _CUTS_SERVANT_TRAITS_T_H_
