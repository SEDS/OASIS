// -*- C++ -*-

//=============================================================================
/**
 * @file      Software_Probe_Bridge_Manager.h
 *
 * $Id: Software_Probe_Bridge_Manager.h 2135 2012-02-16 15:39:18Z dfeiock $
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TENA_SOFTWARE_PROBE_BRIDGE_MANAGER_H_
#define _OASIS_TENA_SOFTWARE_PROBE_BRIDGE_MANAGER_H_

#include "oasis/DataAcquisitionController/handler/Tena_Publisher/Tena_Bridge_Factories.h"
#include "Tena_Software_Probe_export.h"

namespace OASIS
{
// Forward decl.
class Software_Probe_Bridge;

/**
 * @class Software_Probe_Bridge_Manager
 */
class OASIS_TENA_SOFTWARE_PROBE_Export Software_Probe_Bridge_Manager
{
protected:
  /// Default constructor.
  Software_Probe_Bridge_Manager (void);

  /// Destructor.
  virtual ~Software_Probe_Bridge_Manager (void);

public:
  /// Release the manager, and its resources.
  virtual void release (void);

  /// Register bridge factories to the provided Bridge_Factories.
  virtual int register_factories (::OASIS::TENA_Bridge::Bridge_Factories & factories);
};

}


#define OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_FUNC _make_OASIS_Tena_Software_Probe_Bridge_Manager

#define OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_FUNC_STR "_make_OASIS_Tena_Software_Probe_Bridge_Manager"

#define OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_DECL(EXPORT_MACRO) \
  extern "C" EXPORT_MACRO \
  ::OASIS::Software_Probe_Bridge_Manager * \
  OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_FUNC (void)

#define OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_IMPL(TYPE) \
  ::OASIS::Software_Probe_Bridge_Manager * \
  OASIS_TENA_SOFTWARE_BRIDGE_MANAGER_EXPORT_FUNC (void) \
  { \
    TYPE * manager = 0; \
    ACE_NEW_RETURN (manager, TYPE (), 0); \
    return manager; \
  }

#endif  // !defined _OASIS_TENA_SOFTWARE_PROBE_BRIDGE_MANAGER_H_
