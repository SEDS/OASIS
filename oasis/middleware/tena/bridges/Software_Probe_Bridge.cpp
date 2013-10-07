// $Id: Software_Probe_Bridge.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "Software_Probe_Bridge.h"

#if !defined (__OASIS_INLINE__)
#include "Software_Probe_Bridge.inl"
#endif

#include "oasis/streams.h"
#include "oasis/probes/Software_Probe_Header.h"

#include "TENA/Time/Impl.h"

namespace OASIS
{

//
// update
//
int Software_Probe_Bridge::
update (PublicationStateUpdater & updater, ACE_InputCDR & input)
{
  OASIS::Software_Probe_Header probe;
  if (0 != probe.recall (input))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to recall software probe data\n")),
                       -1);

  TENA::Time::LocalClassPtr tena_time (
    TENA::Time::create (static_cast < ::TENA::int32 > (probe.last_ts_.sec ()),
                        probe.last_ts_.usec () * 1000));

  updater.set_last_timestamp (tena_time);
  updater.set_state (probe.state_);
  updater.set_sequence_num (probe.seqnum_);

  return 0;
}

}

