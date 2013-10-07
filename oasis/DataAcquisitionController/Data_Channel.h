// -*- C++ -*-

//=============================================================================
/**
 *  @file       Data_Channel.h
 *
 *  $Id: Data_Channel.h 1884 2011-08-28 20:14:39Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DAC_DATA_CHANNEL_H_
#define _OASIS_DAC_DATA_CHANNEL_H_

#include "ace/Service_Object.h"
#include "oasis/config.h"

#include "DAC_Core_export.h"

namespace OASIS
{
namespace DAC
{

/**
 * @class Data_Handler
 *
 * Interface for handlers to operate on date received by the DAC.
 */
class OASIS_DAC_CORE_Export Data_Channel :
  public ACE_Service_Object
{
public:
  /// Default constructor.
  Data_Channel (void);

  /// Destructor.
  virtual ~Data_Channel (void);

  /// The channel is being activated.
  virtual int handle_activate (void);

  /// The channel is being deactivated.
  virtual int handle_deactivate (void);
};

}
}

#if defined (__OASIS_INLINE__)
#include "Data_Channel.inl"
#endif

#endif  // !defined _OASIS_DAC_DATA_HANDLER_H_
