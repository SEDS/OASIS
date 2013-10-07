// $Id: TAO_Archive_Service.h 2238 2013-03-08 20:50:44Z tmpeiris $

#ifndef _OASIS_TAO_ARCHIVE_SERVICE_H_
#define _OASIS_TAO_ARCHIVE_SERVICE_H_

#include "ace/Auto_Ptr.h"
#include "oasis/middleware/tao/Servant_Manager_T.h"
#include "Archive_Service_i.h"
#include "Archive_ServiceS.h"

#define OASIS_OBV_REGISTER_FACTORY(FACTORY, VALUETYPE) \
  { CORBA::ValueFactory factory = new FACTORY; \
    CORBA::ValueFactory prev_factory = \
    this->orb_->register_value_factory (\
      VALUETYPE::_tao_obv_static_repository_id (),\
                                   factory); \
    if (prev_factory) prev_factory->_remove_ref (); \
    factory->_remove_ref (); }


namespace OASIS
{

// Forward Decl
class DAC_Archive_Service;

/**
 * @class TAO_Archive_Service
 *
 * Standard implementation of the TAO_Archive_Service
 */
class TAO_Archive_Service
{
public:

  /// Default constructor
  TAO_Archive_Service (void);

  /// Destructor
  ~TAO_Archive_Service (void);

  /// Initialize the service.
  int init (int argc, char *argv [],
            DAC_Archive_Service * archive_service);

  /// Finalize the data handler.
  int fini (void);

  /// Get the archive remote service.
  RemoteService_ptr get_remote_service (void);

private:

  /// Register different query factories with ORB
  void register_query_factories (void);

  /// The ORB assigned to the service.
  CORBA::ORB_var orb_;

  /// The POA for this service.
  ::PortableServer::POA_var the_POA_;

  /// The publisher servant.
  Servant_Manager_T <DAC_Archive_Service_i> servant_;

};

}

#endif