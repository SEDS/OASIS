// -*- C++ -*-

//=============================================================================
/**
 * @file        Data_Streams_T.h
 *
 * $Id: Data_Streams_T.h 1896 2011-09-07 14:56:19Z hillj $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_SOFTWARE_PROBE_DATA_STREAMS_T_H_
#define _OASIS_SOFTWARE_PROBE_DATA_STREAMS_T_H_

#include "ace/CDR_Stream.h"
#include "Data_Types.h"

template <typename T>
bool operator >> (ACE_InputCDR & in, std::vector <T> & values);

template <typename T>
bool operator << (ACE_OutputCDR & out, const std::vector <T> & values);

#include "Data_Streams_T.cpp"

#endif  // !defined _OASIS_SOFTWARE_PROBE_DATA_STREAMS_T_H_
