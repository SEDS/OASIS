// -*- C++ -*-

//=============================================================================
/**
 * @file        Registration_Packet.h
 *
 * $Id: Registration_Packet.h 2211 2012-07-25 12:55:51Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DAC_REGISTRATION_PACKET_H_
#define _OASIS_DAC_REGISTRATION_PACKET_H_

#include <vector>
#include <utility>
#include <memory>
#include "ace/Hash_Map_Manager.h"
#include "boost/shared_ptr.hpp"

#include "oasis/probes/Software_Probe_Metadata.h"

namespace OASIS
{
namespace DAC
{
// Forward decl.
class Command_Channel;

/// Type defintion for the pointer type used for software probe instances
typedef boost::shared_ptr <Software_Probe_Metadata> Software_Probe_Metadata_ptr;

/// Type definition for the collection of software probe instances
typedef ACE_Hash_Map_Manager <std::string,
                              Software_Probe_Metadata_ptr,
                              ACE_Thread_Mutex> Software_Probe_Instances;

/// Type definition for a single software probe instance
typedef Software_Probe_Instances::ENTRY Software_Probe_Instance;

/**
 * @struct Registration_Packet
 *
 * Registration packet for an Embedded Instrumentation (EI) node. This
 * object is constructed by a data channel when is receives registration
 * information from an EI node. It is then passed to the DAC, so it can
 * perform its registration operations. Finally, it is passed to all
 * loaded data handlers so they can perform any registration actions.
 */
struct Registration_Packet
{
  /// Default constructor.
  Registration_Packet (void)
    : command_channel_ (0) { }

  /// UUID of the EI node.
  std::string einode_;

  /// Name of the EI node.
  std::string name_;

  /// List of registered probes. The key in the map is the instance
  /// name of the probe. The value of the metadata associatd with
  /// that probe.
  Software_Probe_Instances probes_;

  /// Pointer to the command channel. This allows the DAC to send
  /// commands back into the system.
  Command_Channel * command_channel_;
};

}
}

#endif  // !defined _OASIS_EINODE_DATA_PACKET_H_
