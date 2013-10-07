// $Id: Probe_Csharp_Generator.cpp 2118 2012-01-13 20:29:17Z dpuranik $

#include "Probe_Csharp_Generator.h"
#include "Probe_Csharp_Generator_Visitor.h"

#include "fe/PDL_Configuration.h"
#include "fe/PDL_File.h"

#include "CCF/CodeGenerationKit/IndentationCxx.hpp"
#include "CCF/CodeGenerationKit/IndentationImplanter.hpp"

#include "ace/Get_Opt.h"
#include "ace/OS_NS_string.h"
#include "ace/Process.h"

#include <fstream>
#include <sstream>

//
// OASIS_PDL_Probe_Csharp_Generator
//
OASIS_PDL_Probe_Csharp_Generator::OASIS_PDL_Probe_Csharp_Generator (void)
{

}

//
// ~OASIS_PDL_Probe_Cpp_Generator
//
OASIS_PDL_Probe_Csharp_Generator::~OASIS_PDL_Probe_Csharp_Generator (void)
{

}

//
// parse_args
//
int OASIS_PDL_Probe_Csharp_Generator::parse_args (int argc, char * argv [])
{
  return 0;
}

//
// generate
//
int OASIS_PDL_Probe_Csharp_Generator::generate (const OASIS_PDL_File & file)
{
  // Construct the header and source filename.
  std::ostringstream source_filename;

  source_filename << file.name () << ".cs";

  std::ofstream csfile;

  // Open the source file for writing.
  csfile.open (source_filename.str ().c_str ());

  if (!csfile.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                       source_filename.str ().c_str ()),
                       -1);

  do
  {
    // Declare the implanters for the generator.
    typedef Indentation::Implanter <Indentation::Cxx, char> Implanter;

    Implanter csfile_implanter (csfile);

    OASIS_PDL_Probe_Csharp_Generator_Visitor v (csfile);
    file.accept (v);
  } while (0);

  // Close the file before leaving.
  csfile.close ();

  return 0;
}
