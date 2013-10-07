// $Id: EINode_Observer.cpp 1964 2011-10-03 02:59:33Z hillj $

#include "EINode_Observer.h"
#include "Data_Channel_Subscriber.h"

#include "oasis/DataAcquisitionController/Data_Packet.h"
#include "oasis/DataAcquisitionController/Registration_Packet.h"
#include "oasis/DataAcquisitionController/Execution_Context.h"

namespace OASIS
{

//
// operator <<=
//
void operator <<= (ACE_Utils::UUID & dst, OASIS::Middleware::UUID::ImmutableLocalClassPtr src)
{
  dst.time_low (src->get_data1 ());
  dst.time_mid (src->get_data2 ());
  dst.time_hi_and_version (src->get_data3 ());

  std::vector <TENA::octet> node_id = src->get_data4 ();
  dst.clock_seq_hi_and_reserved (node_id[0]);
  dst.clock_seq_low (node_id[1]);

#if (ACE_MAJOR_VERSION <= 5) && (ACE_MINOR_VERSION <= 6) && (ACE_BETA_VERSION <= 9)
  u_char * node = dst.node ()->node_ID ();
#else
  u_char * node = dst.node ().node_ID ();
#endif

  std::vector <TENA::octet>::iterator
    iter = node_id.begin () + 2, iter_end = node_id.end ();

  for (; iter != iter_end; ++ iter)
    *node ++ = *iter;
}

/**
 * @class read_software_probe_entry_t
 */
struct read_software_probe_entry_t
{
  //
  // read_software_probe_entry_t
  //
  read_software_probe_entry_t (OASIS::DAC::Software_Probe_Instances & dst)
    : dst_ (dst),
      index_ (0)
  {

  }

  //
  // operator ()
  //
  void operator () (const OASIS::Middleware::SoftwareProbeEntry::ImmutableLocalClassPtr entry)
  {
    const OASIS::Middleware::SoftwareProbeMetadata::ImmutableLocalClassPtr metadata = entry->get_metadata ();
    OASIS::DAC::Software_Probe_Instance & dst_inst = this->dst_[this->index_ ++];

    // Store the name of the software probe instance.
    dst_inst.first = entry->get_name ().c_str ();

    // Now, we can store is metadata information.
    dst_inst.second.uuid_ <<= metadata->get_uuid ();
    dst_inst.second.type_info_ = metadata->get_type ().c_str ();
    dst_inst.second.version_major_ = metadata->get_version_major ();
    dst_inst.second.version_minor_ = metadata->get_version_minor ();
    dst_inst.second.schema_ = metadata->get_schema ().c_str ();
  }

private:
  /// Collection of software probe metadata elements.
  OASIS::DAC::Software_Probe_Instances & dst_;

  /// The current index into the vector above.
  size_t index_;
};

//
// operator <<=
//
void operator <<= (OASIS::DAC::Software_Probe_Instances & dst,
                   const std::vector <OASIS::Middleware::SoftwareProbeEntry::ImmutableLocalClassPtr> & src)
{
  // Make sure we have the right size.
  dst.resize (src.size ());

  std::for_each (src.begin (),
                 src.end (),
                 read_software_probe_entry_t (dst));
}

//
// Einode_Observer
//
Einode_Observer::
Einode_Observer (Tena_Data_Channel_Subscriber & parent)
: parent_ (parent)
{

}

//
// Einode_Observer
//
Einode_Observer::~Einode_Observer (void)
{

}

//
// discoveryEvent
//
void Einode_Observer::
discoveryEvent (OASIS::Middleware::RegistrationChannel::ProxyPtr const & proxy,
                OASIS::Middleware::RegistrationChannel::PublicationStatePtr const & state)
{
  // Get the name of this object. If this name is not of
  // interest, then we should remove it from the SDO list.
  std::string name = state->get_name ();
  const std::set <std::string> & channel_names = this->parent_.channel_names ();

  if (channel_names.empty () || channel_names.find (name) != channel_names.end ())
  {
    // Since we care about this channel, we should just go ahead
    // perform any registration operations.
    this->handle_registration (state);
  }
  else
  {
    // We can remove this SDO from the subscription list.
    using OASIS::Middleware::RegistrationChannel::SubscriptionPtr;
    SubscriptionPtr subscription = this->parent_.get_registration_subscription ();
    subscription->removeSDO (proxy);
  }
}

//
// discoveryEvent
//
void Einode_Observer::
discoveryEvent (OASIS::Middleware::DataChannel::ProxyPtr const & proxy,
                OASIS::Middleware::DataChannel::PublicationStatePtr const & state)
{
  // Get the name of this object. If this name is not of
  // interest, then we should remove it from the SDO list.
  std::string name = state->get_name ();
  const std::set <std::string> & channel_names = this->parent_.channel_names ();

  if (channel_names.empty () || channel_names.find (name) != channel_names.end ())
  {
    // Since we care about this channel, we should just go ahead
    // perform any registration operations.
    this->handle_data (state);
  }
  else
  {
    // We can remove this SDO from the subscription list.
    using OASIS::Middleware::DataChannel::SubscriptionPtr;
    SubscriptionPtr subscription = this->parent_.get_data_subscription ();
    subscription->removeSDO (proxy);
  }
}

//
// stateChangeEvent
//
void Einode_Observer::
stateChangeEvent (OASIS::Middleware::RegistrationChannel::ProxyPtr const & proxy,
                  OASIS::Middleware::RegistrationChannel::PublicationStatePtr const & state)
{
  this->handle_registration (state);
}

//
// stateChangeEvent
//
void Einode_Observer::
stateChangeEvent (OASIS::Middleware::DataChannel::ProxyPtr const & proxy,
                  OASIS::Middleware::DataChannel::PublicationStatePtr const & state)
{
  this->handle_data (state);
}

//
// handle_registration
//
void Einode_Observer::
handle_registration (const OASIS::Middleware::RegistrationChannel::PublicationStatePtr & state)
{
  // Extract the registration information from the TENA object.
  DAC::Registration_Packet packet;
  packet.name_ = state->get_name ().c_str ();
  packet.einode_ <<= state->get_uuid ();
  packet.probes_ <<= state->get_probes ();

  // Notify the parent of the registration.
  using DAC::EXECUTION_CONTEXT;

  if (0 != EXECUTION_CONTEXT::instance ()->handle_registration (packet))
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - registration failed for %s\n"),
                packet.name_.c_str ()));
}

//
// handle_registration
//
void Einode_Observer::
handle_data (const OASIS::Middleware::DataChannel::PublicationStatePtr & state)
{
  // Extract the data from the TENA object.
  OASIS::Middleware::DataPacket::ImmutableLocalClassPtr data = state->get_data ();

  DAC::Data_Packet packet;
  packet.byte_order_ = data->get_byte_order ();
  packet.einode_uuid_ <<= data->get_einode ();

  size_t length = data->get_data ().size ();
  ACE_Auto_Array_Ptr <ACE_CDR::Octet> tmp_data (new ACE_CDR::Octet [length]);
  packet.probe_data_length_ = length;

  for (size_t i = 0; i < length; ++ i)
    tmp_data[i] = data->get_data ()[i];

  packet.probe_data_ = tmp_data.get ();

  // Notify the parent of the registration.
  using DAC::EXECUTION_CONTEXT;

  if (0 != EXECUTION_CONTEXT::instance ()->handle_data (packet))
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to handle data\n")));
}

}
