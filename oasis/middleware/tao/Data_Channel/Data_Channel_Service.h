// -*- C++ -*-

//=============================================================================
/**
 *  @file       Data_Channel_Service.h
 *
 *  $Id: Data_Channel_Service.h 1963 2011-10-03 02:45:41Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TAO_DATA_CHANNEL_SERVICE_H_
#define _OASIS_TAO_DATA_CHANNEL_SERVICE_H_

#include "DataChannelS.h"

#include "oasis/middleware/tao/IOR_Table_Trait.h"
#include "oasis/middleware/tao/ORB_Server_Task.h"
#include "oasis/middleware/tao/Servant_Manager_T.h"
#include "oasis/middleware/tao/Servant_Traits_T.h"
#include "oasis/DataAcquisitionController/Data_Channel.h"

#include "DataChannel_export.h"

namespace OASIS
{
// Forward decl.
class Tao_DataChannel_i;

/**
 * @class Tao_Data_Channel_Service
 *
 * Implementation of the standard DAC's data channel.
 */
class Tao_Data_Channel_Service : public DAC::Data_Channel
{
public:
  /// Constructor.
  Tao_Data_Channel_Service (void);

  /// Destructor.
  virtual ~Tao_Data_Channel_Service (void);

  /// Initialize the object.
  virtual int init (int argc, ACE_TCHAR * argv []);

  /// Finalize the object.
  virtual int fini (void);

  /// Handle activation of the channel.
  virtual int handle_activate (void);

  /// Handle deactivation of the channel.
  virtual int handle_deactivate (void);

private:
  /// Parse the command-line arguments.
  int parse_args (int argc, ACE_TCHAR * argv []);

  /// Initialize the POA for this object.
  void initialize_poa (::PortableServer::POA_ptr poa);

  /// Initialize the servant.
  void initialize_servant (void);

  /// The ORB for the object.
  ::CORBA::ORB_var orb_;

  /// The POA for this servant.
  ::PortableServer::POA_var poa_;

  /// Type definition of the servant's traits.
  typedef Servant_Trait_T <IOR_Table_Trait> servant_traits_t;

  /// The DAC's servant.
  Servant_Manager_Ex_T <Tao_DataChannel_i, servant_traits_t> servant_;

  /// The task for the ORB.
  ACE_Auto_Ptr <ORB_Server_Task> task_;
};

}

ACE_FACTORY_DECLARE (OASIS_TAO_DATACHANNEL, OASIS_Tao_Data_Channel_Service)

#endif  // !defined _OASIS_STANDARD_DAC_DATACHANNEL_I_H_
