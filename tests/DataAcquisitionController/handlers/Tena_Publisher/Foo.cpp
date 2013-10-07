// $Id$

#include "Foo.h"
#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Data_Preparer.h"
#include "oasis/probes/Data_Streams_T.h"

namespace OASIS
{

  // 
  // Foo::__metadata__
  // 
  const Foo::METADATA_TYPE Foo::__metadata__;

  // 
  // Foo::metadata
  // 
  const Foo::METADATA_TYPE & Foo::metadata (void) const 
  {
    return ::OASIS::Foo::__metadata__;
  }

  // 
  // Foo
  // 
  Foo::Foo (void) 
  {
  }

  // 
  // ~Foo
  // 
  Foo::~Foo (void) 
  {
  }

  // 
  // recall
  // 
  int Foo::
  recall (const char * data, size_t length, int byte_order) 
  {
    ::OASIS::Software_Probe_Data_Preparer prep (data, length);
    ACE_InputCDR input (prep.message_block (), byte_order);
    return ::OASIS::Foo::recall (input);
  }


  // 
  // recall
  // 
  int Foo::recall (ACE_InputCDR & in) 
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
  void Foo::dump (std::ostream & output) 
  {
    ::OASIS::Software_Probe::dump (output);
  }
}

