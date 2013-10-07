// $Id: Tdl_Stream.cpp 1819 2011-08-02 18:46:55Z hillj $

#include "Tdl_Stream.h"
#include "ctype.h"

NL::NL (void)
{
}

INDENT::INDENT (int do_now)
  :  do_now_ (do_now)
{
}

UNINDENT::UNINDENT (int do_now)
  :  do_now_ (do_now)
{
}

const NL nl;
const INDENT idt;
const INDENT idt_nl (1);
const UNINDENT uidt;
const UNINDENT uidt_nl (1);

Tdl_Stream::Tdl_Stream (std::ostream& strm)
  : strm_ (strm),
    indent_level_ (0)
{
}

Tdl_Stream::~Tdl_Stream (void)
{
}

void
Tdl_Stream::incr_indent (unsigned short flag)
{
  ++indent_level_;

  if (flag != 0)
    {
      this->indent ();
    }
}

// Indentation
void
Tdl_Stream::decr_indent (unsigned short flag)
{
  if (this->indent_level_ > 0)
    {
      --this->indent_level_;
    }

  if (flag != 0)
    {
      this->indent ();
    }
}

void
Tdl_Stream::reset (void)
{
  this->indent_level_ = 0;
}

// Indented print.
void
Tdl_Stream::indent (void)
{
  // Based on the current indentation level, leave appropriate number of blank
  // spaces in the output.
  if (this->indent_level_ > 0)
    {
      for (int i = 0; i < this->indent_level_; ++i)
        {
          this->strm_ << "  ";
        }
    }
}

void
Tdl_Stream::nl (void)
{
  this->strm_ << std::endl;
  this->indent ();
}

// Macro generation.
void
Tdl_Stream::gen_ifdef_macro (const std::string &name)
{
  // All generated IDL files will be in the same directory,
  // so get rid of any path elements in #ifdef guards.
  std::string::size_type pos = name.rfind ('/');
  this->gen_ifdef_macro (
    name.substr (std::string::npos == pos ? 0 : pos + 1).c_str ());
}

void
Tdl_Stream::gen_ifdef_macro (const char *name)
{
  this->strm_ << "\n#ifndef ";
  this->upcase (name);
  this->strm_ << "_IDL\n"
              << "#define ";
  this->upcase (name);
  this->strm_ << "_IDL";
  this->strm_ << std::endl;
  this->indent ();
}

void
Tdl_Stream::gen_endif (const std::string &name)
{
  this->gen_endif (name.c_str ());
}

void
Tdl_Stream::gen_endif (const char *name)
{
  this->strm_ << "\n\n#endif // ";
  this->upcase (name);
  this->strm_ << "_IDL\n\n";
}

Tdl_Stream &
Tdl_Stream::operator<< (const std::string &s)
{
  this->strm_ << s.c_str ();
  return *this;
}

Tdl_Stream &
Tdl_Stream::operator<< (const char *str)
{
  this->strm_ << str;
  return *this;
}

Tdl_Stream &
Tdl_Stream::operator<< (const long &l)
{
  this->strm_ << l;
  return *this;
}

Tdl_Stream &
Tdl_Stream::operator<< (const int & val)
{
  this->strm_ << val;
  return *this;
}

Tdl_Stream &
Tdl_Stream::operator<< (const unsigned long &ul)
{
  this->strm_ << ul;
  return *this;
}

Tdl_Stream &
Tdl_Stream::operator<< (const double &d)
{
  this->strm_ << d;
  return *this;
}

Tdl_Stream &
Tdl_Stream::operator<< (const char &c)
{
  this->strm_ << c;
  return *this;
}

Tdl_Stream &
Tdl_Stream::operator<< (const NL&)
{
  (void) this->nl ();
  return *this;
}

Tdl_Stream &
Tdl_Stream::operator<< (const INDENT& i)
{
  this->incr_indent (0);

  if (i.do_now_)
    {
      (void) this->nl ();
    }

  return *this;
}

Tdl_Stream &
Tdl_Stream::operator<< (const UNINDENT& i)
{
  this->decr_indent (0);

  if (i.do_now_)
    {
      this->nl ();
    }

  return *this;
}

void
Tdl_Stream::upcase (const char *str)
{
  int i = 0;
  char c;

  while ((c = str[i++]) != '\0')
    {
      this->strm_ << static_cast<char> (toupper (c));
    }
}

