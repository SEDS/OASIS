// -*- C++ -*-

//=============================================================================
/**
 * @file        Tena_Publisher_Service.h
 *
 * $Id: Tena_Publisher_Service.h 2104 2012-01-12 19:14:13Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TENA_PUBLISHER_SERVICE_H_
#define _OASIS_TENA_PUBLISHER_SERVICE_H_

#include "OASIS/Middleware/SoftwareProbe.h"
#include "oasis/DataAcquisitionController/Data_Handler.h"
#include "oasis/DataAcquisitionController/Data_Packet.h"
#include "oasis/DataAcquisitionController/Registration_Packet.h"
#include "oasis/DataAcquisitionController/Unregistration_Packet.h"

#include <vector>

#include "ace/Auto_Ptr.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"

#include "Tena_Publisher_Configuration.h"
#include "Tena_Bridge_Factories.h"
#include "Tena_Publisher_Service_export.h"

namespace OASIS
{
// Forward decl.
class Software_Probe_Bridge_Manager;

/**
 * @class Tena_Publisher_Service
 *
 * Publisher service for the DAC. This is a static service handler
 * in that it is always loaded by the DAC.
 */
class OASIS_TENA_PUBLISHER_SERVICE_Export Tena_Publisher_Service :
  public DAC::Data_Handler
{
public:
  /// Default constructor.
  Tena_Publisher_Service (void);

  /// Destructor.
  virtual ~Tena_Publisher_Service (void);

  /**
   * Initialize the archive data handler service.
   *
   * @param[in]       argc        Number of command-line arguments
   * @param[in]       argv        The command-line arguments
   */
  virtual int init (int argc, char * argv []);

  /// Finalize the data handler.
  virtual int fini (void);

  /// Handle a new set of data.
  virtual int handle_data (const DAC::Data_Packet & packet);

  /// Handle a newly registered software probe.
  virtual int handle_registration (const DAC::Registration_Packet & packet);

  /// Handle the unregistration of an EINode and it's probes
  virtual int handle_unregister_einode (const DAC::Unregistration_Packet & packet);

private:
  /// Parse the command-line arguments.
  int parse_args (int argc, char * argv []);

  /// Helper method for loading the software probe bridge factories.
  int load_bridge_manager (const ACE_CString & file);

  /**
   * Load the software probe bridge for the specified software
   * probe instance type.
   *
   * @param[in]       inst            New software probe instance
   */
  int load_bridge (const OASIS::Software_Probe_Metadata &,
                   Software_Probe_Bridge * & bridge);

  /// Helper method to cleanup service objects.
  void cleanup (void);

  /// The service's configuration object.
  ACE_Auto_Ptr <Tena_Publisher_Configuration> config_;

  /// TENA middleware session
  ::TENA::Middleware::SessionPtr session_;

  /// TENA middleware runtime
  ::TENA::Middleware::RuntimePtr runtime_;

  /// TENA middleware execution
  ::TENA::Middleware::ExecutionPtr execution_;

  /// The initial value configuration file for the software probe bridge
  ACE_CString bridge_initial_values_;

  /// The tena config filename
  ACE_CString tena_config_;

  /// Collection of loaded software probe bridges.
  ACE_Hash_Map_Manager <ACE_CString,
                        Software_Probe_Bridge *,
                        ACE_Null_Mutex> loaded_bridges_;

  /// Collection of known bridge factory methods.
  ::OASIS::TENA_Bridge::Bridge_Factories bridge_factories_;
};

}

OASIS_DAC_DATA_HANDLER_DECL (OASIS_TENA_PUBLISHER_SERVICE, _make_OASIS_Tena_Publisher_Service);

#endif  // !defined _OASIS_DAC_ARCHIVE_DATA_HANDLER_H_
