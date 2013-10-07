// $Id: Command_Channel_Adapter.cpp 1965 2011-10-03 15:05:32Z hillj $

#include "Command_Channel_Adapter.h"

namespace OASIS
{
//
// Tao_Command_Channel_Adapter
//
Tao_Command_Channel_Adapter::
Tao_Command_Channel_Adapter (CommandChannel_ptr channel)
: adaptee_ (CommandChannel::_duplicate (channel))
{

}

//
// ~Tao_Command_Channel_Adapter
//
Tao_Command_Channel_Adapter::~Tao_Command_Channel_Adapter (void)
{

}

//
// reset
//
void Tao_Command_Channel_Adapter::reset (CommandChannel_ptr channel)
{
  this->adaptee_ = CommandChannel::_duplicate (channel);
}

//
// release
//
CommandChannel_ptr Tao_Command_Channel_Adapter::release (void)
{
  return this->adaptee_._retn ();
}

//
// handle_command
//
int Tao_Command_Channel_Adapter::
handle_command (const ACE_CString & command)
{
  if (CORBA::is_nil (this->adaptee_.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - command channel is nil\n")),
                       -1);

  try
  {
    this->adaptee_->handle_command (command.c_str ());
    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }

  return -1;
}

}
