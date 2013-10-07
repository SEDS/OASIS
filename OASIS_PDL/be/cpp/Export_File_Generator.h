// -*- C++ -*-

//=============================================================================
/**
 * @file      Export_File_Generator.h
 *
 *  $Id: Export_File_Generator.h 1867 2011-08-22 21:14:42Z hillj $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_BE_CPP_EXPORT_FILE_GENERATOR_H_
#define _OASIS_PDL_BE_CPP_EXPORT_FILE_GENERATOR_H_

#include "fe/PDL_Visitor.h"
#include <ostream>

namespace OASIS_PDL_BE
{
namespace Cpp
{
/**
 * @class Export_File_Generator
 *
 * The export file generator for C++. The generated file contains the
 * export macros for a given library.
 */
class Export_File_Generator
{
public:
  /// Default constructor.
  Export_File_Generator (void);

  /// Destructor.
  ~Export_File_Generator (void);

  /// Generate the export file.
  bool generate (void);
};

}
}

#endif
