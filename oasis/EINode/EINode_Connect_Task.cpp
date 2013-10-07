//  $Id:

#include "EINode_Connect_Task.h"
#include "Standard_EINode.h"
#include "oasis/DataChannel/Data_Channel.h"

#include "ace/Reactor.h"
#include "ace/CORBA_macros.h"

namespace OASIS
{

//
// EINode_Connect_Task
//
EINode_Connect_Task::
EINode_Connect_Task (Standard_EINode * einode)
: einode_ (einode),
  channel_ (0),
  is_active_ (false),
  timer_id_ (-1)
{
  ACE_Reactor * reactor = 0;

  ACE_NEW_THROW_EX (reactor,
                    ACE_Reactor (),
                    ACE_bad_alloc ());

  this->reactor (reactor);
}

//
// ~EINode_Connect_Task
//
EINode_Connect_Task::~EINode_Connect_Task (void)
{
  std::auto_ptr <ACE_Reactor> auto_clean (this->reactor ());
  this->reactor (0);
}

//
// set_data_channel
//
void EINode_Connect_Task::set_data_channel (Data_Channel * channel)
{
  this->channel_ = channel;
}

//
// activate
//
int EINode_Connect_Task::activate (const ACE_Time_Value & interval)
{
  if (this->is_active_)
    return this->timer_id_;

  // Activate the task.
  if (0 != ACE_Task_Base::activate ())
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to activate ")
                ACE_TEXT ("connect task\n")));

  // Schedule the timer for the heartbeat.
  this->timer_id_ =
    this->reactor ()->schedule_timer (this,
                                      0,
                                      ACE_Time_Value::zero,
                                      interval);

  if (this->timer_id_ == -1)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to activate ")
                ACE_TEXT ("connect task\n")));

  this->is_active_ = true;
  return this->timer_id_;
}

//
// deactivate
//
int EINode_Connect_Task::deactivate (void)
{
  if (!this->is_active_)
    return 0;

  // Toggle the active flag.
  this->is_active_ = false;

  // Wakeup the thread and wait for it to exit.
  this->reactor ()->notify (this);
  this->wait ();

  if (this->timer_id_ != -1)
  {
    // Finally, cancel the timer.
    this->reactor ()->cancel_timer (this->timer_id_);
    this->timer_id_ = -1;
  }

  return 0;
}

//
// svc
//
int EINode_Connect_Task::svc (void)
{
  try
  {
    // Set the reactor's owner.
    this->reactor ()->owner (ACE_OS::thr_self ());

    // Keep processing events while we are active.
    while (this->is_active_)
      this->reactor ()->handle_events ();

    return 0;
  }
  catch (...)
  {
    return -1;
  }
}

//
// handle_timeout
//
int EINode_Connect_Task::
handle_timeout (const ACE_Time_Value & , const void * )
{
  if (0 == this->einode_ || 0 == this->channel_)
    return 0;

  try
  {
    // Signal the EINode to try to connect
    this->einode_->handle_connect ();

    // We can deactivate the task since the connection succeeded.
    this->deactivate ();
  }
  catch (const ::OASIS::Connect_Error & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }

  return 0;
}

}
