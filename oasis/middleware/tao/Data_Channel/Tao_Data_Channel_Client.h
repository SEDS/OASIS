// -*- C++ -*-

//=============================================================================
/**
 * @file        Tao_Data_Channel_Client.h
 *
 * $Id: Tao_Data_Channel_Client.h 2220 2012-11-19 17:05:12Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_CORBA_DATA_CHANNEL_H_
#define _OASIS_CORBA_DATA_CHANNEL_H_

#include "DataChannelC.h"
#include "oasis/EINode/Data_Channel.h"

#include "oasis/middleware/tao/Servant_Manager_T.h"
#include "oasis/middleware/tao/ORB_Server_Task.h"

#include "Tao_CommandChannel_i.h"

#include "Tao_Data_Channel_Client_export.h"

namespace OASIS
{
/**
 * @class Tao_Data_Channel_Client
 *
 * Wrapper class for connecting the EINode to a CORBA data channel that
 * has been exposed by a Data Acquisition Controller.
 */
class Tao_Data_Channel_Client : public Data_Channel_Service
{
public:
  /// Default constructor.
  Tao_Data_Channel_Client (void);

  /// Destructor.
  virtual ~Tao_Data_Channel_Client (void);

  /**
   * Initialize this data channel.
   *
   * @param[in]       argc          Number of command-line arguments
   * @param[in]       argv          The actual command-line arguments
   */
  virtual int init (int argc, char * argv []);

  /// Finalize the data channel.
  virtual int fini (void);

  /// Set the EINode for this data channel.
  virtual void set_einode (Standard_EINode * einode);

  /// Perform the registration.
  virtual int perform_registration (const SoftwareProbe_Hash_Map & probes);

  /**
   * Send data to the DAC. This method used to send the data to the
   * DAC is dependent on how it is initialized.
   *
   * @param[in]       data            The actual data
   * @param[in]       length          Size of the payload.
   */
  virtual void send_data (const char * data, size_t length);

  /**
   * Connect the data channel
   *
   * @throws          Connect_Error   Connection attempt failed
   */
  virtual void connect (void);

  /**
   * Factory method for the TAO_Software_Probe_Data_Packager
   */
  virtual Software_Probe_Data_Packager * packager (void);

private:
  /// Helper method for parsing command-line arguments.
  int parse_args (int argc, ACE_TCHAR * argv []);

  /// Helper method for creating a child POA
  PortableServer::POA_ptr create_command_channel_POA (PortableServer::POA_ptr);

  /// ORB for this object.
  ::CORBA::ORB_var orb_;

  /// The parent EINode for this data channel.
  Standard_EINode * einode_;

  /// The data channel connected to the DAC.
  DataChannel_var data_channel_;

  /// Flag to destroy the orb.
  bool run_orb_;

  /// Implementation of the command channel.
  Tao_CommandChannel_i command_channel_;

  /// The command channel servant.
  OASIS::Servant_Manager_T <Tao_CommandChannel_i> servant_;

  /// Task object for running the ORB, if applicable.
  ORB_Server_Task orb_task_;
};

}

ACE_FACTORY_DECLARE (OASIS_TAO_DATACHANNEL_CLIENT, OASIS_Tao_Data_Channel_Client)


#endif  // !defined _OASIS_STANDARD_EINODE_DATA_CHANNEL_H_
