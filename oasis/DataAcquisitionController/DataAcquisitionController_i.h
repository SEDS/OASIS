// -*- C++ -*-

//=============================================================================
/**
 *  @file       DataAcquisitionController_i.h
 *
 *  $Id: DataAcquisitionController_i.h 2207 2012-06-08 20:02:32Z dfeiock $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DATA_ACQUISITION_CONTROLLER_I_H_
#define _OASIS_DATA_ACQUISITION_CONTROLLER_I_H_

#include "DataAcquisitionControllerS.h"
#include "oasis/config.h"

namespace OASIS
{

/**
 * @class DataAcquisitionController_i
 *
 * Default implementation of the DataAcquisitionController interface.
 */
class DataAcquisitionController_i :
  public POA_OASIS::DataAcquisitionController
{
public:
  /// Default constructor.
  DataAcquisitionController_i (void);

  /// Destructor.
  virtual ~DataAcquisitionController_i (void);

  /// Get the DAC's name.
  virtual char * name (void);

  /**
   * Send a command to the DAC for processing. The DAC will locate
   * the corrent Einode, and forward the command along.
   *
   * @param[in]       einode          Target Einode
   * @param[in]       cmdstr          The command string
   */
  virtual void send_command (const char * einode, const char * cmdstr);

  /**
   * Get a remote service by name.
   *
   * @param[in]       name            Name of the service
   */
  virtual RemoteService_ptr get_service (const char * name);

  /// Get a list of services installed on DAC.
  virtual RemoteServiceList * get_services (void);

  /// Get a list of the probes registered on DAC.
  virtual ProbeInstanceList * get_probe_instances (void);

  /// Get the schema for the specified probe
  virtual char * get_schema(const char * name, const char * einode);
};

}

#if defined (__OASIS_INLINE__)
#include "DataAcquisitionController_i.inl"
#endif

#endif  // !defined _OASIS_DATA_ACQUISITION_CONTROLLER_I_H_
