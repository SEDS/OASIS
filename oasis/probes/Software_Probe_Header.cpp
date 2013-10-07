// $Id: Software_Probe_Header.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "Software_Probe_Header.h"
#include "Software_Probe_Data_Preparer.h"

#include "ace/CDR_Stream.h"
#include "oasis/streams.h"

#if !defined (__OASIS_INLINE__)
#include "Software_Probe_Header.inl"
#endif

namespace OASIS
{

//
// dump
//
void Software_Probe_Header::dump (std::ostream & output) const
{
  output << "Header contents [probe=" << this->uuid_.to_string ()->c_str () << "; "
    << "timestamp=" << this->last_ts_.sec () << "." << this->last_ts_.usec () << "; "
    << "seqnum=" << this->seqnum_ << "; state=" << this->state_ << ";]" << std::endl;
}

//
// recall
//
int Software_Probe_Header::
recall (const char * data, size_t length, int byte_order)
{
  Software_Probe_Data_Preparer prep (data, length);
  ACE_InputCDR input (prep.message_block (), byte_order);
  return this->recall (input);
}

//
// recall
//
int Software_Probe_Header::recall (ACE_InputCDR & input)
{
  unsigned char magic[4];
  if (!input.read_octet_array (magic, 4))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read magic\n")),
                       -1);

  if (!(magic[0] == 'E' && magic[1] == 'I' && magic[2] == 'S' && magic[3] == 'A'))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - invalid header format\n")),
                       -1);

  // Read the UUID from the input stream and validate it.
  unsigned char version[2];
  if (!input.read_octet_array (version, 2))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read version\n")),
                       -1);

  if (!(version[0] == 1 && version[1] <= 1))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - invalid header version\n")),
                       -1);

  // Read the UUID from the input stream and validate it.
  if (!(input >>= this->uuid_))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read uuid\n")),
                       -1);

  // Read the second and microsecond.
  ACE_UINT32 sec, usec;
  if (!(input >> sec))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read seconds\n")),
                       -1);

  if (!(input >> usec))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read micro-seconds\n")),
                       -1);

  // Set the last timestamp.
  this->last_ts_.set (sec, usec);

  // Extract the sequence number and probe's state.
  if (!(input.read_ulong (this->seqnum_)))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read sequence number\n")),
                       -1);
if (!(input.read_ushort (this->state_)))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read probe state\n")),
                       -1);

  if (!(input.read_ulong (this->datasize_)))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read data size\n")),
                       -1);

  if (!(input.read_string (this->name_)))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read instance name\n")),
                       -1);

  // Finally, make sure we have the correct alignment.
  input.align_read_ptr (ACE_CDR::MAX_ALIGNMENT);

  return input.good_bit () ? 0 : -1;
}

}
