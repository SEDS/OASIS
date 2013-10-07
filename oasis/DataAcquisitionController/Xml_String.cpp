// $Id: Xml_String.cpp 1926 2011-09-26 20:37:40Z hillj $

#include "Xml_String.h"
#include <ostream>

using xercesc::XMLString;

//
// Xml_String
//
Xml_String::Xml_String (void)
  : wstr_ (0),
    cstr_ (0)
{

}

//
// Xml_String
//
Xml_String::Xml_String (const char* str)
  : wstr_ (0),
    cstr_ (0)
{
  this->wstr_ = XMLString::transcode (str);
}

//
// Xml_String
//
Xml_String::Xml_String (XMLCh *wstr)
  : wstr_ (0),
    cstr_ (0)
{
  this->wstr_ = XMLString::replicate (wstr);
}

//
// Xml_String
//
Xml_String::Xml_String (const XMLCh* wstr)
  : wstr_ (0),
    cstr_ (0)
{
  this->wstr_ = XMLString::replicate (wstr);
}

//
// Xml_String
//
Xml_String::Xml_String (const Xml_String &right)
  : wstr_ (0),
    cstr_ (0)
{
  this->wstr_ = XMLString::replicate (right.wstr_);
}

//
// ~Xml_String
//
Xml_String::~Xml_String (void)
{
  if (0 != this->wstr_)
    XMLString::release (&this->wstr_);

  if (0 != this->cstr_)
    XMLString::release (&this->cstr_);
}

//
// operator =
//
Xml_String& Xml_String::operator = (const Xml_String& rhs)
{
  if (&rhs == this)
    return *this;

  Xml_String temp (rhs);
  std::swap (this->wstr_, temp.wstr_);
  std::swap (this->cstr_, temp.cstr_);

  return *this;
}

//
// operator =
//
Xml_String& Xml_String::operator = (const char * rhs)
{
  Xml_String temp (rhs);
  std::swap (this->wstr_, temp.wstr_);
  std::swap (this->cstr_, temp.cstr_);

  return *this;
}

//
// begin
//
const XMLCh* Xml_String::begin (void) const
{
  return this->wstr_;
}

//
// end
//
const XMLCh* Xml_String::end (void) const
{
  return this->wstr_ + this->size ();
}

//
// append
//
bool Xml_String::append (const XMLCh *tail)
{
  using namespace xercesc;

  int iTailLen = XMLString::stringLen (tail);
  int iWorkLen = XMLString::stringLen (this->wstr_);
  size_t length = iWorkLen + iTailLen + 1;

  XMLCh * result =
    (XMLCh *) XMLPlatformUtils::fgMemoryManager->allocate (length * sizeof (XMLCh));

  bool bOK = result != 0;

  if (bOK)
  {
    XMLCh *target = result;

    XMLString::moveChars (target, this->wstr_, iWorkLen);
    target += iWorkLen;

    XMLString::moveChars (target, tail, iTailLen);
    target += iTailLen;

    *target++ = 0;

    XMLString::release (&this->wstr_);
    this->wstr_ = result;

    if (0 != this->cstr_)
    {
      XMLString::release (&this->cstr_);
      this->cstr_ = 0;
    }
  }

  return bOK;
}

//
// erase
//
bool Xml_String::erase (const XMLCh *head, const XMLCh *tail)
{
  bool bOK = head <= tail && head >= begin() && tail <= end();
  if (bOK)
    {
      XMLCh *result = new XMLCh[ size() - (tail - head) + 1 ];
      XMLCh *target = result;
      bOK = target != NULL;

      if (bOK)
        {
          const XMLCh *cursor = begin();

          while (cursor != head) *target++ = *cursor++;
          cursor = tail;
          while ( cursor != end() ) *target++ = *cursor++;
          *target ++ = 0;

          XMLString::release (&this->wstr_);
          this->wstr_ = result;

          if (0 != this->cstr_)
          {
            XMLString::release (&this->cstr_);
            this->cstr_ = 0;
          }
        }
    }
  return bOK;
}

//
// size
//
int Xml_String::size (void) const
{
  return XMLString::stringLen (this->wstr_);
}

//
// operator []
//
XMLCh Xml_String::operator [] (size_t i)
{
  return this->wstr_[i];
}

//
// operator []
//
const XMLCh Xml_String::operator [] (size_t i) const
{
  return this->wstr_[i];
}

//
// release
//
XMLCh * Xml_String::release (void)
{
  XMLCh * temp = this->wstr_;
  this->wstr_ = 0;

  // Release the C string.
  if (0 != this->cstr_)
  {
    XMLString::release (&this->cstr_);
    this->cstr_ = 0;
  }

  return temp;
}

//
// c_str
//
const char * Xml_String::c_str (void)
{
  if (0 != this->cstr_)
    return this->cstr_;

  this->cstr_ = XMLString::transcode (this->wstr_);
  return this->cstr_;
}

//
// operator const XMLCh *
//
Xml_String::operator const XMLCh * (void) const
{
  return this->wstr_;
}

//
// operator ==
//
bool operator == (const Xml_String & lhs, const Xml_String & rhs)
{
  return 0 == XMLString::compareString (lhs, rhs);
}

//
// operator ==
//
bool operator == (const Xml_String & lhs, const XMLCh * rhs)
{
  return 0 == XMLString::compareString (lhs, rhs);
}

//
// operator ==
//
bool operator == (const XMLCh * lhs, const Xml_String & rhs)
{
  return 0 == XMLString::compareString (lhs, rhs);
}

//
// operator !=
//
bool operator != (const Xml_String & lhs, const Xml_String & rhs)
{
  return !(lhs == rhs);
}

//
// operator !=
//
bool operator != (const XMLCh * lhs, const Xml_String & rhs)
{
  return !(lhs == rhs);
}

//
// operator !=
//
bool operator != (const Xml_String & lhs, const XMLCh * rhs)
{
  return !(lhs == rhs);
}
