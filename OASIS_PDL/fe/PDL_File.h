// -*- C++ -*-

//=============================================================================
/**
 *  @file       PDL_File.h
 *
 *  $Id: PDL_File.h 1820 2011-08-08 23:58:09Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_FILE_H_
#define _OASIS_PDL_FILE_H_

#include <vector>
#include "PDL_Declaration.h"

/**
 * @class OASIS_PDL_Probe_Attr
 *
 * The attributes for a software probe. This is the information
 * that appears before a software probe's definition.
 */
class OASIS_PDL_FE_Export OASIS_PDL_File_Attr
{
public:
  /// Default constructor.
  OASIS_PDL_File_Attr (void);

  /// The major version number.
  int version_major_;

  /// The minor version number.
  int version_minor_;
};

/**
 * @class OASIS_PDL_File
 *
 * Base class for all declarations in the language.
 */
class OASIS_PDL_FE_Export OASIS_PDL_File :
  public OASIS_PDL_Declaration
{
public:
  /// Default constructor.
  OASIS_PDL_File (void);

  /// Destructor.
  virtual ~OASIS_PDL_File (void);

  virtual void accept (OASIS_PDL_Visitor & v) const;

  const std::vector <OASIS_PDL_Declaration *> & decls (void) const;

  void add_decl (OASIS_PDL_Declaration *);

  /// Get the file's attributes.
  const OASIS_PDL_File_Attr & attr (void) const;

  /// Get the file's attributes.
  OASIS_PDL_File_Attr & attr (void);

private:
  /// Collection of child declarations.
  std::vector <OASIS_PDL_Declaration *> decls_;

  /// Attributes about the file.
  OASIS_PDL_File_Attr attr_;
};

#if defined (__OASIS_INLINE__)
#include "PDL_File.inl"
#endif

#endif  // !defined _OASIS_PDL_DECLARATION_H_
