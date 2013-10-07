// -*- C++ -*-

//==============================================================
/**
 *  @file  Xml_Error_Handler.h
 *
 *  $Id: Xml_Error_Handler.h 1926 2011-09-26 20:37:40Z hillj $
 *
 *  @brief Error handler for Xerces
 *
 *  @author Bala Natarajan <bala@dre.vanderbilt.edu>
 */
//================================================================

#ifndef _OASIS_XML_ERROR_HANDLER_H_
#define _OASIS_XML_ERROR_HANDLER_H_

#include "DAC_Core_export.h"
#include "xercesc/sax/ErrorHandler.hpp"

using xercesc::SAXParseException;

/**
 * @class XML_Error_Hander
 *
 * Error handler for parsing an XML file in Xerces-C.
 */
class OASIS_DAC_CORE_Export Xml_Error_Handler :
  public xercesc::ErrorHandler
{
public:
  /// Default constructor.
  Xml_Error_Handler (void);

  /// Destructor.
  ~Xml_Error_Handler (void);

  void warning (const SAXParseException& toCatch);

  void error (const SAXParseException& toCatch);

  void fatalError (const SAXParseException& toCatch);

  /// Reset the errors flag.
  void resetErrors (void);

  /// Get the errors flag.
  bool getErrors (void) const;

private :
  /// Flag of there were errors.
  bool errors_;

  // prevent the following operations
  Xml_Error_Handler (const Xml_Error_Handler&);
  Xml_Error_Handler& operator= (const Xml_Error_Handler&);
};


#endif /* CIAO_XML_ERROR_HANDLER_H*/
