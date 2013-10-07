// $Id: Xml_Error_Handler.cpp 1926 2011-09-26 20:37:40Z hillj $

#include "Xml_Error_Handler.h"
#include "Xml_String.h"

#include "xercesc/dom/DOMLocator.hpp"
#include "xercesc/sax/SAXParseException.hpp"

#include <memory>
#include <iostream>

using xercesc::SAXParseException;

//
// Xml_Error_Handler
//
Xml_Error_Handler::Xml_Error_Handler (void)
: errors_ (false)
{

}

//
// ~Xml_Error_Handler
//
Xml_Error_Handler::~Xml_Error_Handler()
{

}

//
// warning
//
void Xml_Error_Handler::warning (const SAXParseException& toCatch)
{
  char * file = xercesc::XMLString::transcode (toCatch.getSystemId ());
  char * msg = xercesc::XMLString::transcode (toCatch.getMessage ());

  std::cerr << "Warning: " << file << ':' << toCatch.getLineNumber ()
            << ':' << toCatch.getColumnNumber () << " - "
            << msg << std::endl;

  xercesc::XMLString::release (&file);
  xercesc::XMLString::release (&msg);
}

//
// error
//
void Xml_Error_Handler::error (const SAXParseException& toCatch)
{
  char * file = xercesc::XMLString::transcode (toCatch.getSystemId ());
  char * msg = xercesc::XMLString::transcode (toCatch.getMessage ());

  std::cerr << "Error: " << file << ':' << toCatch.getLineNumber ()
            << ':' << toCatch.getColumnNumber () << " - "
            << msg << std::endl;

  this->errors_ = true;

  xercesc::XMLString::release (&file);
  xercesc::XMLString::release (&msg);
}

//
// fatalError
//
void Xml_Error_Handler::fatalError (const SAXParseException& toCatch)
{
  char * file = xercesc::XMLString::transcode (toCatch.getSystemId ());
  char * msg = xercesc::XMLString::transcode (toCatch.getMessage ());

  std::cerr << "Fatal Error: " << file << ':' << toCatch.getLineNumber ()
            << ':' << toCatch.getColumnNumber () << " - "
            << msg << std::endl;

  this->errors_ = true;

  xercesc::XMLString::release (&file);
  xercesc::XMLString::release (&msg);
}

//
// resetErrors
//
void Xml_Error_Handler::resetErrors (void)
{
  this->errors_ = false;
}

//
// getErrors
//
bool Xml_Error_Handler::getErrors (void) const
{
  return this->errors_;
}
