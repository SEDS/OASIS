// $Id$

#include "Dummy_Probe.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/probes/Data_Streams_T.h"


// 
// Dummy_Probe::__metadata__
// 
const Dummy_Probe::METADATA_TYPE Dummy_Probe::__metadata__;

// 
// Dummy_Probe::metadata
// 
const Dummy_Probe::METADATA_TYPE & Dummy_Probe::metadata (void) const 
{
  return ::Dummy_Probe::__metadata__;
}

// 
// Dummy_Probe
// 
Dummy_Probe::Dummy_Probe (void) 
{
}

// 
// ~Dummy_Probe
// 
Dummy_Probe::~Dummy_Probe (void) 
{
}

// 
// recall
// 
int Dummy_Probe::
recall (const char * data, size_t length, int byte_order) 
{
  ::OASIS::Software_Probe_Data_Preparer prep (data, length);
  ACE_InputCDR input (prep.message_block (), byte_order);
  return ::Dummy_Probe::recall (input);
}


// 
// recall
// 
int Dummy_Probe::recall (ACE_InputCDR & in) 
{
  if (0 != ::OASIS::Software_Probe::recall (in))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to recall ")
                       ACE_TEXT ("::OASIS::Software_Probe data\n")),
                      -1);


  return 0;
}

// 
// dump
// 
void Dummy_Probe::dump (std::ostream & output) 
{
  ::OASIS::Software_Probe::dump (output);
}

