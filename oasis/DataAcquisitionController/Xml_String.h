// -*- C++ -*-

//=============================================================================
/**
 *  @file     Xml_String.h
 *
 *  $Id: Xml_String.h 1926 2011-09-26 20:37:40Z hillj $
 *
 *  @author   James H. Hill
 */
//=============================================================================

#ifndef _OASIS_XML_STRING_H_
#define _OASIS_XML_STRING_H_

#include "xercesc/util/XMLString.hpp"
#include "DAC_Core_export.h"

/**
 * @class Xml_String
 *
 * Wrapper class for working with XML strings in Xerces-C
 */
class OASIS_DAC_CORE_Export Xml_String
{
public:
  /// Default constructor.
  Xml_String (void);

  /**
   * Initializing constructor.
   *
   * @param[in]       str       C-string
   */
  Xml_String (const char * str);

  /**
   * Initializing constructor.
   *
   * @param[in]       str       Xerces-C string
   */
  Xml_String (XMLCh * wstr);

  /**
   * Initializing constructor.
   *
   * @param[in]       str       Xerces-C string
   */
  Xml_String (const XMLCh* wstr);

  /**
   * Copy constructor.
   *
   * @param[in]       copy      Source XML string.
   */
  Xml_String (const Xml_String & copy);

  /// Assignment operator.
  Xml_String& operator = (const Xml_String& rhs);

  /// Assignment operator.
  Xml_String& operator = (const char * rhs);

  /// Destructor.
  ~Xml_String (void);

  /// Get a iterator to the beginning of the string.
  const XMLCh* begin (void) const;

  /// Get a iterator to the beginning of the string.
  const XMLCh* end (void) const;

  /**
   * Append a string.
   *
   * @param[in]       tail      String to append
   */
  bool append (const XMLCh* tail);

  /**
   * Erase a portion of the string.
   *
   * @param[in]       head      Starting position
   * @param[in]       tail      Ending position
   */
  bool erase (const XMLCh* head, const XMLCh* tail);

  /// Get the size of the string.
  int size (void) const;

  /// Get a character at the specified index.
  XMLCh operator [] (size_t i);

  /// Get a character at the specified index.
  const XMLCh operator [] (size_t i) const;

  /// Type casting operator.
  operator const XMLCh * (void) const;

  /// Release the string buffer. The caller is responsible
  /// for managing the returned buffer.
  XMLCh * release (void);

  /// Get the C string version of the XercesString.
  const char * c_str (void);

private:
  /// Internal representation
  XMLCh* wstr_;

  /// The C string version of the XercesString.
  char * cstr_;
};

OASIS_DAC_CORE_Export bool operator == (const Xml_String & lhs, const Xml_String & rhs);
OASIS_DAC_CORE_Export bool operator == (const XMLCh * lhs, const Xml_String & rhs);
OASIS_DAC_CORE_Export bool operator == (const Xml_String & lhs, const XMLCh * rhs);

OASIS_DAC_CORE_Export bool operator != (const Xml_String & lhs, const Xml_String & rhs);
OASIS_DAC_CORE_Export bool operator != (const XMLCh * lhs, const Xml_String & rhs);
OASIS_DAC_CORE_Export bool operator != (const Xml_String & lhs, const XMLCh * rhs);

#endif  // !defined _OASIS_XML_STRING_H_
