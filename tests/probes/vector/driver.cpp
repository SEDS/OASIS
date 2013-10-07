// $Id: driver.cpp 2213 2012-08-01 14:05:58Z dfeiock $

#include "oasis/DataChannel/Latest_Local_Data_Channel.h"
#include "vector.h"
#include "vectorImpl.h"

//
// validate_recalled_data
//
bool validate_recalled_data (const ::OASIS::Int16_Vector_ProbeImpl & src,
                             const ::OASIS::Int16_Vector_Probe & dst)
{
  if (src.uuid () != dst.uuid ()
      || src.timestamp () != dst.timestamp ()
      || src.sequence_number () != dst.sequence_number ()
      || src.state () != dst.state ()
      || src.data_size () != dst.data_size ())
   ACE_ERROR_RETURN ((LM_ERROR,
                      ACE_TEXT ("%T (%t) - %M - headers are not equal\n")),
                      false);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - original vector size = %d; ")
              ACE_TEXT ("duplicate vector size = %d\n"),
              src.value ().size (),
              dst.value ().size ()));

  if (src.value () != dst.value ())
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - duplicate vector values are ")
                       ACE_TEXT ("not equal to orginal vector values\n")),
                       false);
  }
  else
  {
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - duplicate vector values are ")
                ACE_TEXT ("equal to orginal vector values\n")));
  }

  return true;
}

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  // Register the software probe with the EINode.
  OASIS::Int16_Vector_ProbeImpl probe_impl;
  probe_impl.init ("--name=VectorTest");

  // Set the software probe's local data channel.
  OASIS::Latest_Local_Data_Channel channel;
  probe_impl.set_data_channel (&channel);

  static const size_t element_count = 10;
  probe_impl.value ().resize (element_count);

  for (size_t i = 0; i < element_count; ++ i)
    probe_impl.value ()[i] = i;

  // Send the data to the channel.
  probe_impl.flush ();

  // Recall the data received on the data channel.
  ::OASIS::Int16_Vector_Probe dup_probe;
  if (0 != dup_probe.recall (channel.get_data (),
                             channel.get_data_length (),
                             ACE_CDR::BYTE_ORDER_NATIVE))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to recall data\n")),
                       -1);
  }

  if (!::validate_recalled_data (probe_impl, dup_probe))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled values are not equal\n")),
                       -1);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - test completed successfully\n")));

  return 0;
}
