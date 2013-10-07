// $Id: ORB_Server_Task.cpp 1934 2011-09-28 14:56:30Z hillj $

#include "ORB_Server_Task.h"

#if !defined (__OASIS_INLINE__)
#include "ORB_Server_Task.inl"
#endif

namespace OASIS
{

//
// svc
//
int ORB_Server_Task::svc (void)
{
  OASIS_TAO_TRACE ("int ORB_Server_Task::svc (void)");

  try
  {
    // Make sure the ORB is not nil before running the task.
    if (::CORBA::is_nil (this->orb_.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - ORB is nil; cannot run task\n")),
                         -1);

    this->orb_->run ();
    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }

  return -1;
}

}
