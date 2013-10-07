// -*- C++ -*-

//=============================================================================
/**
 *  @file       PDL_Complex_Type.h
 *
 *  $Id: PDL_Complex_Type.h 1896 2011-09-07 14:56:19Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_COMPLEX_TYPE_H_
#define _OASIS_PDL_COMPLEX_TYPE_H_

#include <vector>
#include "PDL_Type.h"

/**
 * @class OASIS_PDL_Complex_Type
 *
 * Base class for all declarations in the language.
 */
class OASIS_PDL_FE_Export OASIS_PDL_Complex_Type_Member :
  public OASIS_PDL_Declaration
{
public:
  /// Default constructor.
  OASIS_PDL_Complex_Type_Member (void);

  /// Destructor.
  virtual ~OASIS_PDL_Complex_Type_Member (void);

  /// Accept the visitor.
  void accept (OASIS_PDL_Visitor & v) const;

  /// Get the complex member type.
  OASIS_PDL_Type * type (void) const;

  /// Set the complex member type.
  void type (OASIS_PDL_Type * t);

private:
  /// The member's actual type.
  OASIS_PDL_Type * type_;
};

/**
 * @class OASIS_PDL_Complex_Type
 *
 * Base class for all declarations in the language.
 */
class OASIS_PDL_FE_Export OASIS_PDL_Complex_Type :
  public OASIS_PDL_Type
{
public:
  /// Default constructor.
  OASIS_PDL_Complex_Type (void);

  /// Destructor.
  virtual ~OASIS_PDL_Complex_Type (void);

  /// Get the elements if the complex type.
  const std::vector <OASIS_PDL_Complex_Type_Member *> & members (void) const;

  /// Add a new element to the complex type.
  void add_member (OASIS_PDL_Complex_Type_Member * type);

  /// Create a new member element.
  OASIS_PDL_Complex_Type_Member * new_member (void);

private:
  /// Collection of members in the complex type.
  std::vector <OASIS_PDL_Complex_Type_Member *> members_;
};

#if defined (__OASIS_INLINE__)
#include "PDL_Complex_Type.inl"
#endif

#endif  // !defined _OASIS_PDL_DECLARATION_H_
