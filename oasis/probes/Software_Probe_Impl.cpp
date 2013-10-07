// $Id: Software_Probe_Impl.cpp 2235 2013-02-06 20:18:09Z dfeiock $

#include "Software_Probe_Impl.h"

#if !defined (__OASIS_INLINE__)
#include "Software_Probe_Impl.inl"
#endif

#include "oasis/DataChannel/Local_Data_Channel.h"
#include "oasis/streams.h"

#include "ace/ARGV.h"
#include "ace/CDR_Stream.h"
#include "ace/Get_Opt.h"
#include "ace/High_Res_Timer.h"

#include <iostream>
#include <sstream>

namespace OASIS
{
//
// Software_Probe_Impl
//
Software_Probe_Impl::Software_Probe_Impl (void)
: seqnum_ (0),
  state_ (0),
  data_channel_ (0),
  task_ (this),
  interval_ (ACE_Time_Value::zero),
  packager_ (0),
  is_init_ (false),
  data_size_ (0),
  dump_ (false)
{

}

//
// set_data_channel
//
void Software_Probe_Impl::
set_data_channel (Local_Data_Channel * channel)
{
  this->data_channel_ = channel;
  this->packager_ = channel->packager ();
  if (!this->packager_->init (this->metadata ().uuid_ ,this->name_, this->data_size_))
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to set instance name\n")));

}

//
// flush
//
int Software_Probe_Impl::flush (void)
{
  if (0 != this->package_data (this->packager_))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to package data\n")),
                       -1);

  // Update the data size in our header
  this->datasize_ = this->packager_->data_size ();

  // Send the data to the EINode.
  return this->send_data (this->packager_);
}

//
// send_data
//
int Software_Probe_Impl::
send_data (Software_Probe_Data_Packager * p)
{
  // Make sure we are connected to a data channel.
  if (0 == this->data_channel_)
    ACE_ERROR_RETURN ((LM_WARNING,
                       ACE_TEXT ("%T (%t) - %M - data channel not set\n")),
                       -1);

  // Get the stream information.
  const char * stream = p->stream ();
  size_t length = p->length ();

  // Send the data packet to the EINode.
  this->data_channel_->send_data (stream, length);

  return 0;
}

//
// activate
//
int Software_Probe_Impl::activate (void)
{
  return this->task_.activate (this->interval_);
}

//
// deactivate
//
int Software_Probe_Impl::deactivate (void)
{
  return this->task_.deactivate ();
}

//
// parse_args
//
int Software_Probe_Impl::parse_args (const char * args)
{
  // Convert the command string into a vector of commands.
  ACE_ARGV_T <char> argv (args);
  const char * optargs = "";

  // Parse the command-line options.
  ACE_Get_Opt get_opt (argv.argc (), argv.argv (), optargs, 0);
  get_opt.long_option ("hertz", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("dump", ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("name", ACE_Get_Opt::ARG_REQUIRED);

  int opt = 0;

  while (EOF != (opt = get_opt ()))
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("hertz", get_opt.long_option ()))
      {
        if (0 != this->handle_hertz_command (get_opt.opt_arg ()))
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("%T (%t) - %M - failed to handle --hertz ")
                      ACE_TEXT ("command\n")));
      }

      else if (0 == ACE_OS::strcmp ("dump", get_opt.long_option ()))
        this->dump_ = true;

      else if (0 == ACE_OS::strcmp ("name", get_opt.long_option ()))
        this->instance_name (get_opt.opt_arg ());

      break;
    }
  }

  return 0;
}

//
// init
//
int Software_Probe_Impl::init (const char * params, const char * name)
{
  // Make sure the probe isn't already initalized
  if (this->is_init_)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - probe is already initalized\n")),
                       -1);

  // Parse the command-line options.
  if (0 != this->parse_args (params))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to parse probe options\n")),
                       -1);
  if (name != 0)
    this->instance_name (name);

  this->is_init_ = true;

  return 0;
}

//
// handle_command
//
void Software_Probe_Impl::handle_command (const char * command)
{
  if (0 != this->parse_args (command))
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to parse command-line arguments\n")));

  if (-1 == this->task_.reschedule (this->interval_))
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to reschedule task\n")));
}

//
// handle_hertz_command
//
int Software_Probe_Impl::handle_hertz_command (const char * args)
{
  // Extract the hertz from the option's argument
  size_t hertz;
  std::istringstream istr (args);
  istr >> hertz;

  if (istr.fail ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to parse hertz value\n")),
                       -1);

  if (hertz > 0)
  {
    // Convert the hertz to milliseconds
    long msec = 1000 / hertz;

    ACE_Time_Value tv;
    tv.msec (msec);

    this->interval_ = tv;
  }
  else
    this->interval_ = ACE_Time_Value::zero;

  return 0;
}

//
// instance_name
//
void Software_Probe_Impl::instance_name (const ACE_CString & name)
{
  // Store the instance name.
  this->name_ = name;

  // Update the instance name in the packaging.
  if (this->packager_ != 0)
  {
    if (!this->packager_->init (this->metadata ().uuid_ ,name, this->data_size_))
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("%T (%t) - %M - failed to set instance name\n")));
  }
}


//
// dump
//
void Software_Probe_Impl::
dump (std::ostream & output) const
{
  output << "Dumping header for probe [name=" << this->name_.c_str () << "]" << std::endl;
  output << "Header contents [probe=" << this->uuid_.to_string ()->c_str () << "; "
    << "timestamp=" << this->last_ts_.sec () << "." << this->last_ts_.usec () << "; "
    << "seqnum=" << this->seqnum_ << "; state=" << this->state_ << ";]" << std::endl;
}

//
// package_data
//
int Software_Probe_Impl::
package_data (Software_Probe_Data_Packager * p)
{
  // Get the current sequence number and update it.
  this->last_ts_ = ACE_High_Res_Timer::gettimeofday_hr ();

  // Update the sequence number.
  ++ this->seqnum_;

  if (this->dump_)
    this->dump (::std::cout);

  p->update (this->last_ts_,
             this->seqnum_,
             this->state_);

  // Finally, reset the packager.
  p->reset ();

  return 0;
}


}
