// $Id: driver.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "oasis/DataChannel/Latest_Local_Data_Channel.h"
#include "int16.h"
#include "int16Impl.h"

//
// validate_recalled_data
//
bool validate_recalled_data (const ::OASIS::Int16_SoftwareProbeImpl & src,
                             const ::OASIS::Int16_SoftwareProbe & dst)
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
  OASIS::Int16_SoftwareProbeImpl int16_probe;

  // Set the software probe's local data channel.
  OASIS::Latest_Local_Data_Channel channel;
  int16_probe.set_data_channel (&channel);

  int16_probe.init ("--name=int16_probe");
  int16_probe.value (34);

  // Send the data to the channel.
  int16_probe.flush ();

  // Recall the data received on the data channel.
  ::OASIS::Int16_SoftwareProbe dup_probe;
  if (0 != dup_probe.recall (channel.get_data (),
                             channel.get_data_length (),
                             ACE_CDR::BYTE_ORDER_NATIVE))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to recall data\n")),
                       -1);
  }

  if (!validate_recalled_data (int16_probe, dup_probe))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled values are not equal\n")),
                       -1);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - test completed successfully\n")));

  return 0;
}
