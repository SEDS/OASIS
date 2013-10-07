/* -*- C++ -*- */

//=============================================================================
/**
*  @file    Websoc_Acceptor_Task.h
*
*  $Id: Websock_Acceptor_Task.h 2230 2013-01-24 14:47:29Z dfeiock $
*
*  @author Darshan G. Puranik<dpuranik@iupui.edu>
*/
//=============================================================================

#ifndef WEBSOCK_ACCEPTOR_TASK_H
#define WEBSOCK_ACCEPTOR_TASK_H

#include "ace/pre.h"

#if !defined(ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/Task.h"
#include "ace/Log_Msg.h"
#include "ace/Reactor.h"
#include "Websock_Acceptor_Connector_export.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
* @class ACE_Websock_Acceptor_Task
*
* @brief
*/
class OASIS_WEBSOCK_ACCEPTOR_CONNECTOR_Export ACE_Websock_Acceptor_Task :
public ACE_Task_Base
{
public:
  /// initializing constructor
  ACE_Websock_Acceptor_Task (ACE_Reactor *reactor);

  /// Thread entry point
  int svc (void);
};

ACE_END_VERSIONED_NAMESPACE_DECL

#include "ace/post.h"
#endif //WEBSOCK_ACCEPTOR_TASK_H
