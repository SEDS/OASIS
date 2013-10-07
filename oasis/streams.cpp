// $Id: streams.cpp 1988 2011-10-07 18:15:20Z dfeiock $

#include "streams.h"
#include "ace/Time_Value.h"
#include "ace/CDR_Stream.h"
#include "ace/UUID.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

//
// operator <<=
//
bool operator <<= (ACE_OutputCDR & output, const ACE_Time_Value & tv)
{
  output.write_long (static_cast <ACE_CDR::Long> (tv.sec ()));
  output.write_long (tv.usec ());

  return output.good_bit ();
}

//
// operator <<
//
bool operator <<= (ACE_OutputCDR & output, const ACE_Utils::UUID & uuid)
{
  output.write_ulong (uuid.time_low ());

  output.write_ushort (uuid.time_mid ());
  output.write_ushort (uuid.time_hi_and_version ());

  output.write_octet (uuid.clock_seq_hi_and_reserved ());
  output.write_octet (uuid.clock_seq_low ());

#if (ACE_MAJOR_VERSION <= 5) && (ACE_MINOR_VERSION <= 6) && (ACE_BETA_VERSION <= 9)
  output.write_octet_array (uuid.node ()->node_ID (),
#else
  output.write_octet_array (uuid.node ().node_ID (),
#endif
                            ACE_Utils::UUID_Node::NODE_ID_SIZE);

  return output.good_bit ();
}

///////////////////////////////////////////////////////////////////////////////
//

//
// operator >>=
//
bool operator >>= (ACE_InputCDR & input, ACE_Time_Value & tv)
{
  ACE_UINT32 usec;
  ACE_UINT32 secs;

  input.read_ulong (secs);
  input.read_ulong (usec);

  tv.sec (secs);
  tv.usec (usec);

  return input.good_bit ();
}

bool operator >>= (ACE_InputCDR & input, ACE_Utils::UUID & uuid)
{
  // First, extract the elements of the UUID
  ACE_UINT32 data1;
  ACE_UINT16 data2;
  ACE_UINT16 data3;
  unsigned char chunk[8];

  input.read_ulong (data1);
  input.read_ushort (data2);
  input.read_ushort (data3);
  input.read_octet_array (chunk, 8);

  // Next, store the elements in the ACE_Utils::UUID.
  uuid.time_low (data1);
  uuid.time_mid (data2);
  uuid.time_hi_and_version (data3);

  // Extract the last chunk of the UUID.
  uuid.clock_seq_hi_and_reserved (chunk[0]);
  uuid.clock_seq_low (chunk[1]);

#if (ACE_MAJOR_VERSION <= 5) && (ACE_MINOR_VERSION <= 6) && (ACE_BETA_VERSION <= 9)
  ACE_Utils::UUID_Node::Node_ID & node_id = uuid.node ()->node_ID ();
#else
  ACE_Utils::UUID_Node::Node_ID & node_id = uuid.node ().node_ID ();
#endif

  ACE_OS::memcpy (&node_id,
                  chunk + 2,
                  ACE_Utils::UUID_Node::NODE_ID_SIZE);

  return input.good_bit ();
}

ACE_END_VERSIONED_NAMESPACE_DECL
