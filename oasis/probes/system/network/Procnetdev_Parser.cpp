// $Id: Procnetdev_Parser.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "Procnetdev_Parser.h"
#include "NetworkProbe.h"
#include <fstream>
#include <sstream>
#include "ace/OS.h"

namespace OASIS
{
namespace System
{
namespace Network
{
  //
  // Procnetdev_Parser
  //
  Procnetdev_Parser::Procnetdev_Parser (void)
  {

  }

  //
  // Procnetdev_Parser
  //
  Procnetdev_Parser::~Procnetdev_Parser (void)
  {

  }

  //
  // read_data
  //
  bool Procnetdev_Parser::read_data (LinuxNetworkProbeImpl * probe)
  {
    // Check that the nic is set
    ACE_CString probenic = probe->nic () + ":";
    if (probenic.length () == 1)
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - attempted to get network statistics ")
                         ACE_TEXT ("without specifying a nic\n")),
                         false);

    // Open /proc/stat for reading.
    std::ifstream file;
    file.open (ACE_TEXT ("/proc/net/dev"));

    if (!file.is_open ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to open /proc/net/dev\n")),
                         false);

    // Find metrics
    std::string line;
    std::string procstatnic;
    std::istringstream values;

    while (0 != ACE_OS::strcmp (procstatnic.c_str (), probenic.c_str ()))
    {
      if (file.eof ())
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%T (%t) - %M - Unable to find nic %s in ")
                           ACE_TEXT ("/proc/net/dev\n"),
                           probenic.c_str ()),
                           false);
      std::getline (file, line);
      values.str (line);
      values >> procstatnic;
    }

    // Populate metrics
    ACE_UINT64 metric;
    values >> metric;
    probe->recv_bytes (metric);
    values >> metric;
    probe->recv_packets (metric);
    values >> metric;
    probe->recv_errors (metric);
    values >> metric;
    probe->recv_drop (metric);
    values >> metric;
    probe->recv_fifo (metric);
    values >> metric;
    probe->recv_frames (metric);
    values >> metric;
    probe->recv_compressed (metric);
    values >> metric;
    probe->recv_multicast (metric);
    values >> metric;
    probe->sent_bytes (metric);
    values >> metric;
    probe->sent_packets (metric);
    values >> metric;
    probe->sent_errors (metric);
    values >> metric;
    probe->sent_drop (metric);
    values >> metric;
    probe->sent_fifo (metric);
    values >> metric;
    probe->sent_collision (metric);
    values >> metric;
    probe->sent_carrier (metric);
    values >> metric;
    probe->sent_compressed (metric);

    return true;
  }
}
}
}
