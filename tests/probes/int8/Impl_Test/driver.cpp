// $Id: driver.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "oasis/DataChannel/Latest_Local_Data_Channel.h"
#include "../../Software_Probe_Test_Task.h"
#include "int8.h"
#include "int8Impl.h"

//
// validate_recalled_data
//
bool validate_recalled_data (const ::OASIS::Int8_SoftwareProbeImpl & src,
                             const ::OASIS::Int8_SoftwareProbe & dst)
{
  if (src.uuid () != dst.uuid ()
      || src.timestamp () != dst.timestamp ()
      || src.sequence_number () != dst.sequence_number ()
      || src.state () != dst.state ()
      || src.data_size () != dst.data_size ())
   ACE_ERROR_RETURN ((LM_ERROR,
                      ACE_TEXT ("%T (%t) - %M - headers are not equal\n")),
                      false);

  if (src.value () != dst.value ())
   ACE_ERROR_RETURN ((LM_ERROR,
                      ACE_TEXT ("%T (%t) - %M - failed to recall datasize\n")),
                      false);

  return true;
}

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  // Register the software probe with the EINode.
  OASIS::Int8_SoftwareProbeImpl int8_probe;

  // Set the software probe's local data channel.
  OASIS::Latest_Local_Data_Channel local_channel;
  int8_probe.set_data_channel (&local_channel);

  int8_probe.value (34);

  // Flush data to the channel.
  int8_probe.flush ();

  // Recall the data received on the data channel.
  OASIS::Int8_SoftwareProbe dup_probe;
  if (0 != dup_probe.recall (local_channel.get_data (),
                             local_channel.get_data_length (),
                             ACE_CDR::BYTE_ORDER_NATIVE))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to recall data\n")),
                       -1);
  }

  // Validate the recalled data.
  if (!::validate_recalled_data (int8_probe, dup_probe))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled value is not equal\n")),
                       -1);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - test completed successfully\n")));

  return 0;
}
