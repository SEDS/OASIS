// $Id: OASIS_PDL_App.cpp 2034 2011-10-31 18:15:00Z dfeiock $

#include "OASIS_PDL_App.h"
#include "OASIS_PDL_Parser.h"

#include "fe/PDL_File.h"
#include "fe/PDL_Configuration.h"
#include "be/PDL_Backend_Manager.h"
#include "be/PDL_Backend.h"

// Default backend generators
#include "be/tdl/Tdl_Generator.h"
#include "be/schema/Probe_Schema_Generator.h"
#include "be/cpp/Probe_Cpp_Generator.h"

#include "ace/Get_Opt.h"
#include "ace/OS_NS_string.h"
#include "ace/streams.h"

#include "boost/bind.hpp"

#include <fstream>

//
// OASIS_PDL_App
//
OASIS_PDL_App::OASIS_PDL_App (void)
: generate_schema_ (false),
  print_help_ (false)
{

}

//
// ~OASIS_PDL_App
//
OASIS_PDL_App::~OASIS_PDL_App (void)
{

}

//
// run_main
//
int OASIS_PDL_App::run_main (int argc, char * argv [])
{
  // Parse the command-line arguments.
  if (0 != this->parse_args (argc, argv))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to parse arguments\n")),
                       -1);

  std::auto_ptr <OASIS_PDL_Backend> pdl_backend (this->get_backend ());

  if (0 == pdl_backend.get ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to load backend\n")),
                       -1);

  // Open the file for reading/parsing.
  if (0 != pdl_backend->parse_args (argc, argv))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to parse backend arguments\n")),
                       -1);

  std::for_each (this->input_.begin (),
                 this->input_.end (),
                 boost::bind (&OASIS_PDL_App::process_file,
                              this,
                              argc,
                              argv,
                              _1,
                              pdl_backend.get ()));

  return 0;
}

//
// parse_args
//
int OASIS_PDL_App::parse_args (int argc, char * argv [])
{
  const char * optstr = "o:hl";

  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("backend", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("generate-schema", ACE_Get_Opt::NO_ARG);

  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("list", 'l', ACE_Get_Opt::NO_ARG);

  int opt = 0;
  OASIS_PDL_Configuration * pdl_config = OASIS_PDL_CONFIGURATION::instance ();

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("backend", get_opt.long_option ()))
      {
        this->backend_ = get_opt.opt_arg ();
      }
      else if (0 == ACE_OS::strcmp ("generate-schema", get_opt.long_option ()))
      {
        this->generate_schema_ = true;
      }
      else if (0 == ACE_OS::strcmp ("list", get_opt.long_option ()))
      {
        this->list_backends ();
      }
      else if (0 == ACE_OS::strcmp ("help", get_opt.long_option ()))
      {
        this->print_help_ = true;
      }
      break;

    case 'o':
      pdl_config->outdir_ = get_opt.opt_arg ();
      break;

    case 'l':
      this->list_backends ();
      break;

    case 'h':
      this->print_help_ = true;
      break;
    }
  }

  if (this->print_help_)
    this->print_help ();

  if (this->backend_.empty ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - --backend is missing\n")),
                       -1);

  // The unknown/unused arguments are the input files.
  argv = get_opt.argv ();
  argc = get_opt.argc ();

  for (int i = get_opt.opt_ind (); i < argc; ++ i)
    this->input_.insert (argv[i]);

  return 0;
}

//
// process_file
//
int OASIS_PDL_App::
process_file (int argc,
              char * argv [],
              const std::string & filename,
              OASIS_PDL_Backend * pdl_backend) const
{
  // Open the file for reading/parsing.
  std::ifstream infile;
  infile.open (filename.c_str ());

  if (!infile.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                       filename.c_str ()),
                       -1);

  // Parse the specified file.
  const size_t ext = filename.find_last_of ('.');
  size_t name = filename.find_last_of (ACE_DIRECTORY_SEPARATOR_CHAR);

  if (name == std::string::npos)
    name = -1;

  OASIS_PDL_File file;
  file.name (filename.substr (name + 1, ext - name - 1));

  OASIS_PDL_Parser parser;
  if (!parser.parse_file (infile, file))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to parse %s\n"),
                       filename.c_str ()),
                       -1);

  if (0 != pdl_backend->generate (file))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - backend failed for %s\n"),
                       filename.c_str ()),
                       -1);

  if (this->generate_schema_)
  {
    // Generate the schema definition for this file.
    OASIS_PDL_Probe_Schema_Generator schema_gen;

    // Parse the command-line arguments.
    if (0 != schema_gen.parse_args (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to parse backend arguments\n")),
                         -1);

    // Execute the generator.
    schema_gen.generate (file);
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to generate schema\n")),
                         -1);
  }

  return 0;
}

//
// print_help
//
void OASIS_PDL_App::print_help (void)
{
  static const char * __HELP__ =
    "OASIS probe definition language (PDL) compiler\n"
    "\n"
    "USAGE: oasis_pdl [OPTIONS] FILES\n"
    "\n"
    "General Options:\n"
    "  --backend=TARGET\t\tTarget backend generator (required)\n"
    "  --generate-schema\t\tGenerate XML Schema Definition files\n"
    "  -l, -list\t\tList available backends\n";

  // Print the first part of the help.
  std::cerr << __HELP__;

  // Print the backend help, if applicable.
  std::auto_ptr <OASIS_PDL_Backend> pdl_backend (this->get_backend ());

  if (0 != pdl_backend.get ())
  {
    cerr
      << std::endl
      << "Backend Options:\n";

    pdl_backend->print_help ();
  }

  // Print the remaining help.
  std::cerr
    << std::endl
    << "Print Options:" << std::endl
    << "  -h, --help\t\t\tPrint this help message" << std::endl
    << std::endl;

  ACE_OS::exit (1);
}

//
// list_backends
//
void OASIS_PDL_App::list_backends (void)
{
  std::cerr
    << "Available backends:" << std::endl
    << std::endl
    << " Type         Description" << std::endl
    << " --------     ----------------------------" << std::endl
    << " cpp          C++" << std::endl
    << " tdl          TENA Definition Language" << std::endl;

  ACE_OS::exit (0);
}

//
// get_backend
//
OASIS_PDL_Backend * OASIS_PDL_App::get_backend (void)
{
  OASIS_PDL_Backend * pdl_backend = 0;

  if (this->backend_ == "cpp")
  {
    ACE_NEW_RETURN (pdl_backend,
                    OASIS_PDL_Probe_Cpp_Generator (),
                    pdl_backend);
  }
  else if (this->backend_ == "tdl")
  {
    ACE_NEW_RETURN (pdl_backend,
                    OASIS_PDL_Tdl_Generator (),
                    pdl_backend);
  }

  return pdl_backend;

}
