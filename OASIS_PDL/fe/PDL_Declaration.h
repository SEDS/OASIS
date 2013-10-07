// -*- C++ -*-

//=============================================================================
/**
 *  @file       PDL_Declaration.h
 *
 *  $Id: PDL_Declaration.h 1820 2011-08-08 23:58:09Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_DECLARATION_H_
#define _OASIS_PDL_DECLARATION_H_

#include <string>
#include "oasis/config.h"

#include "PDL_FE_export.h"

// Forward decl.
class OASIS_PDL_Visitor;

/**
 * @class OASIS_PDL_Declaration
 *
 * Base class for all declarations in the language.
 */
class OASIS_PDL_FE_Export OASIS_PDL_Declaration
{
public:
  /// Default constructor.
  OASIS_PDL_Declaration (void);

  /// Destructor.
  virtual ~OASIS_PDL_Declaration (void);

  virtual void accept (OASIS_PDL_Visitor & v) const = 0;

  const std::string & name (void) const;

  void name (const std::string & name);

  std::string fq_name (const std::string & separator = "::") const;

  std::string scope (const std::string & separator = "::") const;

  OASIS_PDL_Declaration * parent (void) const;

  void parent (OASIS_PDL_Declaration * p);

protected:
  /// Name of the declaration.
  std::string name_;

  /// The parent of this declaration.
  OASIS_PDL_Declaration * parent_;
};

#if defined (__OASIS_INLINE__)
#include "PDL_Declaration.inl"
#endif

#endif  // !defined _OASIS_PDL_DECLARATION_H_
