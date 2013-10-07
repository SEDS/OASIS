// -*- C++ -*-

//=============================================================================
/**
 *  @file       PDL_Probe.h
 *
 *  $Id: PDL_Probe.h 1778 2011-03-02 23:52:49Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_PROBE_H_
#define _OASIS_PDL_PROBE_H_

#include "PDL_Complex_Type.h"
#include "ace/UUID.h"

/**
 * @class OASIS_PDL_Probe_Attr
 *
 * The attributes for a software probe. This is the information
 * that appears before a software probe's definition.
 */
class OASIS_PDL_FE_Export OASIS_PDL_Probe_Attr
{
public:
  /// Default constructor.
  OASIS_PDL_Probe_Attr (void);

  /// Unique id for the software probe.
  ACE_Utils::UUID uuid_;

  /// The major version number.
  int version_major_;

  /// The minor version number.
  int version_minor_;

  /// Abstract state of the software probe.
  bool is_abstract_;
};

/**
 * @class OASIS_PDL_Probe
 *
 * Base class for all declarations in the language.
 */
class OASIS_PDL_FE_Export OASIS_PDL_Probe :
  public OASIS_PDL_Complex_Type
{
public:
  /// Default constructor.
  OASIS_PDL_Probe (void);

  /// Destructor.
  virtual ~OASIS_PDL_Probe (void);

  /// Accept the visitor.
  virtual void accept (OASIS_PDL_Visitor & v) const;

  /// Get the probe's attributes.
  const OASIS_PDL_Probe_Attr * attr (void) const;

  /// Set the probe's attributes.
  void attr (OASIS_PDL_Probe_Attr * attr);

  /// Test if the probe has a base probe.
  bool has_base_probe (void) const;

  /// Get the base probe.
  const OASIS_PDL_Probe * base_probe (void) const;

  /// Set the base probe.
  void base_probe (OASIS_PDL_Probe * p);

private:
  /// The software probe's attributes.
  std::auto_ptr <OASIS_PDL_Probe_Attr> attr_;

  /// Pointer to the base probe.
  OASIS_PDL_Probe * base_probe_;
};

#if defined (__OASIS_INLINE__)
#include "PDL_Probe.inl"
#endif

#endif  // !defined _OASIS_PDL_DECLARATION_H_
