// -*- C++ -*-

//=============================================================================
/**
 * @file        Servant_Manager_T.h
 *
 * $Id: Servant_Manager_T.h 1934 2011-09-28 14:56:30Z hillj $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_SERVANT_MANAGER_T_H_
#define _OASIS_SERVANT_MANAGER_T_H_

#include "tao/PortableServer/POAC.h"
#include "oasis/config.h"

#include "OASIS_Tao_export.h"

namespace OASIS
{

/**
 * @class Servant_Manager_T
 *
 * Helper class for managing the lifecycle of a servant. This object
 * behaves like the std::auto_ptr class.
 */
template <typename T>
class Servant_Manager_T
{
public:
  /// Type definition of the servant type.
  typedef T type;

  /**
   * Initializing constructor.
   *
   * @param[in]       servant         Servant to host
   * @param[in]       manage          This object manages \a servant
   */
  Servant_Manager_T (T * servant = 0, bool manage = true);

  /// Desturctor
  ~Servant_Manager_T (void);

  /// Determine of the servant is managed.
  bool is_managed (void) const;

  /**
   * Reset the manager with a new servant.
   *
   * @param[in]       servant         Servant to host
   * @param[in]       manage          This object manages \a servant
   */
  int reset (T * servant = 0, bool manage = true);

  /**
   * Get a pointer to the actual servant.
   *
   * @return      The contained servant.
   */
  T * get (void);

  /**
   * Treat the servant manage as a pointer to the servant.
   *
   * @return      The contained servant.
   */
  T * operator -> (void);

  /**
   * Activate the servant under the specified POA.
   *
   * @param[in]   poa         Target POA for activation.
   */
  void activate (::PortableServer::POA_ptr poa);

  /// Deactivate the servant.
  void deactivate (void);

  /// Get a reference to the servant.
  ::CORBA::Object_ptr get_reference (void);

protected:
  /// Pointer to the servant.
  T * servant_;

  /// POA under which the servant is activated.
  ::PortableServer::POA_var poa_;

private:
  /// The servant is managed by this object.
  bool is_managed_;
};

/**
 * @class Servant_Manager_T
 */
template <typename T, typename TRAITS>
class Servant_Manager_Ex_T :
  public Servant_Manager_T <T>
{
public:
  /// Type definition of the servant type.
  typedef typename Servant_Manager_T <T>::type type;

  /// Type definition of the servant's traits.
  typedef TRAITS traits_type;

  /**
   * Initializing constructor.
   *
   * @param[in]       servant         Servant to host
   * @param[in]       manage          This object manages \a servant
   */
  Servant_Manager_Ex_T (T * servant = 0, bool manage = true);

  /// Desturctor
  ~Servant_Manager_Ex_T (void);

  /**
   * Activate the servant under the specified POA.
   *
   * @param[in]   poa         Target POA for activation.
   */
  void activate (::PortableServer::POA_ptr poa);

  /// Deactivate the servant.
  void deactivate (void);

  template <typename TRAIT>
  int set_trait_value (TRAIT trait, const ACE_CString & value);

  template <typename TRAIT>
  int get_trait_value (TRAIT trait, ACE_CString & value);

private:
  /// Traits of the servant manager.
  TRAITS traits_;
};

}

#if defined (__OASIS_INLINE__)
#include "Servant_Manager_T.inl"
#endif

#include "Servant_Manager_T.cpp"

#endif  // !defined _OASIS_SERVANT_MANAGER_T_H_
