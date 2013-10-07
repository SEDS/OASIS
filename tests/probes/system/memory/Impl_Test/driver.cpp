// $Id: driver.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "oasis/DataChannel/Latest_Local_Data_Channel.h"
#include "oasis/probes/system/memory/MemoryProbe_Impl.h"
#include "oasis/probes/system/memory/MemoryProbe.h"

#include <iostream>

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  // Register the software probe with the EINode.
  OASIS::System::Memory::MemoryProbe_Impl mem_probe;
  mem_probe.init ("--name=MemoryProbe");

  // Set the software probe's local data channel.
  OASIS::Latest_Local_Data_Channel channel;
  mem_probe.set_data_channel (&channel);

  // Get the data and flush
  if (0 != mem_probe.handle_collect_data ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to get memory data\n")),
                       -1);

  if (0 != mem_probe.flush ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to flush memory data\n")),
                       -1);

  // Recall the data received on the data channel.
  OASIS::System::Memory::MemoryProbe dup_probe;
  if (0 != dup_probe.recall (channel.get_data (),
                             channel.get_data_length (),
                             ACE_CDR::BYTE_ORDER_NATIVE))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to recall data\n")),
                       -1);
  }

  // Validate the recalled data.
  if (dup_probe.physical_memory_avail () != mem_probe.physical_memory_avail ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled physical_memory_avail is not equal\n")),
                       -1);

  // Validate the recalled data.
  if (dup_probe.physical_memory_total () != mem_probe.physical_memory_total ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled physical_memory_total is not equal\n")),
                       -1);

#if defined (_WIN32)
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("  physical_memory_avail = %q B\n")
              ACE_TEXT ("  physical_memory_total = %q B\n")
              ACE_TEXT ("  system_cache = %q pages\n")
              ACE_TEXT ("  commit_total = %q pages\n")
              ACE_TEXT ("  commit_limit = %q pages\n")
              ACE_TEXT ("  virtual_total = %q B\n")
              ACE_TEXT ("  virtual_used = %q B\n"),
              mem_probe.physical_memory_avail (),
              mem_probe.physical_memory_total (),
              mem_probe.system_cache (),
              mem_probe.commit_total (),
              mem_probe.commit_limit (),
              mem_probe.virtual_total (),
              mem_probe.virtual_used ()));
#else
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("  physical_memory_avail = %q kB\n")
              ACE_TEXT ("  physical_memory_total = %q kB\n")
              ACE_TEXT ("  system_cache = %q kB\n")
              ACE_TEXT ("  commit_total = %q kB\n")
              ACE_TEXT ("  commit_limit = %q kB\n")
              ACE_TEXT ("  virtual_total = %q kB\n")
              ACE_TEXT ("  virtual_used = %q kB\n")
              ACE_TEXT ("  buffers = %q kB\n")
              ACE_TEXT ("  swap_cache = %q kB\n")
              ACE_TEXT ("  inactive = %q kB\n")
              ACE_TEXT ("  active   = %q kB\n")
              ACE_TEXT ("  high_total = %q kB\n")
              ACE_TEXT ("  high_free = %q kB\n")
              ACE_TEXT ("  low_total = %q kB\n")
              ACE_TEXT ("  low_free = %q kB\n")
              ACE_TEXT ("  swap_total = %q kB\n")
              ACE_TEXT ("  swap_free = %q kB\n")
              ACE_TEXT ("  dirty = %q kB\n")
              ACE_TEXT ("  write_back = %q kB\n")
              ACE_TEXT ("  virtual_chunk = %q kB\n"),
              mem_probe.physical_memory_avail (),
              mem_probe.physical_memory_total (),
              mem_probe.system_cache (),
              mem_probe.commit_total (),
              mem_probe.commit_limit (),
              mem_probe.virtual_total (),
              mem_probe.virtual_used (),
              mem_probe.buffers (),
              mem_probe.swap_cache (),
              mem_probe.inactive (),
              mem_probe.active (),
              mem_probe.high_total (),
              mem_probe.high_free (),
              mem_probe.low_total (),
              mem_probe.low_free (),
              mem_probe.swap_total (),
              mem_probe.swap_free (),
              mem_probe.dirty (),
              mem_probe.write_back (),
              mem_probe.virtual_chunk ()));
#endif

  return 0;
}
