// -*- C++ -*-

//=============================================================================
/**
 *  @file       Data_Channel_Service.h
 *
 *  $Id: Command_Channel_Adapter.h 1965 2011-10-03 15:05:32Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TAO_COMMAND_CHANNEL_ADAPTER_H_
#define _OASIS_TAO_COMMAND_CHANNEL_ADAPTER_H_

#include "CommandChannelC.h"
#include "oasis/DataAcquisitionController/Command_Channel.h"

namespace OASIS
{
/**
 * @class Tao_Command_Channel_Adapter
 *
 * Adapter class for ::OASIS::CommandChannel objects. This class allows
 * the ::OASIS::CommandChannel to expose the OASIS::DAC::Command_Channel
 * interface expected by the DAC.
 */
class Tao_Command_Channel_Adapter :
  public DAC::Command_Channel
{
public:
  /**
   * Initializing constructor
   *
   * @param[in]       channel         Target CommandChannel object
   */
  Tao_Command_Channel_Adapter (CommandChannel_ptr channel = CommandChannel::_nil ());

  /// Destructor.
  virtual ~Tao_Command_Channel_Adapter (void);

  /// Reset the adapter with a new pointer.
  void reset (CommandChannel_ptr channel = CommandChannel::_nil ());

  /// Release the current pointer.
  CommandChannel_ptr release (void);

  /**
   * Handle a command. This command is parsed, then forwarded to the
   * adaptee.
   *
   * @param[in]       command         Command to handle.
   */
  int handle_command (const ACE_CString & command);

private:
  /// Pointer to the CORBA command channel.
  CommandChannel_var adaptee_;
};

}

#endif  // !defined _OASIS_TAO_COMMAND_CHANNEL_ADAPTER_H_
