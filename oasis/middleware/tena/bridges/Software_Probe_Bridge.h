// -*- C++ -*-

//=============================================================================
/**
 * @file        Software_Probe_Bridge.h
 *
 * $Id: Software_Probe_Bridge.h 2135 2012-02-16 15:39:18Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TENA_SOFTWARE_PROBE_BRIDGE_H_
#define _OASIS_TENA_SOFTWARE_PROBE_BRIDGE_H_

#include "TENA/Middleware/config.h"
#include "TENA/Middleware/SessionPtr.h"
#include "OASIS/Middleware/SoftwareProbe.h"

#include "oasis/DataAcquisitionController/Data_Packet.h"
#include "oasis/DataAcquisitionController/Registration_Packet.h"

#include "ace/CDR_Stream.h"

#include "Tena_Software_Probe_export.h"

namespace OASIS
{
/**
 * @class Software_Probe_Bridge
 *
 * Base class for all TENA software probe bridges. The software probe
 * bridge is responsible for translating OASIS data from a software
 * probe to its corresponding TENA SDO.
 */
class OASIS_TENA_SOFTWARE_PROBE_Export Software_Probe_Bridge
{
public:
  /// Default constructor.
  Software_Probe_Bridge (void);

  /// Destructor.
  virtual ~Software_Probe_Bridge (void) = 0;

  /**
   * Configure the software probe bridge. This will create a new
   * servant for the bridge. If one is already set, then it will
   * create a new one thereby replacing the old/current one.
   *
   * @param[in]         session           TENA session object
   * @param[in]         config_file       Initial value config file
   */
  virtual int configure (::TENA::Middleware::Session & session,
                         const ACE_CString & config_file) = 0;

  /**
   * Create a new servant within this bridge. It is assumed that
   * each software probe instance has a corresponding TENA servant
   * in the bridge.
   *
   * @param[in]           einode            Parent EI node
   * @param[in]           metadata          Software probe metadata
   */
  virtual int create_servant (const ACE_Utils::UUID & einode,
                              const ::OASIS::DAC::Software_Probe_Instance & inst) = 0;

  /**
   * Destroy a servant within this bridge.
   *
   * @param[in]           probe_name        Name of the probe to destroy
   */
  virtual int destroy_servant (const ACE_CString & probe_name) = 0;

  /**
   * Publish a data packet. The bridge will tranlate the package from
   * its OASIS format a TENA object. This is done by calling the set_*
   * methods on the target SDO.
   */
  virtual int publish (const DAC::Data_Packet & packet) = 0;

  typedef ::OASIS::Middleware::SoftwareProbe::PublicationStateUpdater PublicationStateUpdater;

  /// Helper method for updating the software probe values.
  static int update (PublicationStateUpdater & updater, ACE_InputCDR & input);
};

}

#if defined (__OASIS_INLINE__)
#include "Software_Probe_Bridge.inl"
#endif

#endif  // !defined _OASIS_TENA_SOFTWARE_PROBE_BRIDGE_H_
