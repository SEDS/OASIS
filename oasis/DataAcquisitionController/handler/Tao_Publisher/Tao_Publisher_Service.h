// -*- C++ -*-

//=============================================================================
/**
 * @file        Publisher_Service.h
 *
 * $Id: Tao_Publisher_Service.h 2071 2011-12-01 15:48:16Z hillj $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DAC_PUBLISHER_SERVICE_H_
#define _OASIS_DAC_PUBLISHER_SERVICE_H_

#include "oasis/DataAcquisitionController/Data_Handler.h"
#include "oasis/middleware/tao/Servant_Manager_T.h"

#include "Tao_Publisher_ServiceS.h"
#include "Tao_PublisherService_i.h"

#include "Tao_Publisher_Service_export.h"

namespace OASIS
{

/**
 * @class Tao_Publisher_Service
 *
 * Publisher service for the DAC. This is a static service handler
 * in that it is always loaded by the DAC.
 */
class OASIS_TAO_PUBLISHER_SERVICE_Export Tao_Publisher_Service :
  public DAC::Data_Handler
{
public:
  /// Default constructor.
  Tao_Publisher_Service (void);

  /// Destructor.
  virtual ~Tao_Publisher_Service (void);

  /**
   * Initialize the archive data handler service.
   *
   * @param[in]       argc        Number of command-line arguments
   * @param[in]       argv        The command-line arguments
   */
  virtual int init (int argc, ACE_TCHAR *argv[]);

  /// Finalize the data handler.
  virtual int fini (void);

  /// Handle a new set of data.
  virtual int handle_data (const DAC::Data_Packet & packet);

  /// Get the publishers remote service.
  virtual RemoteService_ptr get_remote_service (void);

private:
  /// Helper method to initialize POA.
  void initialize_POA (PortableServer::POA_ptr the_POA);

  /// The ORB assigned to the service.
  CORBA::ORB_var orb_;

  /// The POA for this service.
  ::PortableServer::POA_var the_POA_;

  /// Implementation of the publisher servant.
  Tao_PublisherService_i publisher_;

  /// The publisher servant.
  Servant_Manager_T <Tao_PublisherService_i> servant_;
};

}

OASIS_DAC_DATA_HANDLER_DECL (OASIS_TAO_PUBLISHER_SERVICE, _make_OASIS_Tao_Publisher_Service);

#endif  // !defined _OASIS_DAC_ARCHIVE_DATA_HANDLER_H_
