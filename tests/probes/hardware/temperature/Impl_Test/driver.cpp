// $Id: driver.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "oasis/DataChannel/Latest_Local_Data_Channel.h"
#include "oasis/probes/hardware/temperature/Analog_TemperatureProbe_Impl.h"
#include "oasis/probes/hardware/temperature/TemperatureProbe.h"

#include <iostream>

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  // Register the software probe with the EINode.
  OASIS::HardwareProbes::Temperature::AnalogTemperatureProbe_Impl probe;

  // Set the software probe's local data channel.
  OASIS::Latest_Local_Data_Channel channel;
  probe.set_data_channel (&channel);

  // Init the probe
  if (0 != probe.init (argv[1]))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to init temperature probe\n")),
                       -1);

  // Get the data and flush
  if (0 != probe.handle_collect_data ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to get temperature data\n")),
                       -1);

  if (0 != probe.flush ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to flush temperature data\n")),
                       -1);

  // Recall the data received on the data channel.
  OASIS::HardwareProbes::TemperatureProbe dup_probe;
  if (0 != dup_probe.recall (channel.get_data (),
                             channel.get_data_length (),
                             ACE_CDR::BYTE_ORDER_NATIVE))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to recall data\n")),
                       -1);
  }

  // Validate the recalled data.
  if (dup_probe.temperatureCelcius () != probe.temperatureCelcius ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled temperatureCelcius is not equal\n")),
                       -1);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Temperature is %0.2f\n"),
              probe.temperatureCelcius ()));

  return 0;
}
