// $Id: Probe_Schema_Generator.cpp 1896 2011-09-07 14:56:19Z hillj $

#include "Probe_Schema_Generator.h"
#include "Probe_Schema_Generator_Visitor.h"
#include "fe/PDL_Configuration.h"
#include "fe/PDL_File.h"

#include <fstream>
#include <sstream>

OASIS_PDL_BE_IMPL (_make_PDL_Schema_Generator, OASIS_PDL_Probe_Schema_Generator);

//
// OASIS_PDL_Probe_Schema_Generator
//
OASIS_PDL_Probe_Schema_Generator::OASIS_PDL_Probe_Schema_Generator (void)
{

}

//
// ~OASIS_PDL_Probe_Schema_Generator
//
OASIS_PDL_Probe_Schema_Generator::
~OASIS_PDL_Probe_Schema_Generator (void)
{

}

//
// parse_args
//
int OASIS_PDL_Probe_Schema_Generator::parse_args (int argc, char * argv [])
{
  return 0;
}

//
// generate
//
int OASIS_PDL_Probe_Schema_Generator::generate (const OASIS_PDL_File & file)
{
  std::ostringstream pathname;
  pathname << OASIS_PDL_CONFIGURATION::instance ()->outdir_
           << file.name () << ".xsd";

  std::ofstream xsdfile;
  xsdfile.open (pathname.str ().c_str ());

  if (!xsdfile.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                       pathname.str ().c_str ()),
                       -1);

  OASIS_PDL_Probe_Schema_Generator_Visitor v (xsdfile);
  file.accept (v);

  // Close the .xsd file.
  xsdfile.close ();

  return 0;
}
