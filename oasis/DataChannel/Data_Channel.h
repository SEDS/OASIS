// -*- C++ -*-

//=============================================================================
/**
 * @file        Data_Channel.h
 *
 * $Id: Data_Channel.h 2224 2012-12-10 06:35:58Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DATA_CHANNEL_H_
#define _OASIS_DATA_CHANNEL_H_

#include "oasis/middleware/Exceptions.h"
#include "Software_Probe_Data_Packager.h"
#include "Data_Channel_export.h"

namespace OASIS
{
// Forward decl
class Software_Probe_Data_Packager;

/**
 * @class Data_Channel
 *
 * Interface for data channel objects. This interface is responsible
 * for send data to a specified endpoint.
 */
class OASIS_DATA_CHANNEL_Export Data_Channel
{
public:
  /// Default constructor.
  Data_Channel (void);

  /// Destructor.
  virtual ~Data_Channel (void);

  /**
   * Send data over the data channel.
   *
   * @param[in]         data              Data to send
   * @param[in]         length            Size of the data
   * @throws            Transient_Error   Data failed to send
   */
  virtual void send_data (const char * data, size_t length) = 0;

  /**
   * Connect the data channel
   *
   * @throws            Connect_Error     Connection attempt failed
   */
  virtual void connect (void) = 0;

  /**
   * Test if the data channel is connected.
   *
   * @retval      true        Data channel is connected
   * @retval      false       Data channel is not connected
   */
  bool is_connected (void) const;

  /**
   * Get a concrete packager for the data channel type
   */
  virtual Software_Probe_Data_Packager * packager (void) = 0;

protected:
  // Data channel connection state
  bool is_connected_;

  // Packager prototype
  Software_Probe_Data_Packager * packager_;
};

}

#if defined (__OASIS_INLINE__)
#include "Data_Channel.inl"
#endif

#endif  // !defined _OASIS_DATA_CHANNEL_H_
