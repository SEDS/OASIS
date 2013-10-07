// $Id: Websock_Acceptor_Task.cpp 2230 2013-01-24 14:47:29Z dfeiock $

#include "ace/Log_Msg.h"

#include "Websock_Acceptor_Task.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

//
// Constructor
//
ACE_Websock_Acceptor_Task::ACE_Websock_Acceptor_Task (ACE_Reactor *reactor)
{
  //ACE_ERROR((LM_ERROR,
  //           ACE_TEXT ("%T (%t) - %M - ACE_Websock_Acceptor_Task::ACE_Websock_Acceptor_Task()\n")));
  this->reactor (reactor);
}

//
// svc()
//
int ACE_Websock_Acceptor_Task::svc (void)
{
  this->reactor ()->owner (ACE_OS::thr_self ());

  if (0 != this->reactor ()->run_reactor_event_loop())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to start event loop\n")),
                       -1);

  return 0;
}

ACE_END_VERSIONED_NAMESPACE_DECL