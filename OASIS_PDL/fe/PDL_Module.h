// -*- C++ -*-

//=============================================================================
/**
 *  @file       PDL_Module.h
 *
 *  $Id: PDL_Module.h 1716 2010-11-29 00:53:50Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_MODULE_H_
#define _OASIS_PDL_MODULE_H_

#include <vector>
#include "PDL_Declaration.h"

/**
 * @class OASIS_PDL_Declaration
 *
 * Base class for all declarations in the language.
 */
class OASIS_PDL_FE_Export OASIS_PDL_Module :
  public OASIS_PDL_Declaration
{
public:
  /// Default constructor.
  OASIS_PDL_Module (void);

  /// Destructor.
  virtual ~OASIS_PDL_Module (void);

  virtual void accept (OASIS_PDL_Visitor & v) const;

  const std::vector <OASIS_PDL_Declaration *> & decls (void) const;

  void add_decl (OASIS_PDL_Declaration *);

private:
  /// Collection of child declarations.
  std::vector <OASIS_PDL_Declaration *> decls_;
};

#if defined (__OASIS_INLINE__)
#include "PDL_Module.inl"
#endif

#endif  // !defined _OASIS_PDL_DECLARATION_H_
