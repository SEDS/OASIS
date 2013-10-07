// -*- C++ -*-

//=============================================================================
/**
 * @file        IOR_File_Trait.h
 *
 * $Id: IOR_File_Trait.h 1863 2011-08-19 18:39:59Z hillj $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_IOR_FILE_TRAIT_H_
#define _OASIS_IOR_FILE_TRAIT_H_

#include "tao/corba.h"
#include "OASIS_Tao_export.h"

namespace OASIS
{

/**
 * @struct IOR_File_Trait
 */
struct OASIS_TAO_Export IOR_File_Trait
{
public:
  /// Pre-assigned id for the trait.
  static const int ID = 0;

  /**
   * Notification for activating an object.
   *
   * @param[in]       obj         Object undergoing activation
   * @param[in]       value       Value of the trait
   */
  static int handle_activate (::CORBA::Object_ptr obj, const ACE_CString & value);

  /**
   * Notification for deactivating an object.
   *
   * @param[in]       obj         Object undergoing deactivation
   * @param[in]       value       Value of the trait
   */
  static int handle_deactivate (::CORBA::Object_ptr obj, const ACE_CString & value);
};

}

#endif  // !defined _OASIS_IOR_FILE_TRAIT_H_
