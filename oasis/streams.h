// -*- C++ -*-

//=============================================================================
/**
 * @file        streams.h
 */
//=============================================================================

#ifndef _EISA_STREAMS_H_
#define _EISA_STREAMS_H_

#include "OASIS_export.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

// Forward decl.
class ACE_Time_Value;

// Forward decl.
class ACE_InputCDR;

// Forward decl.
class ACE_OutputCDR;

namespace ACE_Utils
{
  // Forward decl.
  class UUID;
}

///////////////////////////////////////////////////////////////////////////////
// insertion operators

OASIS_Export
bool operator <<= (ACE_OutputCDR & output, const ACE_Utils::UUID &);

OASIS_Export
bool operator <<= (ACE_OutputCDR & output, const ACE_Time_Value & tv);

///////////////////////////////////////////////////////////////////////////////
// extraction operators

OASIS_Export
bool operator >>= (ACE_InputCDR & input, ACE_Utils::UUID & uuid);

OASIS_Export
bool operator >>= (ACE_InputCDR & input, ACE_Time_Value & tv);

ACE_END_VERSIONED_NAMESPACE_DECL

#endif  // !defined _EISA_STREAMS_H_
