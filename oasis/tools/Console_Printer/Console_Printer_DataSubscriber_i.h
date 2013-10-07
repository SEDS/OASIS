// -*- C++ -*-

//=============================================================================
/**
 *  @file       Data_Subscriber_i.h
 *
 *  $Id: Console_Printer_DataSubscriber_i.h 2071 2011-12-01 15:48:16Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _CONSOLE_PRINTER_DATA_SUBSCRIBER_H_
#define _CONSOLE_PRINTER_DATA_SUBSCRIBER_H_

#include "oasis/DataAcquisitionController/handler/Tao_Publisher/Tao_Publisher_ServiceS.h"

namespace OASIS
{

/**
 * @class Simple_Data_Subscriber
 *
 * Simple implementation of an OASIS::DataSubscriber interface.
 */
class Console_Printer_DataSubscriber_i : public POA_OASIS::DataSubscriber
{
public:
  /// Default constructor.
  Console_Printer_DataSubscriber_i (void);

  /// Destructor.
  virtual ~Console_Printer_DataSubscriber_i (void);

  /// Name of the data subscriber.
  virtual char * name (void);

  /**
   * Callback for receiving published data.
   *
   * @param[in]       packet        Subscriber data packet
   */
  virtual void handle_data (const OASIS::SubscriberDataPacket & packet);
};

}

#endif  // !defined _SIMPLE_DATA_SUBSCRIBER_H_
