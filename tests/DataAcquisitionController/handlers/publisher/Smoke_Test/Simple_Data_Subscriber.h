// -*- C++ -*-

//=============================================================================
/**
 *  @file       Smoke_Test_Subscriber.h
 *
 *  $Id: Simple_Data_Subscriber.h 1885 2011-08-28 21:18:08Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _SIMPLE_DATA_SUBSCRIBER_H_
#define _SIMPLE_DATA_SUBSCRIBER_H_

#include "oasis/DataAcquisitionController/handler/Tao_Publisher/Tao_Publisher_ServiceS.h"

/**
 * @class Simple_Data_Subscriber
 *
 * Simple implementation of an OASIS::DataSubscriber interface.
 */
class Simple_Data_Subscriber : public POA_OASIS::DataSubscriber
{
public:
  /// Default constructor.
  Simple_Data_Subscriber (void);

  /// Destructor.
  virtual ~Simple_Data_Subscriber (void);

  virtual char * name (void);

  virtual void handle_data (const OASIS::SubscriberDataPacket & packet);
};

#endif  // !defined _SIMPLE_DATA_SUBSCRIBER_H_
