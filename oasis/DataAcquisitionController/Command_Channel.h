// -*- C++ -*-

//=============================================================================
/**
 *  @file       Command_Channel.h
 *
 *  $Id: Command_Channel.h 1895 2011-09-05 12:00:16Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#include "ace/SString.h"

#include "oasis/config.h"
#include "DAC_Core_export.h"


namespace OASIS
{
namespace DAC
{
/**
 * @class Command_Channel
 *
 * Base class for all command channels that plug into the DAC. The
 * target data channel is responsible for creating a concrete command
 * channel when it registers a software probe. This way, the DAC knows
 * what command channel corresponds with a given EINode.
 *
 * The actual implementation of the command channel is left up to the
 * developer. This means the developer can choose any protocol for
 * sending a command to an EINode.
 */
class OASIS_DAC_CORE_Export Command_Channel
{
protected:
  /// Default constructor.
  Command_Channel (void);

public:
  /// Destructor.
  virtual ~Command_Channel (void);

  /**
   * Handle the command. The command is packaged in the format
   * <probe> <command> where <probe> is the target probe of the command
   * and <command> is the command to execute.
   */
  virtual int handle_command (const ACE_CString & cmd) = 0;

  /// Destroy the channel.
  virtual void destroy (void);
};

}
}

#if defined (__OASIS_INLINE__)
#include "Command_Channel.inl"
#endif
