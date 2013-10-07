// -*- C++ -*-

//=============================================================================
/**
 * @file        Data_Channel_Publisher.h
 *
 * $Id: Data_Channel_Publisher.h 1964 2011-10-03 02:59:33Z hillj $
 *
 * @author      Harold Owens II
 *              James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TENA_DATA_CHANNEL_H_
#define _OASIS_TENA_DATA_CHANNEL_H_

#include <OASIS/Middleware/DataPacket.h>
#include <OASIS/Middleware/DataChannel.h>
#include <OASIS/Middleware/RegistrationChannel.h>
#include <OASIS/Middleware/SoftwareProbeEntry.h>

#include "oasis/EINode/Data_Channel.h"
#include "Configuration.h"

#include "Data_Channel_Publisher_export.h"

namespace OASIS
{
/**
 * @class Data_Channel_Publisher
 *
 * Wrapper class for connecting the EINode to a TENA data channel that
 * has been exposed by a Data Acquisition Controller.
 */
class Data_Channel_Publisher : public Data_Channel_Service
{
public:
  /// Default constructor.
  Data_Channel_Publisher (void);

  /// Destructor.
  virtual ~Data_Channel_Publisher (void);

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
   * @param[in]       data          The actual data
   * @param[in]       length        Size of the payload.
   */
  virtual void send_data (const char * data, size_t length);

private:
  /// Helper method that creates the servant.
  int create_registration_channel_servant (const std::vector <OASIS::Middleware::SoftwareProbeEntry::ImmutableLocalClassPtr> &);
  int create_data_channel_servant (const std::vector <TENA::octet> & data);

  /// Helper method that performs cleanup operations.
  void cleanup (void);

  /// The parent EINode for this data channel.
  Standard_EINode * einode_;

  /// TENA middleware session
  TENA::Middleware::SessionPtr session_;

  /// TENA middleware runtime
  TENA::Middleware::RuntimePtr runtime_;

  /// TENA middleware execution
  TENA::Middleware::ExecutionPtr execution_;

  /// The DataChannel servant.
  OASIS::Middleware::DataChannel::ServantPtr data_channel_;
  OASIS::Middleware::RegistrationChannel::ServantPtr reg_channel_;

  /// The configuration for the publisher.
  Configuration config_;
};

}

ACE_FACTORY_DECLARE (OASIS_TENA_DATACHANNEL_PUBLISHER, OASIS_Tena_Data_Channel_Publisher)


#endif  // !defined _OASIS_STANDARD_EINODE_DATA_CHANNEL_H_
