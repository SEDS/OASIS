// $Id: Command_Channel.cpp 1895 2011-09-05 12:00:16Z hillj $

#include "Command_Channel.h"

#if !defined (__OASIS_INLINE__)
#include "Command_Channel.inl"
#endif

namespace OASIS
{
namespace DAC
{

//
// Command_Channel
//
OASIS_INLINE
void Command_Channel::destroy (void)
{
  delete this;
}

}
}
