// -*- C++ -*-

//=============================================================================
/**
 *  @file       PDL_Complex_Type.h
 *
 *  $Id: PDL_Simple_Type.h 1768 2011-03-01 01:04:39Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_SIMPLE_TYPE_H_
#define _OASIS_PDL_SIMPLE_TYPE_H_

#include "PDL_Type.h"

/**
 * @class OASIS_PDL_Complex_Type
 *
 * Base class for all declarations in the language.
 */
class OASIS_PDL_FE_Export OASIS_PDL_Simple_Type :
  public OASIS_PDL_Type
{
public:
  /// Emumeration of the different types.
  enum tk_kind
  {
    tk_boolean,
    tk_string,
    tk_int8,
    tk_int16,
    tk_int32,
    tk_int64,
    tk_uint8,
    tk_uint16,
    tk_uint32,
    tk_uint64,
    tk_real32,
    tk_real64
  };

  /// Default constructor.
  OASIS_PDL_Simple_Type (void);

  /// Destructor.
  virtual ~OASIS_PDL_Simple_Type (void);

  void kind (tk_kind kind);

  tk_kind kind (void) const;

  void accept (OASIS_PDL_Visitor & v) const;

  virtual std::string fq_name (const std::string & separator) const;

private:
  /// Type type kind for this type.
  tk_kind kind_;
};

#if defined (__OASIS_INLINE__)
#include "PDL_Simple_Type.inl"
#endif

#endif  // !defined _OASIS_PDL_DECLARATION_H_
