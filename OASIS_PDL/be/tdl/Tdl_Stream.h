// -*- C++ -*-

//=============================================================================
/**
 * @file      Tdl_Stream.h
 *
 *  $Id: Tdl_Stream.h 1819 2011-08-02 18:46:55Z hillj $
 *
 *  @author   Jeff Parsons
 *
 *  This class was originally used in the CoSMIC IDL generator. Because
 *  PDL is very close to TDL, we are going to reuse the IDLStream class
 *  from CoSMIC's IDL generator here in this library.
 */
//=============================================================================

#ifndef _OASIS_PDL_TDL_STREAM_H_
#define _OASIS_PDL_TDL_STREAM_H_

#include <ostream>

// A dummy structure to inform TAO_OutStream's << operator to  put a newline
// and use the current indentation for the succeeding line
struct NL
{
  NL (void);
};

struct INDENT
{
  //   Increase the indentation level, if the "do_now" parameter is
  //   not zero then the <indent> method is called on the stream.
  //
  INDENT (int do_now = 0);

  const int do_now_;
};

struct UNINDENT
{
  //   Decrease the indentation level, if the "do_now" parameter is
  //   not zero then the <indent> method is called on the stream.
  //
  UNINDENT (int do_now = 0);

  const int do_now_;
};

extern const NL nl;
extern const INDENT idt;
extern const INDENT idt_nl;
extern const UNINDENT uidt;
extern const UNINDENT uidt_nl;

class Tdl_Stream
{
public:
  Tdl_Stream (std::ostream& strm);
  // constructor.

  virtual ~Tdl_Stream (void);
  // destructor.

  void incr_indent (unsigned short flag = 1);
  // increment the indentation level and by default actually indent the output
  // accordingly

  void decr_indent (unsigned short flag = 1);
  // decrease the indentation level and by default actually indent the output
  // accordingly

  void reset (void);
  // reset indentation level to 0

  void indent (void);
  // indent starting next line

  void nl (void);
  // put a newline and indent on the next line

  void gen_ifdef_macro (const std::string &);
  void gen_ifdef_macro (const char *);
  // generate a #if !defined, #defined macro

  void gen_endif (const std::string &);
  void gen_endif (const char *);
  // generate an endif statement

  Tdl_Stream &operator<< (const std::string &);
  Tdl_Stream &operator<< (const char *);
  Tdl_Stream &operator<< (const long &);
  Tdl_Stream &operator<< (const int &);
  Tdl_Stream &operator<< (const unsigned long &);
  Tdl_Stream &operator<< (const double &);
  Tdl_Stream &operator<< (const char &);

  // = MANIPULATORS

  Tdl_Stream &operator<< (const NL &);
  Tdl_Stream &operator<< (const INDENT &);
  Tdl_Stream &operator<< (const UNINDENT &);

private:
  std::ostream& strm_;
  int indent_level_;

private:
  void upcase (const char *);
};

#endif // IDLSTREAM_H