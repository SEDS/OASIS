// $Id: Tao_Data_Channel_Client.cpp 2234 2013-02-01 15:22:32Z dfeiock $

#include "Tao_Data_Channel_Client.h"

#include "oasis/EINode/Standard_EINode.h"
#include "oasis/probes/Software_Probe_Impl.h"
#include "oasis/middleware/tao/UUID.h"

#include "Tao_Software_Probe_Data_Packager.h"

#include "ace/Get_Opt.h"

//
// operator <<=
//
void operator <<= (OASIS::SoftwareProbeMetadata & dst,
                   const OASIS::Software_Probe_Metadata & src)
{
  dst.uuid <<= src.uuid_;
  dst.type = ::CORBA::string_dup (src.type_info_.c_str ());
  dst.version_major = src.version_major_;
  dst.version_minor = src.version_minor_;
  dst.schema = ::CORBA::string_dup (src.schema_.c_str ());
}

/**
 * @class gather_probe_metadata_t
 *
 * Helper functor for writing probe metadata to the target output
 * stream. This will also keep track of the total metadata size.
 */
struct gather_probe_metadata_t
{
public:
  //`
  // gather_probe_metadata_t
  //
  gather_probe_metadata_t (OASIS::SoftwareProbeEntrySeq & probes)
    : probes_ (probes),
      index_ (0)
  {

  }

  //
  // operator ()
  //
  void operator () (const OASIS::SoftwareProbe_Hash_Map::ENTRY & entry)
  {
    // Get the next entry in the listing.
    ::OASIS::SoftwareProbeEntry & probe = this->probes_[this->index_ ++];

    // Get the software probe's information.
    probe.name = ::CORBA::string_dup (entry.key ().c_str ());
    probe.metadata <<= entry.item ()->metadata ();
  }

private:
  /// Target output stream for metadata.
  ::OASIS::SoftwareProbeEntrySeq & probes_;

  /// The size of the metadata.
  size_t index_;
};


namespace OASIS
{
//
// Tao_Data_Channel_Client
//
Tao_Data_Channel_Client::Tao_Data_Channel_Client (void)
: run_orb_ (true),
  servant_ (&command_channel_, false)
{

}

//
// ~Tao_Data_Channel_Client
//
Tao_Data_Channel_Client::~Tao_Data_Channel_Client (void)
{

}

//
// set_einode
//
void Tao_Data_Channel_Client::set_einode (Standard_EINode * einode)
{
  // Save the EINode.
  this->einode_ = einode;

  // Pass the EINode to the command channel.
  this->command_channel_.set_einode (einode);
}

//
// init
//
int Tao_Data_Channel_Client::init (int argc, ACE_TCHAR * argv [])
{
  try
  {
    // Parse the command-line arguments.
    if (0 != this->parse_args (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to parse ")
                         ACE_TEXT ("command-line arguments\n")),
                         -1);

    // Resolve the RootPOA.
    ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");
    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolved RootPOA\n")),
                         -1);

    ::PortableServer::POA_var root_poa = ::PortableServer::POA::_narrow (obj.in ());

    if (::CORBA::is_nil (root_poa.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - object is not a POA\n")),
                         -1);

    // Create the child POA for the command channel.
    ::PortableServer::POA_var the_POA =
      this->create_command_channel_POA (root_poa.in ());

    // Finally, activate the servant and task to execute commands.
    this->servant_.activate (the_POA.in ());

    if (this->run_orb_)
      this->orb_task_.activate ();

    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }

  return -1;
}

//
// parse_args
//
int Tao_Data_Channel_Client::parse_args (int argc, ACE_TCHAR * argv [])
{
  // Initialize the CORBA orb.
  this->orb_ = ::CORBA::ORB_init (argc, argv);

  // Initialize the command-line parser.
  const char * optargs = "";
  ACE_Get_Opt get_opt (argc, argv, optargs, 0);

  get_opt.long_option ("no-orb", ACE_Get_Opt::NO_ARG);

  // Parse the command-line options specific to this service.
  int opt = 0;

  while (EOF != (opt = get_opt ()))
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("no-orb", get_opt.long_option ()))
        this->run_orb_ = false;

      break;
    }
  }

  // Set the tasks ORB if this service needs to run its own
  // ORB.
  if (this->run_orb_)
    this->orb_task_.reset (this->orb_.in ());

  return 0;
}

//
// create_command_channel_POA
//
::PortableServer::POA_ptr Tao_Data_Channel_Client::
create_command_channel_POA (::PortableServer::POA_ptr parent)
{
  // Construct the policy list for the LoggingServerPOA.
  ::CORBA::PolicyList policies (6);
  policies.length (6);

  policies[0] = parent->create_thread_policy (PortableServer::SINGLE_THREAD_MODEL);
  policies[1] = parent->create_servant_retention_policy (PortableServer::RETAIN);
  policies[2] = parent->create_id_assignment_policy (PortableServer::SYSTEM_ID);
  policies[3] = parent->create_id_uniqueness_policy (PortableServer::UNIQUE_ID);
  policies[4] = parent->create_lifespan_policy (PortableServer::TRANSIENT);
  policies[5] = parent->create_request_processing_policy (PortableServer::USE_ACTIVE_OBJECT_MAP_ONLY);

  // Create the child POA for the test logger factory servants.
  ::PortableServer::POA_var child_POA =
    parent->create_POA ("TAO_CommandChannel",
                        ::PortableServer::POAManager::_nil (),
                        policies);

  for (size_t i = 0; i < 6; ++ i)
    policies[i]->destroy ();

  PortableServer::POAManager_var the_mgr = child_POA->the_POAManager ();
  the_mgr->activate ();

  return child_POA._retn ();
}

//
// deactivate
//
int Tao_Data_Channel_Client::fini (void)
{
  try
  {
    if (!::CORBA::is_nil (this->data_channel_.in ()))
    {
      UUID uuid;

      // Make sure we unregister this EINode.
      uuid <<= this->einode_->configuration ().uuid ();
      this->data_channel_->unregister_einode (uuid);
    }

    // Deactivate the command channel so it can no longer receive
    // any commmands to process.
    this->servant_.deactivate ();

    if (this->run_orb_)
    {
      // Shutdown the ORB, and wait for all task to complete.
      this->orb_->shutdown ();
      this->orb_task_.wait ();

      // Finally, destroy the ORB. We are assuming that because
      // you are running the ORB, then you are the owner of the
      // ORB.
      this->orb_->destroy ();
    }

    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }

  return -1;
}

//
// perform_registration
//
int Tao_Data_Channel_Client::
perform_registration (const SoftwareProbe_Hash_Map & probes)
{
  try
  {
    if (::CORBA::is_nil (this->data_channel_.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - data channel is NIL; ")
                         ACE_TEXT ("cannot perform registration\n")),
                         -1);

    const OASIS::Einode_Configuration & config = this->einode_->configuration ();
    const ACE_Utils::UUID & uuid = config.uuid ();

    // First, copy the EINode's information to the structure.
    ::OASIS::EINodeRegistration reginfo;
    reginfo.uuid <<= uuid;
    reginfo.name = ::CORBA::string_dup (config.name ().c_str ());

    ::CORBA::Object_var obj = this->servant_.get_reference ();
    reginfo.cmd_channel = ::OASIS::CommandChannel::_narrow (obj.in ());

    // Next, gather all the loaded probe's metadata.
    reginfo.probes.length (probes.current_size ());
    std::for_each (probes.begin (),
                   probes.end (),
                   gather_probe_metadata_t (reginfo.probes));

    // Register this EINode with the DAC. This include sending the
    // registration information, and the handler for receiving commands.
    this->data_channel_->register_einode (reginfo);

    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }

  return -1;
}

//
// send_data
//
void Tao_Data_Channel_Client::send_data (const char * data, size_t length)
{
  try
  {
    if (!::CORBA::is_nil (this->data_channel_.in ()))
    {
      // Initialize the packet contents.
      DataPacket packet;

      packet.byte_order = ACE_BYTE_ORDER;
      packet.einode_uuid <<= this->einode_->configuration ().uuid ();
      packet.data.replace (length,
                           length,
                           (unsigned char *)data,
                           false);

      // Send the packet to the DAC.
      this->data_channel_->send_data (packet);
    }
    else
    {
      this->is_connected_ = false;
      throw ::OASIS::Transient_Error ("object is not a DataChannel");
    }
  }
  catch (const ::CORBA::Exception & ex)
  {
    this->is_connected_ = false;
    throw ::OASIS::Transient_Error (ex._info ().c_str ());
  }
}

//
// connect
//
void Tao_Data_Channel_Client::connect (void)
{
  try
  {
    // Resolve the DataChannel object reference.
    ::CORBA::Object_var obj =
      this->orb_->resolve_initial_references ("DataChannel");

    if (::CORBA::is_nil (obj.in ()))
      throw ::OASIS::Connect_Error ("failed to resolve the DataChannel");

    // Extract the data channel from the object.
    this->data_channel_ = DataChannel::_narrow (obj.in ());

    if (::CORBA::is_nil (this->data_channel_.in ()))
      throw ::OASIS::Connect_Error ("object is not a DataChannel");

    this->is_connected_ = true;
  }
  catch (const ::CORBA::Exception & ex)
  {
    throw Connect_Error (ex._info ().c_str ());
  }
  catch (const std::exception & ex)
  {
    throw Connect_Error (ex.what ());
  }
}

Software_Probe_Data_Packager *
Tao_Data_Channel_Client::packager (void)
{
  return new Tao_Software_Probe_Data_Packager ();
}

}

ACE_FACTORY_NAMESPACE_DEFINE (OASIS_TAO_DATACHANNEL_CLIENT,
                              OASIS_Tao_Data_Channel_Client,
                              OASIS::Tao_Data_Channel_Client);
