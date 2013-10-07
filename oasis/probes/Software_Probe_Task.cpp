// $Id: Software_Probe_Task.cpp 2045 2011-11-11 19:15:52Z dfeiock $

#include "Software_Probe_Task.h"
#include "Software_Probe_Impl.h"
#include "ace/Reactor.h"
#include "ace/CORBA_macros.h"

namespace OASIS
{

//
// Software_Probe_Task
//
Software_Probe_Task::
Software_Probe_Task (Software_Probe_Impl * probe)
: probe_ (probe),
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
// ~Software_Probe_Task
//
Software_Probe_Task::~Software_Probe_Task (void)
{
  ACE_Reactor * reactor = this->reactor ();
  this->reactor (0);

  // Delete the reactor.
  delete reactor;
}

//
// activate
//
int Software_Probe_Task::activate (const ACE_Time_Value & interval)
{
  if (this->is_active_)
    return this->timer_id_;

  // Activate the task.
  this->is_active_ = true;
  if (0 != ACE_Task_Base::activate ())
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to activate ")
                ACE_TEXT ("publication task\n")));

  // Schedule the timer for the heartbeat.
  this->timer_id_ = this->reactor ()->schedule_timer (this,
                                                      0,
                                                      ACE_Time_Value::zero,
                                                      interval);

  if (this->timer_id_ == -1)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to activate ")
                ACE_TEXT ("publication task\n")));

  return this->timer_id_;
}

//
// deactivate
//
int Software_Probe_Task::deactivate (void)
{
  if (!this->is_active_)
    return 0;

  // Toggle the active flag.
  this->is_active_ = false;

  // Wakeup the thread and wait for it to exit.
  this->reactor ()->notify (this);
  this->wait ();

  // Finally, cancel the timer.
  if (this->timer_id_ != -1)
  {
    this->reactor ()->cancel_timer (this->timer_id_);
    this->timer_id_ = -1;
  }

  return 0;
}

//
// reschedule
//
int Software_Probe_Task::reschedule (const ACE_Time_Value & interval)
{
  if (this->is_active_)
    return this->reactor ()->reset_timer_interval (this->timer_id_, interval);

  return 0;
}

//
// handle_timeout
//
int Software_Probe_Task::
handle_timeout (const ACE_Time_Value & , const void * )
{
  // There is no need to continue if there is no probe associated
  // with this task.
  if (0 == this->probe_)
    return 0;

  // Since this is an active object, we should signal the probe
  // to collect some new data, if applicable.
  if (0 != this->probe_->handle_collect_data ())
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to collect new probe ")
                ACE_TEXT ("data [type=%s; uuid=%s]\n"),
                this->probe_->metadata ().type_info_.c_str (),
                this->probe_->metadata ().uuid_.to_string ()->c_str ()));

  /// @note Should we return an error if the data collection
  ///       failed? Or, should we just flush the old data?

  if (0 != this->probe_->flush ())
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to flush probe ")
                ACE_TEXT ("data [type=%s; uuid=%s]\n"),
                this->probe_->metadata ().type_info_.c_str (),
                this->probe_->metadata ().uuid_.to_string ()->c_str ()));

  return 0;
}

//
// svc
//
int Software_Probe_Task::svc (void)
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

}
