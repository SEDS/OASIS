// -*- C++ -*-

//=============================================================================
/**
 *  @file       Tao_CommandChannel_i.h
 *
 *  $Id: Tao_CommandChannel_i.h 1965 2011-10-03 15:05:32Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_TAO_COMMANDCHANNEL_I_H_
#define _OASIS_TAO_COMMANDCHANNEL_I_H_

#include "CommandChannelS.h"

namespace OASIS
{
// Forward decl.
class Standard_EINode;

/**
 * @class Tao_CommandChannel_i
 *
 * Implementation of the TAO CommandHandler interface. This allows the
 * DAC to send commands to an EINode using the TAO middleware.
 */
class Tao_CommandChannel_i :
  public POA_OASIS::CommandChannel
{
public:
  /// Default constructor.
  Tao_CommandChannel_i (void);

  /// Destructor.
  virtual ~Tao_CommandChannel_i (void);

  /// Handle a command from the DAC.
  virtual void handle_command (const char * cmd);

  /// Set the command channel's callback einode.
  void set_einode (Standard_EINode * einode);

private:
  /// Pointer to the target einode.
  Standard_EINode * einode_;
};

}

#endif  // !defined _OASIS_TAO_COMMANDCHANNEL_I_H_
