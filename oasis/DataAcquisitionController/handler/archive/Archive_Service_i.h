// $Id: Archive_Service_i.h 2238 2013-03-08 20:50:44Z tmpeiris $

#ifndef _OASIS_DAC_ARCHIVE_SERVICE_I_H_
#define _OASIS_DAC_ARCHIVE_SERVICE_I_H_

#include "Archive_ServiceS.h"
#include "oasis/DataAcquisitionController/Data_Handler.h"
#include "Metric_Cursor_i.h"
#include "Query_i.h"

#include "ace/Null_Mutex.h"


namespace OASIS
{

// Forward Decl
class DAC_Archive_Service;

/**
 * @class DAC_Archive_Service_i
 *
 * Implementation for the Archive Service TAO version.
 * service.
 */
class DAC_Archive_Service_i :
  public POA_OASIS::ArchiveService
{
public:

  /// Initializing constructor
  DAC_Archive_Service_i (::PortableServer::POA_ptr parent,
                         DAC_Archive_Service * archive_service);

  /// Destructor.
  virtual ~DAC_Archive_Service_i (void);

  /// Get the service's name.
  virtual char * name (void);

  /// Returns a remote cursor to the client, so he can iterate throgh the records
  virtual ::OASIS::Cursor_ptr get_data (::OASIS::Query * query);


private:

  /// POA for activating the servants
  ::PortableServer::POA_var archiver_poa_;

  /// The Service which has the access to the data.
  DAC_Archive_Service * service_;

};

}

#endif  // !defined #define _OASIS_DAC_ARCHIVE_SERVICE_I_H_
