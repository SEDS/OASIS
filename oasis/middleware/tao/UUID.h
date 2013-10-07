// -*- C++ -*-

//=============================================================================
/**
 * @file          UUID.h
 *
 * $Id: UUID.h 1863 2011-08-19 18:39:59Z hillj $
 *
 * @author        James H. Hill
 */
//=============================================================================

#ifndef _OASIS_UUID_H_
#define _OASIS_UUID_H_

#include "OASIS_UUIDC.h"
#include "ace/UUID.h"

#include "OASIS_Tao_export.h"

/**
 * Extract a ::OASIS::UUID from the CORBA structure and store it in an
 * ACE_Utils::UUID object.
 *
 * @param[in]         src           Source object
 * @param[in]         dst           Destination object
 * @retval            true          Successfully extracted data
 * @retval            false         Failed to extract data
 */
OASIS_TAO_Export
bool operator >>= (const ::OASIS::UUID & src, ACE_Utils::UUID & dst);

/**
 * Insert an ACE_Utils::UUID object into an ::OASIS::UUID CORBA
 * structure.
 *
 * @param[in]         dst           Destination object
 * @param[in]         src           Source object
 * @retval            true          Successfully inserted data
 * @retval            false         Failed to insert data
 */
OASIS_TAO_Export
bool operator <<= (::OASIS::UUID & dst, const ACE_Utils::UUID & src);

#endif  // !defined _EISA_UUID_H_
