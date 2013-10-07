// $Id: driver.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "inheritanceImpl.h"
#include "inheritance.h"
#include "oasis/DataChannel/Latest_Local_Data_Channel.h"

//
// evaluate_Test_B
//
bool evaluate_Test_B (void)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - executing evaluate_Test_B ()\n")));

  // Register the software probe with the EINode.
  Test::BImpl b_probe_impl;

  // Set the software probe's local data channel.
  OASIS::Latest_Local_Data_Channel channel;
  b_probe_impl.set_data_channel (&channel);

  const int a_val = 45;
  const int b_val = 67;

  b_probe_impl.a_value (a_val);
  b_probe_impl.b_value (b_val);

  if (0 != b_probe_impl.flush ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to flush %s probe\n"),
                       b_probe_impl.__metadata__.type_info_.c_str ()),
                       false);

  // Recall the data received on the data channel.
  Test::B b_probe_dup;
  if (0 != b_probe_dup.recall (channel.get_data (),
                               channel.get_data_length (),
                               ACE_CDR::BYTE_ORDER_NATIVE))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to recall data\n")),
                       false);
  }

  // Validate the recalled data.
  if (b_probe_impl.a_value () != b_probe_dup.a_value ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled a_value () is not equal\n")),
                       false);

  if (b_probe_impl.b_value () != b_probe_dup.b_value ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled a_value () is not equal\n")),
                       false);

  return true;
}

//
// evaluate_Test_C
//
bool evaluate_Test_C (void)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - executing evaluate_Test_C ()\n")));

  // Register the software probe with the EINode.
  Test::CImpl c_probe_impl;

  // Set the software probe's local data channel.
  OASIS::Latest_Local_Data_Channel channel;
  c_probe_impl.set_data_channel (&channel);

  const int a_val = 45;
  const int b_val = 67;
  const int c_val = 456;

  c_probe_impl.a_value (a_val);
  c_probe_impl.b_value (b_val);
  c_probe_impl.c_value (c_val);

  if (0 != c_probe_impl.flush ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to flush %s probe\n"),
                       c_probe_impl.__metadata__.type_info_.c_str ()),
                       false);

  // Recall the data received on the data channel.
  Test::C c_probe_dup;
  if (0 != c_probe_dup.recall (channel.get_data (),
                               channel.get_data_length (),
                               ACE_CDR::BYTE_ORDER_NATIVE))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to recall data\n")),
                       false);
  }

  // Validate the recalled data.
  if (c_probe_impl.a_value () != c_probe_dup.a_value ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled a_value () is not equal\n")),
                       false);

  if (c_probe_impl.b_value () != c_probe_dup.b_value ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled b_value () is not equal\n")),
                       false);

  if (c_probe_impl.c_value () != c_probe_dup.c_value ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - recalled c_value () is not equal\n")),
                       false);

  return true;
}

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  if (!evaluate_Test_B ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - evaluate_Test_B () failed\n")),
                       1);

  if (!evaluate_Test_C ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - evaluate_Test_C () failed\n")),
                       1);

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - successfully recalled probe data\n")));

  return 0;
}
