// -*- C++ -*-

//=============================================================================
/**
 *  @file       PDL_Struct.h
 *
 *  $Id: PDL_Struct.h 1716 2010-11-29 00:53:50Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_STRUCT_H_
#define _OASIS_PDL_STRUCT_H_

#include "PDL_Complex_Type.h"

/**
 * @class OASIS_PDL_Struct
 *
 * Base class for all declarations in the language.
 */
class OASIS_PDL_FE_Export OASIS_PDL_Struct :
  public OASIS_PDL_Complex_Type
{
public:
  /// Default constructor.
  OASIS_PDL_Struct (void);

  /// Destructor.
  virtual ~OASIS_PDL_Struct (void);

  virtual void accept (OASIS_PDL_Visitor & v) const;
};

#if defined (__OASIS_INLINE__)
#include "PDL_Struct.inl"
#endif

#endif  // !defined _OASIS_PDL_DECLARATION_H_
