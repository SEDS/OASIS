// $Id: Tao_CommandChannel_i.cpp 1970 2011-10-03 19:44:11Z hillj $

#include "Tao_CommandChannel_i.h"
#include "oasis/EINode/Standard_EINode.h"

namespace OASIS
{

//
// Tao_CommandChannel_i
//
Tao_CommandChannel_i::Tao_CommandChannel_i (void)
: einode_ (0)
{

}

//
// ~Tao_CommandChannel_i
//
Tao_CommandChannel_i::~Tao_CommandChannel_i (void)
{

}

//
// handle_command
//
void Tao_CommandChannel_i::handle_command (const char * cmd)
{
  if (0 == this->einode_)
    return;

  if (0 != this->einode_->handle_command (cmd))
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to execute command '%s'"),
                cmd));
}

//
// set_einode
//
void Tao_CommandChannel_i::set_einode (Standard_EINode * einode)
{
  this->einode_ = einode;
}

}
