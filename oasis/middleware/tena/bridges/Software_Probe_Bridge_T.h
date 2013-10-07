// -*- C++ -*-

//=============================================================================
/**
 * @file        Software_Probe_Bridge_T.h
 *
 * $Id: Software_Probe_Bridge_T.h 2135 2012-02-16 15:39:18Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TENA_SOFTWARE_PROBE_BRIDGE_T_H_
#define _OASIS_TENA_SOFTWARE_PROBE_BRIDGE_T_H_

#include "Software_Probe_Bridge.h"
#include "Initial_Value_T.h"
#include "Var_T.h"
#include "Configuration_Group.h"
#include "Configuration_Manager.h"
#include "Configuration_Exception.h"

namespace OASIS
{

/**
 * @class Software_Probe_Bridge_T
 *
 * Template class for all software probe bridges. This bridge class defines
 * the necessary constructs for any given Tena SDO.
 */
template <typename SDO>
class Software_Probe_Bridge_T : public Software_Probe_Bridge
{
public:
  /// Type definition of the SDO type.
  typedef SDO sdo_type;

  /// Default constructor.
  Software_Probe_Bridge_T (void);

  /// Destructor.
  virtual ~Software_Probe_Bridge_T (void);

  /**
   * Configure the software probe bridge. This will create a new
   * servant for the bridge. If one is already set, then it will
   * create a new one thereby replacing the old/current one.
   *
   * @param[in]         session           TENA session object
   * @param[in]         config_file       Initial value config filename
   */
  virtual int configure (::TENA::Middleware::Session & session,
                         const ACE_CString & config_file);

  /**
   * Destroy a servant within this bridge.
   *
   * @param[in]           probe_name        Name of the probe to destroy
   */
  virtual int destroy_servant (const ACE_CString & probe_name);

protected:
  /// Helper method that initialize
  static int initialize_metadata (typename SDO::PublicationStateInitializer & initializer,
                                  const ACE_Utils::UUID & einode,
                                  const DAC::Software_Probe_Instance & inst);

  /// Type definition of the servant factory.
  typename SDO::ServantFactoryPtr factory_;

  /// Type definition for the map of servants.
  typedef std::map <ACE_CString, typename SDO::ServantPtr> ServantPtr_Map;

  /// Servants managed by the software probe bridge.
  ServantPtr_Map servants_;

  /// Initial value configuration group
  Configuration_Group group_;
};

/**
 * @struct updater_t
 */
template <typename T, typename P1>
struct updater_t
{
  /// Type definition of the setter method.
  typedef void (T::*FUNC_PTR) (P1);

  /**
   * Initializing constructor.
   *
   * @param[in]       funcptr       Pointer to setter method
   */
  updater_t (FUNC_PTR funcptr);

  /**
   * Functor for updating the target value.
   *
   * @param[in]       t             Target updater object
   * @param[in]       in            Input stream with data
   */
  int operator () (T & t, ACE_InputCDR & in);

private:
  /// Pointer to the setter method.
  FUNC_PTR funcptr_;
};

/**
 * @struct updater_t
 * Specialized for ::std::string
 */
template <typename T>
struct updater_t<T, const ::std::string &>
{
  /// Type definition of the setter method.
  typedef void (T::*FUNC_PTR) (const ::std::string &);

  /**
   * Initializing constructor.
   *
   * @param[in]       funcptr       Pointer to setter method
   */
  updater_t (FUNC_PTR funcptr);

  /**
   * Functor for updating the target value.
   *
   * @param[in]       t             Target updater object
   * @param[in]       in            Input stream with data
   */
  int operator () (T & t, ACE_InputCDR & in);

private:
  FUNC_PTR funcptr_;
};

/**
 * Function that creates the updater_t functor.
 */
template <typename T, typename P1>
updater_t <T, P1> updater (void (T::*func) (P1));

template <typename T>
updater_t <T, ::std::string> updater (void (T::*func) (::std::string));

}

#if defined (__OASIS_INLINE__)
#include "Software_Probe_Bridge_T.inl"
#endif

#include "Software_Probe_Bridge_T.cpp"

#endif  // !defined _OASIS_TENA_SOFTWARE_PROBE_BRIDGE_H_
