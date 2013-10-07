// $Id: DataChannel_i.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "DataChannel_i.h"
#include "Command_Channel_Adapter.h"
#include "Tao_Data_Packet.h"


#include "oasis/middleware/tao/UUID.h"
#include "oasis/probes/Software_Probe_Metadata.h"
#include "oasis/DataAcquisitionController/Execution_Context.h"

/**
 * @struct copy_software_probe_t
 */
struct copy_software_probe_t
{
  //
  // copy_software_probe_t
  //
  copy_software_probe_t (OASIS::DAC::Software_Probe_Instances & probes,
                         OASIS::Metadata_Registry & registry)
    : probes_ (probes),
      registry_ (registry)
  {

  }

  //
  // operator ()
  //
  void operator () (const OASIS::SoftwareProbeEntry & entry)
  {
    OASIS::DAC::Software_Probe_Metadata_ptr metadata;

    // Get the metadata object from the registry if possible
    if (0 != this->registry_.find (entry.metadata.type.in (), metadata))
    {
      // Did not find the metadata in the registry, create it
      ACE_Utils::UUID uuid;
      entry.metadata.uuid >>= uuid;

      metadata.reset (
        new OASIS::Software_Probe_Metadata (uuid.to_string ()->c_str (),
                                            entry.metadata.type.in (),
                                            entry.metadata.version_major,
                                            entry.metadata.version_minor,
                                            entry.metadata.schema.in ()));

      // Add the metadata to the registry
      this->registry_.bind (entry.metadata.type.in (), metadata);
    }

    this->probes_.bind (entry.name.in (), metadata);
  }

private:
  OASIS::DAC::Software_Probe_Instances & probes_;
  OASIS::Metadata_Registry & registry_;
};

namespace OASIS
{

//
// Tao_DataChannel_i
//
Tao_DataChannel_i::Tao_DataChannel_i (void)
{

}

//
// ~Tao_DataChannel_i
//
Tao_DataChannel_i::~Tao_DataChannel_i (void)
{

}

//
// send_data
//
void Tao_DataChannel_i::send_data (const DataPacket & packet)
{
  Tao_Data_Packet p (packet);

  // Get the DAC.  Using the singleton has better performance
  // than storing an Execution_Context pointer.
  using OASIS::DAC::EXECUTION_CONTEXT;
  int retval = EXECUTION_CONTEXT::instance ()->handle_data (p);

  if (0 != retval)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - handle_data () had %d error(s)\n"),
                retval));
}

//
// register_einode
//
void Tao_DataChannel_i::
register_einode (const EINodeRegistration & einode_reg)
{
  // Extract the registration and pass it to the callback.
  DAC::Registration_Packet packet;

  this->build_registration_packet (einode_reg, packet);

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - received registration from %s\n"),
              packet.einode_.c_str ()));

  using OASIS::DAC::EXECUTION_CONTEXT;
  int retval = EXECUTION_CONTEXT::instance ()->handle_registration (packet);

  if (0 != retval)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - handle_registration () ")
                ACE_TEXT ("had %d error(s)\n"),
                retval));
}

//
// build_registration_packet
//
void Tao_DataChannel_i::
build_registration_packet (const EINodeRegistration & einode_reg,
                           OASIS::DAC::Registration_Packet & packet)
{
  /// Copy the name
  packet.name_ = einode_reg.name.in ();

  // Copy the UUID
  ACE_Utils::UUID uuid;
  einode_reg.uuid >>= uuid;

  packet.einode_ = uuid.to_string ()->c_str ();

  // Wrap the command channel in a proxy.
  ACE_NEW_THROW_EX (packet.command_channel_,
                    OASIS::Tao_Command_Channel_Adapter (einode_reg.cmd_channel.in ()),
                    CORBA::NO_MEMORY ());

  // Update the length of the probes.
  CORBA::ULong length = einode_reg.probes.length ();

  // Copy over each probe entry.
  std::for_each (einode_reg.probes.get_buffer (),
                 einode_reg.probes.get_buffer () + length,
                 copy_software_probe_t (packet.probes_, this->registry_));
}

//
// unregister_einode
//
void Tao_DataChannel_i::unregister_einode (const UUID & uuid)
{
  ACE_Utils::UUID target_uuid;
  uuid >>= target_uuid;

  using OASIS::DAC::EXECUTION_CONTEXT;
  int retval = EXECUTION_CONTEXT::instance ()->handle_unregister_einode (target_uuid);

  if (0 != retval)
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - handle_unregister_einode () ")
                ACE_TEXT ("had %d error(s)\n"),
                retval));

}

}
