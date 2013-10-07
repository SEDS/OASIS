// $Id: Command_Injector_App.cpp 2034 2011-10-31 18:15:00Z dfeiock $

#include "Command_Injector_App.h"
#include "Command_Parser.h"

#include "ace/Get_Opt.h"
#include "ace/streams.h"

#include "boost/bind.hpp"

#include <algorithm>

static const char * __HELP__ =
"Basic command injector for OASIS\n"
"\n"
"USAGE: oasis_cmd -ORBInitRef TEM=LOCATION [OPTIONS] \"COMMAND\"\n"
"\n"
"General options:\n"
"  -h, --help                   Print this help message\n"
"\n"
"\n"
"Additional information:\n"
"LOCATION is the location of the Test Execution Manager. The location\n"
"needs to be a value that is resolvable using the TAO string_to_object()\n"
"method. Examples of such resolvable values include:\n"
"\n"
" * corbaloc:         - IOR table location\n"
" * corbaname:        - Naming service location\n"
" * file://           - IOR file location\n"
"\n"
"COMMAND is the command sent to a software probe. The format of the COMMAD\n"
"is as follows:\n"
"\n"
"  [DAC].[EINODE].[PROBE] [ARGS]\n"
"\n"
"where DAC, EINODE, and PROBE is the name of the target Data Acquisition\n"
"Controller, EI node, and software probe, respectively. Finally, ARGS is the\n"
"command arguments sent to the software probe.\n"
"\n"
"NOTE: The COMMAND parameter must be placed in quotation marks.\n";

namespace OASIS
{

//
// Command_Injector_App
//
Command_Injector_App::Command_Injector_App (void)
{

}

//
// ~Command_Injector_App
//
Command_Injector_App::~Command_Injector_App (void)
{

}

//
// run_main
//
int Command_Injector_App::run_main (int argc, char * argv [])
{
  try
  {
    // Parse the command line arguments.
    if (0 != this->parse_args (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to parse ")
                         ACE_TEXT ("command-line options\n")),
                         -1);

    // Resolve the TestExecutionManager reference.
    ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("TEM");
    if (CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve TEM\n")),
                         -1);

    TestExecutionManager_var tem = TestExecutionManager::_narrow (obj.in ());

    if (CORBA::is_nil (tem.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - object is not a ")
                         ACE_TEXT ("TestExecutionManager object\n")),
                         -1);

    // Now, locate the DAC in the command.
    std::for_each (this->commands_.begin (),
                   this->commands_.end (),
                   boost::bind (&Command_Injector_App::execute_command,
                                this,
                                tem.in (),
                                _1));

    // Destroy the ORB.
    this->orb_->destroy ();

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
// parse_args
//
int Command_Injector_App::parse_args (int argc, char * argv [])
{
  // Initialize the ORB first. This will remove all CORBA
  // specific command-line arguments.
  this->orb_ = ::CORBA::ORB_init (argc, argv);

  const char * opts = "h";
  ACE_Get_Opt get_opt (argc, argv);

  get_opt.long_option ("help", 'h');

  int ch = 0;
  while (EOF != (ch = get_opt ()))
  {
    switch (ch)
    {
    case 0:
      if (0 != ACE_OS::strcmp ("help", get_opt.long_option ()))
        this->print_help ();

      break;

    case 'h':
      this->print_help ();
      break;
    }
  }

  for (int i = get_opt.opt_ind (); i < get_opt.argc (); ++ i)
    this->commands_.push_back (get_opt.argv ()[i]);

  return 0;
}

//
// print_help
//
void Command_Injector_App::print_help (void)
{
  std::cerr << __HELP__ << std::endl;
  ACE_OS::exit (1);
}

//
// execute_command
//
int Command_Injector_App::
execute_command (TestExecutionManager_ptr tem, const std::string & command)
{
  // Parse the provided command line.
  Command_Parser_Result result;
  Command_Parser parser;

  if (!parser.parse (command, result))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to parse '%s'\n"),
                       command.c_str ()),
                       -1);

  // Locate the DAC.
  DataAcquisitionControllerSeq_var the_DACs = tem->get_DACs ();
  CORBA::ULong count = the_DACs->length ();

  for (CORBA::ULong i = 0; i < count; ++ i)
  {
    // Get the name of the current DAC.
    DataAcquisitionController_ptr the_DAC = the_DACs[i];
    CORBA::String_var name = the_DAC->name ();

    if (0 == ACE_OS::strcmp (name.in (), result.dac_name_.c_str ()))
    {
      ACE_ERROR ((LM_INFO,
                  ACE_TEXT ("%T (%t) - %M - sending command string to %s\n"),
                  result.dac_name_.c_str ()));

      the_DAC->send_command (result.einode_name_.c_str (),
                             result.command_.c_str ());

      return 0;
    }
  }

  ACE_ERROR ((LM_ERROR,
              ACE_TEXT ("%T (%t) - %M - %s is not a valid DAC name\n"),
              result.dac_name_.c_str ()));

  return -1;
}

//
// shutdown
//
void Command_Injector_App::shutdown (void)
{
  try
  {
    if (!::CORBA::is_nil (this->orb_.in ()))
      this->orb_->shutdown ();
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - unknown exception at shutdown\n")));
  }
}

}
