// -*- C++ -*-
// $Id: Exceptions.inl 2102 2012-01-11 19:04:38Z dfeiock $

namespace OASIS
{

//
// Connect_Error
//
OASIS_INLINE
Connect_Error::Connect_Error (void)
{

}

//
// Connect_Error
//
OASIS_INLINE
Connect_Error::Connect_Error (const char * reason)
#if defined (_WIN32)
: std::exception (reason)
#endif
{

#if !defined (_WIN32)
  this->message_ = new char [strlen (reason) + 1];
  strcpy (this->message_, reason);
#endif

}

//
// Connect_Error
//
OASIS_INLINE
Connect_Error::~Connect_Error (void) throw ()
{

#if !defined (_WIN32)
  delete[] this->message_;
#endif

}

#if !defined (_WIN32)
//
// what
//
OASIS_INLINE
const char * Connect_Error::what (void) const throw ()
{
  return this->message_;
}
#endif

//
// Transient_Error
//
OASIS_INLINE
Transient_Error::Transient_Error (void)
{

}

//
// Transient__Error
//
OASIS_INLINE
Transient_Error::Transient_Error (const char * reason)
#if defined (_WIN32)
: std::exception (reason)
#endif
{

#if !defined (_WIN32)
  this->message_ = new char [strlen (reason) + 1];
  strcpy (this->message_, reason);
#endif

}

//
// Transient_Error
//
OASIS_INLINE
Transient_Error::~Transient_Error (void) throw ()
{

#if !defined (_WIN32)
  delete[] this->message_;
#endif

}

#if !defined (_WIN32)
//
// what
//
OASIS_INLINE
const char * Transient_Error::what (void) const throw ()
{
  return this->message_;
}
#endif

}
