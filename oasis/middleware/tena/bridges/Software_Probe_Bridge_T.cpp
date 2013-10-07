// $Id: Software_Probe_Bridge_T.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#if !defined (__OASIS_INLINE__)
#include "Software_Probe_Bridge_T.inl"
#endif

#include "TENA/Time/Impl.h"

namespace OASIS
{
  //
  // to_tena_uuid
  //
  inline ::OASIS::Middleware::UUID::LocalClassPtr
  to_tena_uuid (const ACE_Utils::UUID & uuid)
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

    return
      ::OASIS::Middleware::UUID::create (uuid.time_low (),
                                         uuid.time_mid (),
                                         uuid.time_hi_and_version (),
                                         node_id);
  }

//
// initialize_metadata
//
template <typename SDO>
int Software_Probe_Bridge_T <SDO>::
initialize_metadata (typename SDO::PublicationStateInitializer & initializer,
                     const ACE_Utils::UUID & einode,
                     const DAC::Software_Probe_Instance & inst)
{
  OASIS::Middleware::SoftwareProbeMetadata::LocalClassPtr tena_metadata (
    OASIS::Middleware::SoftwareProbeMetadata::create (to_tena_uuid (inst.int_id_->uuid_),
                                                      inst.int_id_->type_info_.c_str (),
                                                      inst.int_id_->version_major_,
                                                      inst.int_id_->version_minor_,
                                                      inst.int_id_->schema_.c_str ()));

  // Update the initializer with its initial values for the software
  // probe base class.
  initializer.set_name (inst.ext_id_.c_str ());
  initializer.set_metadata (tena_metadata);
  initializer.set_einode (to_tena_uuid (einode));
  initializer.set_last_timestamp (TENA::Time::create ());
  initializer.set_state (0);
  initializer.set_sequence_num (0);

  return 0;
}

//
// configure
//
template <typename SDO>
int Software_Probe_Bridge_T <SDO>::
configure (::TENA::Middleware::Session & session, const ACE_CString & config_file)
{
  this->factory_ = SDO::ServantFactory::create (session);

  // Parse config_file if defined
  if (0 != config_file.length ())
  {
    Configuration_Manager manager;
    if (!manager.parse (this->group_, config_file))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to parse configuration file %s\n"),
                         config_file.c_str ()),
                         -1);
  }
  return 0;
}

//
// destroy_servant
//
template <typename SDO>
int Software_Probe_Bridge_T <SDO>::
destroy_servant (const ACE_CString & probe_name)
{
  typename std::map <ACE_CString, typename SDO::ServantPtr>::iterator iter;
  iter = this->servants_.find (probe_name);

  if (iter != this->servants_.end ())
  {
    // Destory the servant
    iter->second.reset ();
    this->servants_.erase (iter);
    return 0;
  }

  ACE_ERROR_RETURN ((LM_ERROR,
                     ACE_TEXT ("%T (%t) - %M - attempted to destroy a servant which does not exist\n")),
                     -1);
}


//
// updater_t
//
template <typename T, typename P1>
int updater_t <T, P1>::operator () (T & t, ACE_InputCDR & in)
{
  // Read the value from the input stream.
  typename oasis_var_t <P1>::result_type value;

  if (!(in >> value))
    return -1;

  // Set the value.
  (t.*this->funcptr_) (value);

  return 0;
}

//
// updater_t
// Specialized for ::std::string
//
template <typename T>
int updater_t <T, const ::std::string &>::operator () (T & t, ACE_InputCDR & in)
{
  // Read the value from the input stream.
  ACE_CString streamvalue;

  if (!(in >> streamvalue))
    return -1;

  ::std::string value (streamvalue.c_str());

  // Set the value.
  (t.*this->funcptr_) (value);

  return 0;
}

//
// initializer_t operator ()
//
template <typename T, typename P1>
bool initialize_t <T, P1>::
operator () (T & t, const std::string & value_id, Configuration_Member_Container * container)
{
  if (container == 0)
    return (*this) (t);

  try
  {
    std::istringstream stream ( (*container)[value_id].value ());
    typename oasis_dereference_var_t <P1>::result_type value;
    if (!(stream >> value))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - Unable to convert %s to ")
                         ACE_TEXT ("tena datatype")),
                         false);
    (t.*this->funcptr_) (value);
  }
  catch (Invalid_Child & ex)
  {
    return (*this) (t);
  }

  return true;
}

//
// initializer_t operator ()
// Specialized for ::std::string
//
template <typename T>
bool initialize_t <T, const ::std::string &>::
operator () (T & t, const std::string & value_id, Configuration_Member_Container * container)
{
  if (container == 0)
    return (*this) (t);

  try
  {
    typename oasis_dereference_var_t <const ::std::string &>::result_type value;
    value = (*container)[value_id].value ();
    (t.*this->funcptr_) (value);
  }
  catch (Invalid_Child & ex)
  {
    return (*this) (t);
  }

  return true;
}

}
