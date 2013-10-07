// $Id: Subscriber_Task.cpp 2095 2012-01-05 15:51:11Z dfeiock $

#include "Subscriber_Task.h"

#if !defined (__OASIS_INLINE__)
#include "Subscriber_Task.inl"
#endif

#include "TENA/Middleware/Session.h"

namespace OASIS
{

//
// svc
//
int Tena_Subscriber_Task::svc (void)
{
  try
  {
    // Right now, we keep processing callbacks while the session is
    // valid. The delay between callbacks is predetermined. In the
    // future, it will be possible to configure the delay between
    // callbacks.
    while (this->session_.isValid ())
      this->session_->evokeMultipleCallbacks (1000 * 1000);

    return 0;
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - unknown exception\n")));
  }

  return -1;
}

}
