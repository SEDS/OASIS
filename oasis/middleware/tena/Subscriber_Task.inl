// $Id: Subscriber_Task.inl 1862 2011-08-19 17:07:25Z hillj $

namespace OASIS
{
//
// Tena_Subscriber_Task
//
OASIS_INLINE
Tena_Subscriber_Task::Tena_Subscriber_Task (void)
{

}

//
// Tena_Subscriber_Task
//
OASIS_INLINE
Tena_Subscriber_Task::Tena_Subscriber_Task (TENA::Middleware::SessionPtr session)
: session_ (session)
{

}

//
// Tena_Subscriber_Task
//
OASIS_INLINE
Tena_Subscriber_Task::~Tena_Subscriber_Task (void)
{

}

//
// Tena_Subscriber_Task
//
OASIS_INLINE
int Tena_Subscriber_Task::reset (TENA::Middleware::SessionPtr session)
{
  this->session_ = session;
  return 0;
}

}
