// -*- C++ -*-

//=============================================================================
/**
 * @file        Exceptions.h
 *
 * $Id: Exceptions.h 2235 2013-02-06 20:18:09Z dfeiock $
 *
 * @author      Dennis C. Feiock <dfeiock@iupui.edu>
 */
//=============================================================================

#ifndef _OASIS_MIDDLEWARE_EXCEPTIONS_H_
#define _OASIS_MIDDLEWARE_EXCEPTIONS_H_

#include <stdexcept>
#include "oasis/config.h"

#include "Middleware_export.h"

namespace OASIS
{

/**
 * @class Connect_Error
 *
 * Exception thrown when a connection fails.
 */
class OASIS_MIDDLEWARE_Export Connect_Error :
  public std::exception
{
public:
  /// Default constructor.
  Connect_Error (void);

  /**
   * Initialization constructor. This constructor allows the caller
   * to provide more detailed information with the exception.
   *
   * @param[in]       reason        Reason for connect failure
   */
  Connect_Error (const char * reason);

  /// Destructor.
  virtual ~Connect_Error (void) throw ();

#if !defined (_WIN32)
  /// Error text accessor
  virtual const char * what (void) const throw ();

private:
  /// Error text
  char * message_;
#endif

};

/**
 * @class Transient_Error
 *
 * Exception thrown when using an established connection fails.
 */
class OASIS_MIDDLEWARE_Export Transient_Error :
  public std::exception
{
public:
  /// Default constructor.
  Transient_Error (void);

  /**
   * Initialization constructor. This constructor allows the caller
   * to provide more detailed information with the exception.
   *
   * @param[in]       reason        Reason for connect failure
   */
  Transient_Error (const char * reason);

  /// Destructor.
  virtual ~Transient_Error (void) throw ();

#if !defined (_WIN32)
  /// Error text accessor
  virtual const char * what (void) const throw ();

private:
  /// Error text
  char * message_;
#endif

};

}

#if defined (__OASIS_INLINE__)
#include "Exceptions.inl"
#endif


#endif  // !defined _OASIS_MIDDLEWARE_EXCEPTIONS_H_
