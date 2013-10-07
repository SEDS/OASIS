// -*- C++ -*-

//=============================================================================
/**
 * @file        Unregistration_Packet.h
 *
 * $Id: Unregistration_Packet.h 2068 2011-11-30 21:13:36Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DAC_UNREGISTRATION_PACKET_H_
#define _OASIS_DAC_UNREGISTRATION_PACKET_H_

#include <vector>
#include <utility>

#include "oasis/probes/Software_Probe_Metadata.h"

namespace OASIS
{
namespace DAC
{
// Forward decl.
class Command_Channel;

/// Type definition of a software probe instance.
typedef
  std::pair <ACE_CString, ACE_CString>
  Unregister_Software_Probe_Instance;

/// Type definition for the collection of software probe instancs.
typedef std::vector <Unregister_Software_Probe_Instance> Unregister_Software_Probe_Instances;

/**
 * @struct Unregistration_Packet
 *
 * Unregistration packet for an Embedded Instrumentation (EI) node. This
 * object is constructed by the dac when it receives unregistration
 * information from an EI node. Finally, it is passed to all
 * loaded data handlers so they can perform any unregistration actions.
 */
struct Unregistration_Packet
{
  /// Default constructor.
  Unregistration_Packet (void)
    : command_channel_ (0) { }

  /// UUID of the EI node.
  ACE_Utils::UUID uuid_;

  /// Name of the EI node.
  ACE_CString name_;

  /// List of probes belonging to the einode. The key in the pair is the instance
  /// name of the probe. The value is the probe type.
  std::vector <Unregister_Software_Probe_Instance> probes_;

  /// Pointer to the command channel. This allows handlers to send
  /// commands back to the einode if needed.
  Command_Channel * command_channel_;
};

}
}

#endif  // !defined _OASIS_EINODE_DATA_PACKET_H_
