// $Id: Load_Configuration_Test.cpp 1851 2011-08-17 12:13:17Z hillj $

#include "ace/ARGV.h"
#include "ace/Log_Msg.h"

#include "oasis/EINode/Configuration.h"
#include "oasis/EINode/Standard_EINode.h"

//
// validate_einode_configuration
//
bool validate_einode_configuration (const OASIS::Einode_Configuration & config)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - validating configuration\n")));

  if (config.name () != "TestEINode")
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - expected %s; read %s\n"),
                       ACE_TEXT ("TestEINode"),
                       config.name ().c_str ()),
                       false);

  ACE_Utils::UUID expected_uuid ("A0F1C229-135F-4047-BADD-2DE55C75FBC2");
  if (config.uuid () != expected_uuid)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - expected %s; read %s\n"),
                       expected_uuid.to_string ()->c_str (),
                       config.uuid ().to_string ()->c_str ()),
                       false);

  static const char * data_channel_directive =
    "dynamic TaoChannel Service_Object * OASIS_Tao_Data_Channel_Client:_make_Tao_Data_Channel_Client () \" \"";

  if (config.data_channel ().directive_ != data_channel_directive)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read directive; ")
                       ACE_TEXT ("expected [%s]; read [%s]\n"),
                       data_channel_directive,
                       config.data_channel ().directive_.c_str ()),
                       false);

#define PROBE_COUNT 3

  static const std::string probes[PROBE_COUNT] =
  {
    "probe h1 Heartbeat_Software_Probe:_make_Heartbeat_Software_Probe_Factory () \" \"",
    "probe h2 Heartbeat_Software_Probe:_make_Heartbeat_Software_Probe_Factory () \" \"",
    "probe h3 Heartbeat_Software_Probe:_make_Heartbeat_Software_Probe_Factory () \" \""
  };

  if (config.data_channel ().probes_.size () != PROBE_COUNT)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - expected 3 probe(s); read %d\n"),
                       config.data_channel ().probes_.size ()),
                       false);

  //for (size_t i = 0; i < PROBE_COUNT; ++ i)
  //{
  //  if (config.data_channel ().probes_[i] != probes[i])
  //    ACE_ERROR_RETURN ((LM_ERROR,
  //                       ACE_TEXT ("%T (%t) - %M - failed to read probe; ")
  //                       ACE_TEXT ("expected [%s], read [%s]\n"),
  //                       probes[i],
  //                       config.data_channel ().probes_[i].c_str ()),
  //                       false);
  //}

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - validation complete\n")));

  return true;
}

//
// test_load_configuration_command_line
//
int test_load_configuration_command_line (void)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - executing test_load_configuration_command_line ()\n")));

  OASIS::Standard_EINode einode;
  ACE_ARGV_T <char> args;
  args.add ("test_load_configuration_command_line -c test.einode");

  einode.init (args.argc (), args.argv ());

  if (!validate_einode_configuration (einode.configuration ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - invalid configuration\n")),
                       -1);

  return 0;
}

//
// test_load_configuration_manually
//
int test_load_configuration_manually (void)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - executing test_load_configuration_manually ()\n")));

  OASIS::Standard_EINode einode;
  if (0 != einode.load_configuration ("test.einode"))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to load configuration\n")),
                       -1);

  if (!validate_einode_configuration (einode.configuration ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - invalid configuration\n")),
                       -1);

  return 0;
}

//
// main
//
int ACE_TMAIN (int argc, char * argv [])
{
  try
  {
    // Load the configuration from file.
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - loading einode configuration\n")));

    OASIS::Einode_Configuration config;
    if (!config.load_file ("test.einode"))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to load configuration\n")),
                         1);

    // Validate the loaded configuration.
    if (!validate_einode_configuration (config))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - invalid configuration\n")),
                         1);

    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - test executed successfully\n")));

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
                ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));
  }

  return 1;
}
