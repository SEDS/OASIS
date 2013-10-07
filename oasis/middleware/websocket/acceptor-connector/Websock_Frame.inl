// -*- C++ -*-
//
// $Id: Websock_Frame.inl 2230 2013-01-24 14:47:29Z dfeiock $

#include "Websock_Frame.h"
ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE
ACE_Websock_Frame::ACE_Websock_Frame ()
{

}

ACE_INLINE
ACE_Websock_Frame::~ACE_Websock_Frame ()
{
  delete[] payload_;
}

ACE_END_VERSIONED_NAMESPACE_DECL