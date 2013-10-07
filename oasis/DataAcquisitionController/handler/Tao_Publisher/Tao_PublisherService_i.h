// -*- C++ -*-

//=============================================================================
/**
 * @file        Tao_PublisherService_i.h
 *
 * $Id: Tao_PublisherService_i.h 2069 2011-11-30 23:57:59Z hillj $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TAO_PUBLISHERSERVICE_I_H_
#define _OASIS_TAO_PUBLISHERSERVICE_I_H_

#include "Tao_Publisher_ServiceS.h"
#include "oasis/DataAcquisitionController/Data_Handler.h"

#include "ace/Null_Mutex.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/UUID.h"

namespace OASIS
{

/**
 * @class Tao_PublisherService_i
 *
 * Standard implementation of the DataAcquisitionControllerPublisher
 * interface.
 */
class Tao_PublisherService_i :
  public POA_OASIS::PublisherService
{
public:
  /// Default constructor.
  Tao_PublisherService_i (void);

  /// Destructor.
  virtual ~Tao_PublisherService_i (void);

  /// Get the service's name.
  virtual char * name (void);

  /**
   * Register for real-time updates.
   *
   * @param[in]         probe         Software probe of interest
   * @param[in]         subscriber    Subscriber interface
   * @return            Subscription cookie.
   */
  virtual void register_subscriber (const ::OASIS::UUID & probe,
                                    ::OASIS::DataSubscriber_ptr subscriber);

  /**
   * Unregister for real-time updates.
   *
   * @param[in]         c             Subscription cookie
   */
  virtual void unregister_subscriber (const ::OASIS::UUID & probe,
                                      ::OASIS::DataSubscriber_ptr subscriber);

  /**
   * Handle a new data packet. This will publish the contents of
   * the packet to all interested parties.
   */
  int handle_data (const DAC::Data_Packet & packet);

private:
  /// Type definition for the collection of subscribers.
  typedef ACE_Unbounded_Set <OASIS::DataSubscriber_var> Subscriber_Set;

  /// Type definition for the subscriber table.
  typedef ACE_Hash_Map_Manager <ACE_Utils::UUID,
                                Subscriber_Set *,
                                ACE_Null_Mutex>
                                Subscriber_Table;

  /// Collection of subscribers.
  Subscriber_Table subscribers_;
};

}

#endif  // !defined _OASIS_TAO_PUBLISHERSERVICE_I_H_
