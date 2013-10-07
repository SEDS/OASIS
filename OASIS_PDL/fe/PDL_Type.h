// -*- C++ -*-

//=============================================================================
/**
 *  @file       PDL_Type.h
 *
 *  $Id: PDL_Type.h 1716 2010-11-29 00:53:50Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_TYPE_H_
#define _OASIS_PDL_TYPE_H_

#include "PDL_Declaration.h"

/**
 * @class OASIS_PDL_Declaration
 *
 * Base class for all declarations in the language.
 */
class OASIS_PDL_FE_Export OASIS_PDL_Type :
  public OASIS_PDL_Declaration
{
public:
  /// Default constructor.
  OASIS_PDL_Type (void);

  /// Destructor.
  virtual ~OASIS_PDL_Type (void);
};

#if defined (__OASIS_INLINE__)
#include "PDL_Type.inl"
#endif

#endif  // !defined _OASIS_PDL_DECLARATION_H_
