// $Id: Probe_Cpp_Generator.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "Probe_Cpp_Generator.h"

#include "Configuration.h"
#include "Export_File_Generator.h"
#include "Stub_Probe_Cpp_Generator_Visitor.h"
#include "Impl_Probe_Cpp_Generator_Visitor.h"
#include "Metadata_Cpp_Generator_Visitor.h"

#include "fe/PDL_Configuration.h"
#include "fe/PDL_File.h"

#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

#include "ace/Get_Opt.h"
#include "ace/OS_NS_string.h"
#include "ace/Process.h"

#include <fstream>
#include <sstream>

OASIS_PDL_BE_IMPL (_make_PDL_Cpp_Generator, OASIS_PDL_Probe_Cpp_Generator);

//
// OASIS_PDL_Probe_Cpp_Generator
//
OASIS_PDL_Probe_Cpp_Generator::OASIS_PDL_Probe_Cpp_Generator (void)
{

}

//
// ~OASIS_PDL_Probe_Cpp_Generator
//
OASIS_PDL_Probe_Cpp_Generator::~OASIS_PDL_Probe_Cpp_Generator (void)
{

}

//
// parse_args
//
int OASIS_PDL_Probe_Cpp_Generator::parse_args (int argc, char * argv [])
{
  const char * optargs = "";

  ACE_Get_Opt get_opt (argc, argv, optargs);

  get_opt.long_option ("export-file", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("export-macro", ACE_Get_Opt::ARG_REQUIRED);

  int opt = 0;

  while (EOF != (opt = get_opt ()))
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("export-file", get_opt.long_option ()))
      {
        OASIS_PDL_BE::Cpp::CONFIGURATION::instance ()->export_file_ = get_opt.opt_arg ();
      }
      else if (0 == ACE_OS::strcmp ("export-macro", get_opt.long_option ()))
      {
        OASIS_PDL_BE::Cpp::CONFIGURATION::instance ()->export_macro_ = get_opt.opt_arg ();
      }
      break;
    }
  }

  return 0;

  ACE_UNUSED_ARG (argc);
  ACE_UNUSED_ARG (argv);
}

//
// generate
//
int OASIS_PDL_Probe_Cpp_Generator::generate (const OASIS_PDL_File & file)
{
  if (0 != this->generate_metadata (file))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to generate metadata file\n")),
                       -1);
  }

  if (0 != this->generate_stub (file))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to generate stub file\n")),
                       -1);
  }

  if (0 != this->generate_impl (file))
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to generate impl file\n")),
                       -1);
  }

  // Finally, generate the export file.
  OASIS_PDL_BE::Cpp::Export_File_Generator export_gen;

  using OASIS_PDL_BE::Cpp::CONFIGURATION;

  if (CONFIGURATION::instance ()->has_export () && !export_gen.generate ())
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to generate export file\n")),
                       -1);
  }


  return 0;
}

//
// generate_stub
//
int OASIS_PDL_Probe_Cpp_Generator::generate_stub (const OASIS_PDL_File & file)
{
  // Construct the header and source filename.
  std::ostringstream source_filename, header_filename;
  header_filename << OASIS_PDL_CONFIGURATION::instance ()->outdir_
                  << file.name () << ".h";

  source_filename << OASIS_PDL_CONFIGURATION::instance ()->outdir_
                  << file.name () << ".cpp";

  std::ofstream hfile, cppfile;

  // Open the header file for writing.
  hfile.open (header_filename.str ().c_str ());

  if (!hfile.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                       header_filename.str ().c_str ()),
                       -1);

  // Open the source file for writing.
  cppfile.open (source_filename.str ().c_str ());

  if (!cppfile.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                       source_filename.str ().c_str ()),
                       -1);

  do
  {
    // Declare the implanters for the generator.
    typedef Indentation::Implanter <Indentation::Cxx, char> Implanter;

    Implanter cppfile_implanter (cppfile);
    Implanter hfile_implanter (hfile);

    OASIS_PDL_Stub_Probe_Cpp_Generator_Visitor v (hfile, cppfile);
    file.accept (v);
  } while (0);

  // Close the files before leaving.
  hfile.close ();
  cppfile.close ();

  return 0;
}

//
// generate_impl
//
int OASIS_PDL_Probe_Cpp_Generator::generate_impl (const OASIS_PDL_File & file)
{
  // Construct the header and source filename.
  std::ostringstream source_filename, header_filename;
  header_filename << OASIS_PDL_CONFIGURATION::instance ()->outdir_
                  << file.name () << "Impl.h";

  source_filename << OASIS_PDL_CONFIGURATION::instance ()->outdir_
                  << file.name () << "Impl.cpp";

  std::ofstream hfile, cppfile;

  // Open the header file for writing.
  hfile.open (header_filename.str ().c_str ());

  if (!hfile.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                       header_filename.str ().c_str ()),
                       -1);

  // Open the source file for writing.
  cppfile.open (source_filename.str ().c_str ());

  if (!cppfile.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                       source_filename.str ().c_str ()),
                       -1);

  do
  {
    // Declare the implanters for the generator.
    typedef Indentation::Implanter <Indentation::Cxx, char> Implanter;

    Implanter cppfile_implanter (cppfile);
    Implanter hfile_implanter (hfile);

    OASIS_PDL_Impl_Probe_Cpp_Generator_Visitor v (hfile, cppfile);
    file.accept (v);
  } while (0);

  // Close the files before leaving.
  hfile.close ();
  cppfile.close ();

  return 0;
}

//
// generate_metadata
//
int OASIS_PDL_Probe_Cpp_Generator::generate_metadata (const OASIS_PDL_File & file)
{
  // Construct the header and source filename.
  std::ostringstream source_filename, header_filename;
  header_filename << OASIS_PDL_CONFIGURATION::instance ()->outdir_
                  << file.name () << "_Metadata.h";

  source_filename << OASIS_PDL_CONFIGURATION::instance ()->outdir_
                  << file.name () << "_Metadata.cpp";

  std::ofstream hfile, cppfile;

  // Open the header file for writing.
  hfile.open (header_filename.str ().c_str ());

  if (!hfile.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                       header_filename.str ().c_str ()),
                       -1);

  // Open the source file for writing.
  cppfile.open (source_filename.str ().c_str ());

  if (!cppfile.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                       source_filename.str ().c_str ()),
                       -1);

  do
  {
    // Declare the implanters for the generator.
    typedef Indentation::Implanter <Indentation::Cxx, char> Implanter;

    Implanter cppfile_implanter (cppfile);
    Implanter hfile_implanter (hfile);

    OASIS_PDL_Metadata_Cpp_Generator_Visitor v (hfile, cppfile);
    file.accept (v);
  } while (0);

  // Close the files before leaving.
  hfile.close ();
  cppfile.close ();

  return 0;
}
