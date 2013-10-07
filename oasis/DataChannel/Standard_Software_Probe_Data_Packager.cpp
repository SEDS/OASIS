// $ Id$

#include "Standard_Software_Probe_Data_Packager.h"

#if !defined (__OASIS_INLINE__)
#include "Standard_Software_Probe_Data_Packager.inl"
#endif

#include "oasis/streams.h"

namespace OASIS
{

//
// init
//
bool Standard_Software_Probe_Data_Packager::
init (const ACE_Utils::UUID & uuid, const ACE_CString & name, size_t data_size)
{
  // Allocate the stream to the desired size
  this->probe_.reset ();
  if (data_size != 0)
  {
    this->fixed_size_ = 44 + name.length () + data_size;
    char * buf = 0;
    this->probe_.adjust (this->fixed_size_, buf);
    this->probe_.consolidate ();
    this->probe_.reset ();
  }

  // Write the header magic.
  if (!this->probe_.write_char_array ("EISA", 4))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to write magic\n")),
                       false);

  // Write the version number. We should allow the user to select
  // what version to use for writing the header. For now, however,
  // we assume that everyone is using version 1.1.
  static unsigned char version[2] = {1, 1};
  if (!this->probe_.write_octet_array (version, 2))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to write version\n")),
                       false);

  // Write the Uuid for the software probe's type.
  if (!(this->probe_ <<= uuid))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to write uuid\n")),
                       false);

  // Write the placeholders for the time (both sec and usec).
  if (0 == (this->ph_tv_sec_ = this->probe_.write_long_placeholder ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to reserve space ")
                       ACE_TEXT ("for secs\n")),
                       false);

  if (0 == (this->ph_tv_usec_ = this->probe_.write_long_placeholder ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to reserve space ")
                       ACE_TEXT ("for usecs\n")),
                       false);

  // Write placeholders for the sequence number and state.
  if (0 == (this->ph_seqnum_ = this->probe_.write_long_placeholder ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to reserve space ")
                       ACE_TEXT ("for sequence number\n")),
                       false);

  if (0 == (this->ph_state_ = this->probe_.write_short_placeholder ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to reserve space ")
                       ACE_TEXT ("for state\n")),
                       false);

  // Write placeholder for the data size.
  if (0 == (this->ph_data_size_ = this->probe_.write_long_placeholder ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to reserve space ")
                       ACE_TEXT ("for data size\n")),
                       false);

  if (!this->instance_name_i (name))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to initialize ")
                       ACE_TEXT ("instance name\n")),
                       false);

  // Store the initialization state.
  this->is_init_ = this->probe_.good_bit ();
  return this->is_init_;
}

//
// instance_name
//
bool Standard_Software_Probe_Data_Packager::instance_name (const ACE_CString & name)
{
  if (!this->is_init_)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - packager not initialized\n")),
                       false);

  return this->instance_name_i (name);
}

//
// instance_name_i
//
bool Standard_Software_Probe_Data_Packager::instance_name_i (const ACE_CString & name)
{
  // Reset the header's pointer, then set its alignment to the constant
  // size of the header.
  this->probe_.reset ();

  char * buf = 0;
  this->probe_.adjust (44, buf);

  // We can now write the instance name of the header.
  if (!this->probe_.write_string (name))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to write instance name\n")),
                       false);

  // Finally, make sure the write pointer is aligned.
  this->probe_.align_write_ptr (ACE_CDR::MAX_ALIGNMENT);

  // Store the length of the header
  this->end_of_header_ = this->probe_.length ();

  return this->probe_.good_bit ();
}


//
// update
//
void Standard_Software_Probe_Data_Packager::
update (const ACE_Time_Value & tv, ACE_UINT32 seqnum, ACE_UINT32 state)
{
  // Write the timestamp to the header.
  this->probe_.replace (static_cast <ACE_CDR::Long> (tv.sec ()), this->ph_tv_sec_);
  this->probe_.replace (static_cast <ACE_CDR::Long> (tv.usec ()), this->ph_tv_usec_);

  // Replace the sequence number and state.
  this->probe_.replace (static_cast <ACE_CDR::Long> (seqnum), this->ph_seqnum_);
  this->probe_.replace (static_cast <ACE_CDR::Short> (state), this->ph_state_);
}

//
// stream
//
const char * Standard_Software_Probe_Data_Packager::stream (void)
{
  // Update the data size attribute in the header.
  this->probe_.replace (static_cast <ACE_CDR::Long> (this->data_size ()),
                        this->ph_data_size_);

  // Consolidate the message blocks
  this->probe_.consolidate ();

  // Return the stream as a char *
  return this->probe_.buffer ();
}

//
// reset
//
void Standard_Software_Probe_Data_Packager::reset (void)
{
  if (0 == this->fixed_size_)
  {
    // Reset the CDR and adjust the write pointer to the end of the header
    this->probe_.reset ();

    char * buf = 0;
    this->probe_.adjust (this->end_of_header_, buf);
  }
}

//
// write methods
//
int Standard_Software_Probe_Data_Packager::write_boolean (const bool & in)
{
  return (this->probe_ << in);
}

int Standard_Software_Probe_Data_Packager::write_string (const ACE_CString & in)
{
  return (this->probe_ << in);
}

int Standard_Software_Probe_Data_Packager::write_int8 (const ACE_INT8 & in)
{
  return (this->probe_ << in);
}

int Standard_Software_Probe_Data_Packager::write_int16 (const ACE_INT16  & in)
{
  return (this->probe_ << in);
}

int Standard_Software_Probe_Data_Packager::write_int32 (const ACE_INT32 & in)
{
  return (this->probe_ << in);
}

int Standard_Software_Probe_Data_Packager::write_int64 (const ACE_INT64 & in)
{
  return (this->probe_ << in);
}

int Standard_Software_Probe_Data_Packager::write_uint8 (const ACE_UINT8 & in)
{
  return (this->probe_ << in);
}

int Standard_Software_Probe_Data_Packager::write_uint16 (const ACE_UINT16 & in)
{
  return (this->probe_ << in);
}

int Standard_Software_Probe_Data_Packager::write_uint32 (const ACE_UINT32 & in)
{
  return (this->probe_ << in);
}

int Standard_Software_Probe_Data_Packager::write_uint64 (const ACE_UINT64 & in)
{
  return (this->probe_ << in);
}

int Standard_Software_Probe_Data_Packager::write_real32 (const double & in)
{
  ACE_CDR::Double db (in);
  return (this->probe_ << db);
}

int Standard_Software_Probe_Data_Packager::write_real64 (const long double & in)
{
  return 1;
}

}
