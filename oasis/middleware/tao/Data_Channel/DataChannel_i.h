// -*- C++ -*-

//=============================================================================
/**
 *  @file       DataChannel_i.h
 *
 *  $Id: DataChannel_i.h 2211 2012-07-25 12:55:51Z dfeiock $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TAO_DATACHANNEL_I_H_
#define _OASIS_TAO_DATACHANNEL_I_H_

#include "DataChannelS.h"
#include "oasis/middleware/tao/IOR_Table_Trait.h"
#include "oasis/middleware/tao/Servant_Manager_T.h"
#include "oasis/middleware/tao/Servant_Traits_T.h"
#include "oasis/DataAcquisitionController/Data_Channel.h"
#include "oasis/DataAcquisitionController/Registration_Packet.h"

namespace OASIS
{

/// Type definition for the metadata registry
typedef ACE_Hash_Map_Manager <std::string,
                              DAC::Software_Probe_Metadata_ptr,
                              ACE_Thread_Mutex> Metadata_Registry;

/**
 * @class Tao_DataChannel_i
 *
 * Implementation of the standard DAC's data channel.
 */
class Tao_DataChannel_i : public POA_OASIS::DataChannel
{
public:
  /**
   * Initializing constructor.
   */
  Tao_DataChannel_i (void);

  /// Destructor.
  virtual ~Tao_DataChannel_i (void);

  /// Handle new data from the EINode.
  virtual void send_data (const DataPacket & packet);

  /**
   * Register an EINode
   *
   * @param[in]         r           Registration data
   */
  virtual void register_einode (const EINodeRegistration & r);

  /**
   * Unregister an EINode
   *
   * @param[in]         uuid        UUID to unregister.
   */
  virtual void unregister_einode (const UUID & uuid);

private:
  // Helper method for building registration packets
  void build_registration_packet (const EINodeRegistration & einode_reg,
                                  DAC::Registration_Packet & packet);

  /// Collection of all the metadata objects recieved by the data channel
  Metadata_Registry registry_;
};

}

#endif  // !defined _OASIS_STANDARD_DAC_DATACHANNEL_I_H_
