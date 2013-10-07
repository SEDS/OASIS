// $Id: Export_File_Generator.cpp 1867 2011-08-22 21:14:42Z hillj $

#include "Export_File_Generator.h"
#include "Configuration.h"

#include "fe/PDL_Configuration.h"

#include <fstream>
#include <sstream>

namespace OASIS_PDL_BE
{
namespace Cpp
{

//
// Export_File_Generator
//
Export_File_Generator::Export_File_Generator (void)
{

}

//
// ~Export_File_Generator
//
Export_File_Generator::~Export_File_Generator (void)
{

}

//
// generate
//
bool Export_File_Generator::generate (void)
{
  // Locate the basename of the export macro.
  using OASIS_PDL_BE::Cpp::CONFIGURATION;
  const std::string & export_macro = CONFIGURATION::instance ()->export_macro_;
  std::string export_basename;

  size_t pos = export_macro.find ("_Export");
  if (pos != std::string::npos)
    export_basename = export_macro.substr (0, pos);

  std::ostringstream filename;
  filename
    << OASIS_PDL_CONFIGURATION::instance ()->outdir_
    << "/"
    << CONFIGURATION::instance ()->export_file_;

  std::ofstream fout;
  fout.open (filename.str ().c_str ());

  if (!fout.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open %s for writing\n"),
                       filename.str ().c_str ()),
                       false);

  fout
    << "// -*- C++ -*-" << std::endl
    << "// ------------------------------" << std::endl
    << std::endl
    << "#ifndef _" << export_basename << "_EXPORT_H" << std::endl
    << "#define _" << export_basename << "_EXPORT_H" << std::endl
    << std::endl
    << "#include \"ace/config-all.h\"" << std::endl
    << "#include \"oasis/config.h\"" << std::endl
    << std::endl
    << "#if defined (ACE_AS_STATIC_LIBS) && !defined (" << export_basename << "_HAS_DLL)" << std::endl
    << "#  define " << export_basename << "_HAS_DLL 0" << std::endl
    << "#endif /* ACE_AS_STATIC_LIBS && " << export_basename << "_HAS_DLL */" << std::endl
    << std::endl
    << "#if !defined (" << export_basename << "_HAS_DLL)" << std::endl
    << "#  define " << export_basename << "_HAS_DLL 1" << std::endl
    << "#endif /* ! " << export_basename << "_HAS_DLL */" << std::endl
    << std::endl
    << "#if defined (" << export_basename << "_HAS_DLL) && (" << export_basename << "_HAS_DLL == 1)" << std::endl
    << "#  if defined (" << export_basename << "_BUILD_DLL)" << std::endl
    << "#    define " << export_basename << "_Export ACE_Proper_Export_Flag" << std::endl
    << "#    define " << export_basename << "_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)" << std::endl
    << "#    define " << export_basename << "_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)" << std::endl
    << "#  else /* " << export_basename << "_BUILD_DLL */" << std::endl
    << "#    define " << export_basename << "_Export ACE_Proper_Import_Flag" << std::endl
    << "#    define " << export_basename << "_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)" << std::endl
    << "#    define " << export_basename << "_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)" << std::endl
    << "#  endif /* " << export_basename << "_BUILD_DLL */" << std::endl
    << "#else /* " << export_basename << "_HAS_DLL == 1 */" << std::endl
    << "#  define " << export_basename << "_Export" << std::endl
    << "#  define " << export_basename << "_SINGLETON_DECLARATION(T)" << std::endl
    << "#  define " << export_basename << "_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)" << std::endl
    << "#endif /* " << export_basename << "_HAS_DLL == 1 */" << std::endl
    << std::endl
    << "// Set " << export_basename << "_NTRACE = 0 to turn on library specific tracing even if" << std::endl
    << "// tracing is turned off for ACE." << std::endl
    << "#if !defined (" << export_basename << "_NTRACE)" << std::endl
    << "#  if (ACE_NTRACE == 1)" << std::endl
    << "#    define " << export_basename << "_NTRACE 1" << std::endl
    << "#  else /* (ACE_NTRACE == 1) */" << std::endl
    << "#    define " << export_basename << "_NTRACE 0" << std::endl
    << "#  endif /* (ACE_NTRACE == 1) */" << std::endl
    << "#endif /* !" << export_basename << "_NTRACE */" << std::endl
    << std::endl
    << "#if (" << export_basename << "_NTRACE == 1)" << std::endl
    << "#  define " << export_basename << "_TRACE(X)" << std::endl
    << "#else /* (" << export_basename << "_NTRACE == 1) */" << std::endl
    << "#  if !defined (ACE_HAS_TRACE)" << std::endl
    << "#    define ACE_HAS_TRACE" << std::endl
    << "#  endif /* ACE_HAS_TRACE */" << std::endl
    << "#  define " << export_basename << "_TRACE(X) ACE_TRACE_IMPL(X)" << std::endl
    << "#  include \"ace/Trace.h\"" << std::endl
    << "#endif /* (" << export_basename << "_NTRACE == 1) */" << std::endl
    << std::endl
    << "#endif /* " << export_basename << "_EXPORT_H */" << std::endl
    << std::endl
    << "// End of auto generated file." << std::endl;

  // Close the output file.
  fout.close ();

  return true;
}

}
}
