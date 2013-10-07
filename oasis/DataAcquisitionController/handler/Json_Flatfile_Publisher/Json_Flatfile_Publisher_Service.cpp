//$Id $

#include "oasis/probes/Software_Probe.h"
#include "oasis/probes/Software_Probe_Header.h"
#include "oasis/probes/system/processor/ProcessorProbe.h"
#include "oasis/probes/system/memory/MemoryProbe.h"
#include "oasis/DataAcquisitionController/Data_Packet.h"

#include "Json_Flatfile_Publisher_Service.h"

OASIS_DAC_DATA_HANDLER_IMPL (_make_OASIS_DAC_Json_Flatfile_Publisher_Service, OASIS::DAC_Json_Flatfile_Publisher_Service);

namespace OASIS
{
  //
  // DAC_Json_Flatfile_Publisher_Service
  //
  DAC_Json_Flatfile_Publisher_Service::DAC_Json_Flatfile_Publisher_Service (void)
  {

  }

  //
  // ~DAC_Json_Flatfile_Publisher_Service
  //
  DAC_Json_Flatfile_Publisher_Service::~DAC_Json_Flatfile_Publisher_Service (void)
  {
  }

  //
  // init
  //
  /*int DAC_Json_Flatfile_Publisher_Service::init(int argc, char *argv[])
  {
    return 0;
  }*/

  //
  // fini
  //
  int DAC_Json_Flatfile_Publisher_Service::fini (void)
  {
    if (!this->flat_file.is_open())
      this->flat_file.close();
    return 0;
  }

  //
  //handle_data
  //
  int DAC_Json_Flatfile_Publisher_Service
    ::handle_data (const OASIS::DAC::Data_Packet & packet)
  {
    OASIS::Software_Probe_Header probe;

    probe.recall(packet.probe_data (),
                 packet.probe_data_length (),
                 packet.byte_order ());

    ACE_CString probe_name = probe.name_;

    if (probe_name == "ProcessorProbe_SmokeTest")
    {
      OASIS::System::Processor::LinuxProcessorProbe linux_processor_probe;
      linux_processor_probe.recall(packet.probe_data(),
                                   packet.probe_data_length(),
                                   packet.byte_order());

      // Now processor_probe has all the required values to store on file in its
      // member variables.
      if(!this->flat_file.is_open())
      {
        this->flat_file.open("Processor_Info.txt", std::fstream::out | std::fstream::in | std::fstream::trunc);
      }
      this->flat_file<<"{";
      this->flat_file<<"\"idle_time\":"<<linux_processor_probe.idle_time ()<<",";
      this->flat_file<<"\"system_time\":"<<linux_processor_probe.system_time ()<<",";
      this->flat_file<<"\"user_time\":"<<linux_processor_probe.user_time ()<<",";
      this->flat_file<<"\"nice_time\":"<<linux_processor_probe.nice_time ()<<",";
      this->flat_file<<"\"iowait_time\":"<<linux_processor_probe.iowait_time ()<<",";
      this->flat_file<<"\"irq_time\":"<<linux_processor_probe.irq_time ()<<",";
      this->flat_file<<"\"soft_irq_time\":"<<linux_processor_probe.soft_irq_time ();
      this->flat_file<<"}";
      this->flat_file<<std::endl;

      this->flat_file.close();
    }
    else if (probe_name == "MemoryProbe_SmokeTest")
    {
      OASIS::System::Memory::LinuxMemoryProbe linux_memory_probe;
      linux_memory_probe.recall(packet.probe_data(),
                                   packet.probe_data_length(),
                                   packet.byte_order());

      // Now processor_probe has all the required values to store on file in its
      // member variables.
      if(!this->flat_file.is_open())
      {
        this->flat_file.open("Memory_Info.txt", std::fstream::out | std::fstream::in | std::fstream::trunc);
      }
      this->flat_file<<"{";
      this->flat_file<<"\"physical_memory_avail\":"<<linux_memory_probe.physical_memory_avail ()<<",";
      this->flat_file<<"\"physical_memory_total\":"<<linux_memory_probe.physical_memory_total ()<<",";
      this->flat_file<<"\"system_cache\":"<<linux_memory_probe.system_cache ()<<",";
      this->flat_file<<"\"commit_limit\":"<<linux_memory_probe.commit_limit ()<<",";
      this->flat_file<<"\"commit_total\":"<<linux_memory_probe.commit_total ()<<",";
      this->flat_file<<"\"virtual_total\":"<<linux_memory_probe.virtual_total ()<<",";
      this->flat_file<<"\"virtual_used\":"<<linux_memory_probe.virtual_used ()<<",";
      this->flat_file<<"\"buffers\":"<<linux_memory_probe.buffers ()<<",";
      this->flat_file<<"\"swap_cache\":"<<linux_memory_probe.swap_cache ()<<",";
      this->flat_file<<"\"inactive\":"<<linux_memory_probe.inactive ()<<",";
      this->flat_file<<"\"active\":"<<linux_memory_probe.active ()<<",";
      this->flat_file<<"\"high_total\":"<<linux_memory_probe.high_total ()<<",";
      this->flat_file<<"\"high_free\":"<<linux_memory_probe.high_free ()<<",";
      this->flat_file<<"\"low_total\":"<<linux_memory_probe.low_total ()<<",";
      this->flat_file<<"\"low_free\":"<<linux_memory_probe.low_free ()<<",";
      this->flat_file<<"\"swap_total\":"<<linux_memory_probe.swap_total ()<<",";
      this->flat_file<<"\"swap_free\":"<<linux_memory_probe.swap_free ()<<",";
      this->flat_file<<"\"dirty\":"<<linux_memory_probe.dirty ()<<",";
      this->flat_file<<"\"write_back\":"<<linux_memory_probe.write_back ()<<",";
      this->flat_file<<"\"virtual_chunk\":"<<linux_memory_probe.virtual_chunk ();
      this->flat_file<<"}";
      this->flat_file<<std::endl;

      this->flat_file.close();
    }

    return 0;
  }
}
