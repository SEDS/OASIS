// -*- C++ -*-

//=============================================================================
/**
 * @file        DAC_Archive_Service.h
 *
 * $Id: Archive_Service.h 2238 2013-03-08 20:50:44Z tmpeiris $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DAC_ARCHIVE_SERVICE_H_
#define _OASIS_DAC_ARCHIVE_SERVICE_H_

#include "oasis/DataAcquisitionController/Data_Handler.h"
#include "ace/Auto_Ptr.h"

#if defined (OASIS_HAS_TAO)
#include "TAO_Archive_Service.h"
#include "Metric_Cursor_i.h"
#endif

#include <vector>

#include "Archive_Service_export.h"

namespace OASIS
{
// Forward decl.
class Software_Probe_Metadata;

// Forward decl.
class Metrics_Table;

/**
 * @class DAC_Archive_Service
 *
 * Implementation of a DAC data handler that stores collected
 * metrics in a SQLite database. This service is a static service
 * so it is loaded when the DAC is loaded.
 */
class OASIS_DAC_ARCHIVE_SERVICE_Export DAC_Archive_Service : public DAC::Data_Handler
{
public:
  /// Default constructor.
  DAC_Archive_Service (void);

  /// Destructor.
  virtual ~DAC_Archive_Service (void);

  /// Initialize the service.
  virtual int init (int argc, char *argv []);

  /// Finalize the data handler.
  virtual int fini (void);

  /// Get the archive remote service.
  virtual RemoteService_ptr get_remote_service (void);

  /// Handle a new data packet. The data packet will be stored in
  /// the target database.
  virtual int handle_data (const DAC::Data_Packet & packet);

#if defined (OASIS_HAS_TAO)
  /// Return a remote cursor to query the metric table
  Metric_Cursor_i * get_data_cursor (const char * __sqlstr__,
                                     std::vector <std::string> & values);
#endif

private:
  /// Helper method for parsing command-line options.
  int parse_args (int argc, char *argv [] );

  /// The metrics data table.
  ACE_Auto_Ptr <Metrics_Table> tbl_metrics_;

#if defined (OASIS_HAS_TAO)
  /// The TAO represntation of the Archive Service
  TAO_Archive_Service tao_service_;
#endif
};

}

// Declare the service factory.
OASIS_DAC_DATA_HANDLER_DECL (OASIS_DAC_ARCHIVE_SERVICE, _make_OASIS_DAC_Archive_Service);

#endif  // !defined _OASIS_DAC_ARCHIVE_DATA_HANDLER_H_
