// -*- C++ -*-

//=============================================================================
/**
 * @file        Tena_Bridge_Factories.h
 *
 * $Id: Tena_Bridge_Factories.h 2104 2012-01-12 19:14:13Z dfeiock $
 *
 * @author      Dennis Feiock
 */
//=============================================================================

#ifndef _OASIS_TENA_BRIDGE_FACTORIES_H_
#define _OASIS_TENA_BRIDGE_FACTORIES_H_

#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"

namespace OASIS
{
// Forward decl.
class Software_Probe_Bridge;

namespace TENA_Bridge
{
  /// Type definition of the bridge factory method.
  typedef Software_Probe_Bridge * (*BRIDGE_FACTORY_METHOD) (void);

  /// Type definition of the registered bridge factories.
  typedef ACE_Hash_Map_Manager <ACE_CString,
                                BRIDGE_FACTORY_METHOD,
                                ACE_Null_Mutex> Bridge_Factories;

}
}

#endif  // !defined _TENA_BRIDGE_FACTORIES_H_
