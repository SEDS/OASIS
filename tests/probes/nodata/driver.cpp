// $Id: driver.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "oasis/DataChannel/Latest_Local_Data_Channel.h"
#include "nodata.h"
#include "nodataImpl.h"

//
// validate_recalled_data
//
bool validate_recalled_data (const ::OASIS::Software_Probe_Impl & src,
                             const ::OASIS::Software_Probe & dst)
{
  if (src.uuid () != dst.uuid ()
      || src.timestamp () != dst.timestamp ()
      || src.sequence_number () != dst.sequence_number ()
      || src.state () != dst.state ()
      || src.data_size () != dst.data_size ())
   ACE_ERROR_RETURN ((LM_ERROR,
                      ACE_TEXT ("%T (%t) - %M - headers are not equal\n")),
                      false);

  return true;
}

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  try
  {
    // Register the software probe with the EINode.
    Test::NoDataProbeImpl nodata_impl;

    // Set the software probe's local data channel.
    OASIS::Latest_Local_Data_Channel channel;
    nodata_impl.set_data_channel (&channel);

    nodata_impl.init ("--name=nodata-instance");

    if (0 != nodata_impl.flush ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to flush %s probe\n"),
                         nodata_impl.__metadata__.type_info_.c_str ()),
                         1);

    // Recall data that was just sent over the local data channel.
    Test::NoDataProbe p;
    if (0 != p.recall (channel.get_data (),
                       channel.get_data_length (),
                       ACE_CDR::BYTE_ORDER_NATIVE))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to recall data\n")),
                         1);
    }

    // Validate that the generate software probe is able to recall
    // the actual data.
    if (!validate_recalled_data (nodata_impl, p))
     ACE_ERROR_RETURN ((LM_ERROR,
                        ACE_TEXT ("%T (%t) - %M - failed to recall probe's data\n")),
                        1);

    // Recall the data received on the data channel.
    Test::NoDataProbe nodata;
    if (0 != nodata.recall (channel.get_data (),
                            channel.get_data_length (),
                            ACE_CDR::BYTE_ORDER_NATIVE))
    {
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to recall data\n")),
                         1);
    }

    // Validate the recalled data.
    if (!validate_recalled_data (nodata_impl, nodata))
     ACE_ERROR_RETURN ((LM_ERROR,
                        ACE_TEXT ("%T (%t) - %M - failed to recall probe's data\n")),
                        1);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - successfully recalled data\n")));

    return 0;
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }
  catch (...)
  {

  }

  return 1;
}
