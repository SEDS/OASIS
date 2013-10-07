// -*- C++ -*-

//=============================================================================
/**
 * @file        Local_Data_Channel.h
 *
 * $Id: Local_Data_Channel.h 2221 2012-11-19 20:26:38Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_LOCAL_DATA_CHANNEL_H_
#define _OASIS_LOCAL_DATA_CHANNEL_H_

#include "Data_Channel.h"

#include "oasis/config.h"

namespace OASIS
{

/**
 * @class Local_Data_Channel
 *
 * Interface for local data channel objects. The main difference
 * between a this interface and a Data_Channel is this interface
 * is for data channel implementations that are locality constrained,
 * such as the data channel between a software probe and EINode.
 *
 * Local data channels do not provide their own packager.  Instead,
 * the EINode provides the target middleware packager to them.
 */
class OASIS_DATA_CHANNEL_Export Local_Data_Channel :
  public Data_Channel
{
public:
  /// Default constructor.
  Local_Data_Channel (void);

  /// Destructor.
  virtual ~Local_Data_Channel (void);

  /// Connect
  virtual void connect (void);

  /// Packager getter
  Software_Probe_Data_Packager * packager (void);

  /// Packager setter
  void packager (Software_Probe_Data_Packager * p);
};

}

#if defined (__OASIS_INLINE__)
#include "Local_Data_Channel.inl"
#endif

#endif  // !defined _OASIS_DATA_CHANNEL_H_
