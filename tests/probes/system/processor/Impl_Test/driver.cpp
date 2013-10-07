// $Id: driver.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "oasis/DataChannel/Latest_Local_Data_Channel.h"
#include "oasis/probes/system/processor/ProcessorProbe_Impl.h"
#include "oasis/probes/system/processor/ProcessorProbe.h"

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  // Register the software probe with the EINode.
  OASIS::System::Processor::ProcessorProbe_Impl Processor_probe;
  Processor_probe.init ("--name=Processor_probe --dump");

  // Set the software probe's local data channel.
  OASIS::Latest_Local_Data_Channel channel;
  Processor_probe.set_data_channel (&channel);

  // Get the data and flush
  if (0 != Processor_probe.handle_collect_data ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - probe impl failed to collect data\n")),
                       -1);

  Processor_probe.flush ();


  // Recall the data received on the data channel.
  OASIS::System::Processor::LinuxProcessorProbe dup_probe;

  std::cout << dup_probe.instance_name ();

  if (0 != dup_probe.recall (channel.get_data (),
                             channel.get_data_length (),
                             (int)ACE_CDR::BYTE_ORDER_NATIVE))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to recall data\n")),
                       -1);
  }

  // Validate the recalled data.
  if (dup_probe.user_time () != Processor_probe.user_time ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled value is not equal\n")),
                       -1);

  // Validate the recalled data.
  if (dup_probe.system_time () != Processor_probe.system_time ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled value is not equal\n")),
                       -1);

  // Validate the recalled data.
  if (dup_probe.idle_time () != Processor_probe.idle_time ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled value is not equal\n")),
                       -1);

  std::cout << "dupe probe:" << std::endl;
  dup_probe.dump (std::cout);
  std::cout << "end dupe probe" << std::endl;
#if defined (_WIN32)
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("  idle_time = %q\n")
              ACE_TEXT ("  system_time = %q\n")
              ACE_TEXT ("  user_time = %q\n"),
              Processor_probe.idle_time (),
              Processor_probe.system_time (),
              Processor_probe.user_time ()));
#else
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("  idle_time = %q\n")
              ACE_TEXT ("  system_time = %q\n")
              ACE_TEXT ("  user_time = %q\n")
              ACE_TEXT ("  nice_time = %q\n")
              ACE_TEXT ("  iowait_time = %q\n")
              ACE_TEXT ("  irq_time = %q\n")
              ACE_TEXT ("  soft_irq_time = %q\n"),
              Processor_probe.idle_time (),
              Processor_probe.system_time (),
              Processor_probe.user_time (),
              Processor_probe.nice_time (),
              Processor_probe.iowait_time (),
              Processor_probe.irq_time (),
              Processor_probe.soft_irq_time ()));
#endif

  return 0;
}
