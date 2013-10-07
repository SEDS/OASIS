// -*- C++ -*-

//=============================================================================
/**
 * @file        Local_Data_Channel_i.h
 *
 * $Id: LocalDataChannel_i.h 2221 2012-11-19 20:26:38Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_LOCALDATACHANNEL_I_H_
#define _OASIS_LOCALDATACHANNEL_I_H_

#include "oasis/DataChannel/Local_Data_Channel.h"
#include "oasis/config.h"

namespace OASIS
{
// Forward decl.
class Standard_EINode;

/**
 * @class LocalDataChannel
 *
 * Basic implementation of a local data channel object.
 */
class Local_Data_Channel_i : public Local_Data_Channel
{
public:
  /**
   * Initializing constructor.
   */
  Local_Data_Channel_i (Standard_EINode * einode);

  /// Destructor.
  virtual ~Local_Data_Channel_i (void);

  /**
   * Set data via the local data channel.
   *
   * @param[in]         data        Pointer to the data
   * @param[in]         length      Length of the data
   */
  virtual void send_data (const char * data, size_t length);

private:
  /// The parent EINode for this data channel.
  Standard_EINode * einode_;
};

}

#if defined (__OASIS_INLINE__)
#include "LocalDataChannel_i.inl"
#endif

#endif  // !defined _OASIS_LOCALDATACHANNEL_I_H_
