// $Id: driver.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "oasis/DataChannel/Latest_Local_Data_Channel.h"
#include "int64.h"
#include "int64Impl.h"

//
// validate_recalled_data
//
bool validate_recalled_data (const ::OASIS::Int64_SoftwareProbeImpl & src,
                             const ::OASIS::Int64_SoftwareProbe & dst)
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
  OASIS::Int64_SoftwareProbeImpl int64_probe;

  // Set the software probe's local data channel.
  OASIS::Latest_Local_Data_Channel channel;
  int64_probe.set_data_channel (&channel);

  int64_probe.value (34);

  // Flush the data to the local channel.
  int64_probe.flush ();

  // Recall the data received on the data channel.
  ::OASIS::Int64_SoftwareProbe dup_probe;
  if (0 != dup_probe.recall (channel.get_data (),
                             channel.get_data_length (),
                             ACE_CDR::BYTE_ORDER_NATIVE))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to recall data\n")),
                       -1);
  }

  // Validate the recalled data.
  if (!::validate_recalled_data (int64_probe, dup_probe))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled value is not equal\n")),
                       -1);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - test completed successfully\n")));

  return 0;
}
