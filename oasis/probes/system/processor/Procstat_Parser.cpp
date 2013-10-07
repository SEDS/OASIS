// $Id: Procstat_Parser.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "Procstat_Parser.h"

#include "ProcessorProbeImpl.h"
#include <fstream>
#include <sstream>

namespace OASIS
{
namespace System
{
namespace Processor
{
  //
  // Procstat_Parser
  //
  Procstat_Parser::Procstat_Parser (void)
  {

  }

  //
  // Procstat_Parser
  //
  Procstat_Parser::~Procstat_Parser (void)
  {

  }

  //
  // read_data
  //
  bool Procstat_Parser::read_data (LinuxProcessorProbeImpl * probe)
  {

    // Open /proc/stat for reading.
    std::ifstream file;
    file.open (ACE_TEXT ("/proc/stat"));

    if (!file.is_open ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to open /proc/stat\n")),
                        false);

    // Read the first line
    std::string line;
    std::getline (file, line);
    std::istringstream values (line);

    // Parse the first line
    std::string cpu_label;
    values >> cpu_label;
    ACE_UINT64 metric;

    values >> metric;
    probe->user_time (metric);
    values >> metric;
    probe->nice_time (metric);
    values >> metric;
    probe->system_time (metric);
    values >> metric;
    probe->idle_time (metric);
    values >> metric;
    probe->iowait_time (metric);
    values >> metric;
    probe->irq_time (metric);
    values >> metric;
    probe->soft_irq_time (metric);

    return true;
  }
}
}
}
