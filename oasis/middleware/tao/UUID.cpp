// $Id: UUID.cpp 1934 2011-09-28 14:56:30Z hillj $

#include "UUID.h"
#include "ace/OS_NS_string.h"

//
// operator >>=
//
bool operator >>= (const ::OASIS::UUID & src, ACE_Utils::UUID & dst)
{
  OASIS_TAO_TRACE ("bool operator >>= (const ::OASIS::UUID &, ACE_Utils::UUID &)");

  // Extract the integer values from the UUID.
  dst.time_low (src.data1);
  dst.time_mid (src.data2);
  dst.time_hi_and_version (src.data3);

  // Extract the last chunk of the UUID.
  dst.clock_seq_hi_and_reserved (src.data4[0]);
  dst.clock_seq_low (src.data4[1]);

  ACE_Utils::UUID_Node::Node_ID & node_id = dst.node ().node_ID ();

  ACE_OS::memcpy (&node_id,
                  src.data4.get_buffer () + 2,
                  ACE_Utils::UUID_Node::NODE_ID_SIZE);

  return true;
}

//
// operator <<=
//
bool operator <<= (::OASIS::UUID & dst, const ACE_Utils::UUID & src)
{
  OASIS_TAO_TRACE ("bool operator <<= (::OASIS::UUID &, const ACE_Utils::UUID &)");

  // Insert the integer values of the UUID.
  dst.data1 = src.time_low ();
  dst.data2 = src.time_mid ();
  dst.data3 = src.time_hi_and_version ();

  // Insert the last chunk of the UUID.
  dst.data4.length (8);
  dst.data4[0] = src.clock_seq_hi_and_reserved ();
  dst.data4[1] = src.clock_seq_low ();

  ACE_OS::memcpy (dst.data4.get_buffer () + 2,
                  src.node ().node_ID (),
                  ACE_Utils::UUID_Node::NODE_ID_SIZE);

  return true;
}
