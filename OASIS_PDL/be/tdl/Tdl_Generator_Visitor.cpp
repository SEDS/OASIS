// $Id: Tdl_Generator_Visitor.cpp 1824 2011-08-10 14:42:58Z hillj $

#include "Tdl_Generator_Visitor.h"

#if !defined (__OASIS_INLINE__)
#include "Tdl_Generator_Visitor.inl"
#endif

#include "Tdl_Type_Generator.h"
#include "Tdl_Probe_Generator.h"

#include "fe/PDL_Configuration.h"
#include "fe/PDL_File.h"
#include "fe/PDL_Module.h"
#include "fe/PDL_Probe.h"

#include "boost/bind.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>

//
// visit_file
//
void OASIS_PDL_Tdl_Generator_Visitor::
visit_file (const OASIS_PDL_File & file)
{
  // Open the container file for writing.
  std::ostringstream filename;
  filename
    << OASIS_PDL_CONFIGURATION::instance ()->outdir_
    << "OASIS-" << file.name () << "-v"
    << file.attr ().version_major_ << "." << file.attr ().version_minor_
    << ".tdl";

  std::ofstream tdl_file;
  tdl_file.open (filename.str ().c_str ());

  if (tdl_file.is_open ())
  {
    OASIS_PDL_Tdl_Probe_Generator probe_gen (tdl_file);
    file.accept (probe_gen);
  }
  else
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - failed to open %s\n"),
                filename.str ().c_str ()));
}

