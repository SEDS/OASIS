// $Id: Data_Channel_Publisher.cpp 2095 2012-01-05 15:51:11Z dfeiock $

#include "Data_Channel_Publisher.h"
#include "Configuration.h"

#include "oasis/EINode/Data_Channel.h"
#include "oasis/EINode/Standard_EINode.h"
#include "oasis/probes/Software_Probe_Impl.h"

#include <TENA/Middleware/Utils/Endpoint.h>
#include <OASIS/Middleware/SoftwareProbeEntry.h>

#include "ace/UUID.h"
#include "ace/Get_Opt.h"

#include <string>

//
// create_UUID
//
OASIS::Middleware::UUID::LocalClassPtr create_UUID (const ACE_Utils::UUID & uuid)
{
  std::vector <TENA::octet> node_id;
  node_id.push_back (uuid.clock_seq_hi_and_reserved ());
  node_id.push_back (uuid.clock_seq_low ());

  // Copy entry NodeID information
#if (ACE_MAJOR_VERSION <= 5) && (ACE_MINOR_VERSION <= 6) && (ACE_BETA_VERSION <= 9)
  node_id.insert (node_id.end (),
                  uuid.node ()->node_ID (),
                  uuid.node ()->node_ID () + ACE_Utils::UUID_Node::NODE_ID_SIZE);
#else
  node_id.insert (node_id.end (),
                  uuid.node ().node_ID (),
                  uuid.node ().node_ID () + ACE_Utils::UUID_Node::NODE_ID_SIZE);
#endif

  // Copy the UUID struct from entry to TENA UUID
  OASIS::Middleware::UUID::LocalClassPtr tena_uuid (
    OASIS::Middleware::UUID::create (uuid.time_low (),
                                     uuid.time_mid (),
                                     uuid.time_hi_and_version (),
                                     node_id));

  return tena_uuid;
}

/**
 * @class gather_probe_metadata_t
 *
 * Helper functor for writing probe metadata to the target output
 * stream. This will also keep track of the total metadata size.
 */
struct insert_entry_t
{
public:
  //
  // gather_probe_metadata_t
  //
  insert_entry_t (std::vector <OASIS::Middleware::SoftwareProbeEntry::ImmutableLocalClassPtr> & probes)
    : probes_ (probes)
  {

  }

  //
  // operator ()
  //
  void operator () (const OASIS::SoftwareProbe_Hash_Map::ENTRY & entry)
  {
    const OASIS::Software_Probe_Metadata & metadata = entry.item ()->metadata ();
    OASIS::Middleware::UUID::LocalClassPtr tena_uuid (::create_UUID (metadata.uuid_));

    OASIS::Middleware::SoftwareProbeMetadata::LocalClassPtr tena_metadata (
      OASIS::Middleware::SoftwareProbeMetadata::create (tena_uuid,
                                                        metadata.type_info_.c_str (),
                                                        metadata.version_major_,
                                                        metadata.version_minor_,
                                                        metadata.schema_.c_str ()));

    OASIS::Middleware::SoftwareProbeEntry::LocalClassPtr probe_entry (
      OASIS::Middleware::SoftwareProbeEntry::create (entry.key ().c_str (),
                                                     tena_metadata));

    // Store the software probe.
    this->probes_.push_back (probe_entry);
  }

private:
  /// Target output stream for metadata.
  std::vector <OASIS::Middleware::SoftwareProbeEntry::ImmutableLocalClassPtr> & probes_;
};


namespace OASIS
{
//
// Data_Channel_Publisher
//
Data_Channel_Publisher::Data_Channel_Publisher (void)
{

}

//
// ~Data_Channel_Publisher
//
Data_Channel_Publisher::~Data_Channel_Publisher (void)
{

}

//
// set_einode
//
void Data_Channel_Publisher::set_einode (Standard_EINode * einode)
{
  this->einode_ = einode;
}

//
// init
//
int Data_Channel_Publisher::init (int argc, ACE_TCHAR * argv [])
{
  try
  {
    // Parse the configuration and initialize the TENA middleware.
    this->config_.parse (argc, argv);
    this->runtime_ = TENA::Middleware::init (this->config_.tenaConfiguration ());

    // Join the execution in the configuration file.
    TENA::Middleware::Endpoint endpoint =
      this->config_["emEndpoint"].getValue <TENA::Middleware::Endpoint> ();

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - joining execution %s\n"),
                endpoint.toString ().c_str ()));

    this->execution_ = this->runtime_->joinExecution (endpoint);

    // Join the session in the configuration file.
    std::string session = this->config_["sessionName"].getValue <std::string> ();

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - creating session %s\n"),
                session.c_str ()));

    this->session_ = this->execution_->createSession (session);

    return 0;
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - unknown exception caught\n")));
  }

  this->cleanup ();

  return -1;
}

//
// cleanup
//
void Data_Channel_Publisher::cleanup (void)
{
  if (this->data_channel_.isValid ())
    this->data_channel_.reset ();

  if (this->reg_channel_.isValid ())
    this->reg_channel_.reset ();

  if (this->session_.isValid ())
    this->session_.reset ();

  if (this->runtime_.isValid ())
    this->runtime_.reset ();
}

//
// create_registration_channel_servant
//
int Data_Channel_Publisher::
create_registration_channel_servant (const std::vector <OASIS::Middleware::SoftwareProbeEntry::ImmutableLocalClassPtr> & probes)
{
  if (!this->session_.isValid ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - session pointer is invalid\n")),
                       -1);

  // Create the servant factory that will be used to create the
  // new servant object.
  OASIS::Middleware::RegistrationChannel::ServantFactoryPtr factory =
    OASIS::Middleware::RegistrationChannel::ServantFactory::create (*this->session_);

  // Set the values of the initializer.
  std::auto_ptr <OASIS::Middleware::RegistrationChannel::PublicationStateInitializer>
    initializer (factory->createInitializer ());

  const OASIS::Einode_Configuration & config = this->einode_->configuration ();

  initializer->set_name (config.name ().c_str ());
  initializer->set_uuid (::create_UUID (config.uuid ()));
  initializer->set_probes (probes);

  TENA::Middleware::CommunicationProperties cp =
    this->config_["bestEffort"].isSet() ?
    TENA::Middleware::BestEffort : TENA::Middleware::Reliable;

  // Instantiate a new servant.
  this->reg_channel_ = factory->createServant (*initializer, cp);

  return 0;
}

//
// create_data_channel_servant
//
int Data_Channel_Publisher::
create_data_channel_servant (const std::vector <TENA::octet> & data)
{
  if (!this->session_.isValid ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - session pointer is invalid\n")),
                       -1);

  // Create the servant factory that will be used to create the
  // new servant object.
  OASIS::Middleware::DataChannel::ServantFactoryPtr factory =
    OASIS::Middleware::DataChannel::ServantFactory::create (*this->session_);

  // Set the values of the initializer.
  std::auto_ptr <OASIS::Middleware::DataChannel::PublicationStateInitializer>
    initializer (factory->createInitializer ());

  const OASIS::Einode_Configuration & config = this->einode_->configuration ();

  OASIS::Middleware::DataPacket::LocalClassPtr packet (
    OASIS::Middleware::DataPacket::create (::create_UUID (config.uuid ()),
    static_cast <bool> (ACE_BYTE_ORDER),
    data));

  initializer->set_name (config.name ().c_str ());
  initializer->set_data (packet);

  TENA::Middleware::CommunicationProperties cp =
    this->config_["bestEffort"].isSet() ?
    TENA::Middleware::BestEffort : TENA::Middleware::Reliable;

  // Instantiate a new servant.
  this->data_channel_ = factory->createServant (*initializer, cp);

  return 0;
}

//
// deactivate
//
int Data_Channel_Publisher::fini (void)
{
  try
  {
    this->cleanup ();
    return 0;
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - unknown exception caught\n")));
  }

  return -1;
}

//
// perform_registration
//
int Data_Channel_Publisher::
perform_registration (const SoftwareProbe_Hash_Map & probes)
{
  try
  {
    // Construct the TENA registration information.
    std::vector <OASIS::Middleware::SoftwareProbeEntry::ImmutableLocalClassPtr> entries;
    entries.reserve (probes.current_size ());

    std::for_each (probes.begin (),
                   probes.end (),
                   insert_entry_t (entries));

    if (this->reg_channel_.isValid ())
    {
      // We are just going to update the registration information.
      std::auto_ptr <OASIS::Middleware::RegistrationChannel::PublicationStateUpdater>
        updater (this->reg_channel_->createUpdater ());

      updater->set_probes (entries);
      this->reg_channel_->commitUpdater (updater);
    }
    else
    {
      // We are creating the servant for the first time.
      if (0 != this->create_registration_channel_servant (entries))
        ACE_ERROR_RETURN ((LM_ERROR,
                           ACE_TEXT ("%T (%t) - %M - failed to registration ")
                           ACE_TEXT ("channel servant\n")),
                           -1);
    }

    return 0;
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - unknown exception caught\n")));
  }

  return -1;
}

//
// send_data
//
void Data_Channel_Publisher::send_data (const char * data, size_t length)
{
  try
  {
    std::vector <TENA::octet> tena_data (data, data + length);

    if (this->data_channel_.isValid ())
    {
      // Insert new data by creating an update.
      std::auto_ptr <OASIS::Middleware::DataChannel::PublicationStateUpdater>
        updater (this->data_channel_->createUpdater ());

      OASIS::Middleware::DataPacket::ImmutableLocalClassPtr ro_packet (updater->get_data ());
      OASIS::Middleware::DataPacket::LocalClassPtr packet (ro_packet->clone ());

      packet->set_data (tena_data);
      updater->set_data (packet);

      this->data_channel_->commitUpdater (updater);
    }
    else
    {
      if (0 != this->create_data_channel_servant (tena_data))
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("%T (%t) - %M - failed to data channel servant\n")));
    }
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - unknown exception caught\n")));
  }
}

}

ACE_FACTORY_NAMESPACE_DEFINE (OASIS_TENA_DATACHANNEL_PUBLISHER,
                              OASIS_Tena_Data_Channel_Publisher,
                              OASIS::Data_Channel_Publisher);
