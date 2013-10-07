// $Id: ORB_Server_Task.inl 1934 2011-09-28 14:56:30Z hillj $

namespace OASIS
{

//
// ORB_Server_Task
//
OASIS_INLINE
ORB_Server_Task::ORB_Server_Task (::CORBA::ORB_ptr orb)
: orb_ (::CORBA::ORB::_duplicate (orb))
{
  OASIS_TAO_TRACE ("ORB_Server_Task::ORB_Server_Task (::CORBA::ORB_ptr)");
}

//
// ORB_Server_Task
//
OASIS_INLINE
ORB_Server_Task::~ORB_Server_Task (void)
{
  OASIS_TAO_TRACE ("ORB_Server_Task::~ORB_Server_Task (void)");
}

//
// ORB_Server_Task
//
OASIS_INLINE
int ORB_Server_Task::reset (CORBA::ORB_ptr orb)
{
  OASIS_TAO_TRACE ("int ORB_Server_Task::reset (CORBA::ORB_ptr)");

  this->orb_ = ::CORBA::ORB::_duplicate (orb);
  return 0;
}

}
