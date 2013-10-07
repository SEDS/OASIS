// -*- C++ -*-

//=============================================================================
/**
 *  @file       PDL_Vector_Type.h
 *
 *  $Id: PDL_Vector_Type.h 1896 2011-09-07 14:56:19Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_VECTOR_TYPE_H_
#define _OASIS_PDL_VECTOR_TYPE_H_

#include "PDL_Type.h"

/**
 * @class OASIS_PDL_Complex_Type
 *
 * Base class for all declarations in the language.
 */
class OASIS_PDL_FE_Export OASIS_PDL_Vector_Type :
  public OASIS_PDL_Type
{
public:
  /// Default constructor.
  OASIS_PDL_Vector_Type (void);

  /// Destructor.
  virtual ~OASIS_PDL_Vector_Type (void);

  /// Set the vector's type.
  void type (OASIS_PDL_Type * t);

  /// Get the vector's type.
  OASIS_PDL_Type * type (void) const;

  /// Accept the visitor.
  virtual void accept (OASIS_PDL_Visitor & v) const;

private:
  /// The vector's element type.
  OASIS_PDL_Type * type_;
};

#if defined (__OASIS_INLINE__)
#include "PDL_Vector_Type.inl"
#endif

#endif  // !defined _OASIS_PDL_VECTOR_TYPE_H_
