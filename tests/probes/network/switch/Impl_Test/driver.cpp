// $Id: driver.cpp 2214 2012-08-10 15:00:08Z dfeiock $

#include "oasis/DataChannel/Latest_Local_Data_Channel.h"
#include "oasis/probes/network/switch/SwitchProbe_Impl.h"
#include "oasis/probes/network/switch/SwitchProbe.h"

#include <iostream>

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  // Register the software probe with the EINode.
  OASIS::Network::Switch::SwitchProbe_Impl probe;
  probe.init ("--name=SwitchProbe --host=192.168.2.254 --community=public --port=1 --port=2");

  // Set the software probe's local data channel.
  OASIS::Latest_Local_Data_Channel channel;
  probe.set_data_channel (&channel);

  // Get the data and flush
  if (0 != probe.handle_collect_data ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to get probe data\n")),
                       -1);

  if (0 != probe.flush ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to flush probe data\n")),
                       -1);

  // Recall the data received on the data channel.
  OASIS::Network::Switch::SwitchProbe dup_probe;
  if (0 != dup_probe.recall (channel.get_data (),
                             channel.get_data_length (),
                             ACE_CDR::BYTE_ORDER_NATIVE))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to recall data\n")),
                       -1);
  }

  // Validate the recalled data.
  if (dup_probe.uptime () != probe.uptime ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled value is not equal\n")),
                       -1);

  // Validate the recalled data.
  if (dup_probe.ports ()[0].description != probe.ports ()[0].description)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled value is not equal\n")),
                       -1);

  std::cout << "Probe Values:" << std::endl;
  probe.dump (std::cout);

  return 0;
}
