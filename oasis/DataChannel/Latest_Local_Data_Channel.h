// -*- C++ -*-

//=============================================================================
/**
 *  @file       Latest_Local_Data_Channel.h
 *
 *  $Id: Latest_Local_Data_Channel.h 2221 2012-11-19 20:26:38Z dfeiock $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_LATEST_LOCAL_DATA_CHANNEL_H_
#define _OASIS_LATEST_LOCAL_DATA_CHANNEL_H_

#include "ace/Auto_Ptr.h"
#include "Local_Data_Channel.h"

namespace OASIS
{

/**
 * @class Latest_Local_Data_Channel
 *
 * Implementation of the local data channel that keeps track of the
 * latest data sent. This channel is good for testing if data is being
 * sent correctly. Moreover, it can be recalled to validate that the
 * data is preserved during packaging and unpackaging.
 */
class OASIS_DATA_CHANNEL_Export Latest_Local_Data_Channel :
  public Local_Data_Channel
{
public:
  /// Default constructor.
  Latest_Local_Data_Channel (void);

  /// Destructor.
  virtual ~Latest_Local_Data_Channel (void);

  /// Handle the sending of new data.
  void send_data (const char * data, size_t length);

  /// Get a pointer to the data.
  const char * get_data (void) const;

  /// Get the data length.
  size_t get_data_length (void) const;

private:
  /// The actual data.
  ACE_Auto_Array_Ptr <char> data_;

  /// The data's length.
  size_t length_;
};

}

#if defined (__OASIS_INLINE__)
#include "Latest_Local_Data_Channel.inl"
#endif

#endif  // !defined _OASIS_LATEST_LOCAL_DATA_CHANNEL_H_
