// -*- C++ -*-

//=============================================================================
/**
 * @file      Attribute_Generator.h
 *
 *  $Id: Configuration.h 1867 2011-08-22 21:14:42Z hillj $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_BE_CPP_CONFIGURATION_H_
#define _OASIS_PDL_BE_CPP_CONFIGURATION_H_

#include <string>
#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"

namespace OASIS_PDL_BE
{
namespace Cpp
{

/**
 * @struct Configuration
 *
 * Configuration for the C++ backend generator.
 */
struct Configuration
{
  /// The export macro for the file.
  std::string export_macro_;

  /// The file containing the export macro.
  std::string export_file_;

  /// Test if the configuration has an export.
  bool has_export (void) const
  {
    return !this->export_macro_.empty ();
  }
};

typedef ACE_Singleton <Configuration, ACE_Null_Mutex> CONFIGURATION;

}
}

#endif  // !defined _OASIS_PDL_BE_CPP_CONFIGURATION_H_