// $Id: OASIS_PDL_Symbol_Table.cpp 1896 2011-09-07 14:56:19Z hillj $

#include "OASIS_PDL_Symbol_Table.h"
#include "fe/PDL_Simple_Type.h"

//
// OASIS_PDL_Symbol_Table
//
OASIS_PDL_Symbol_Table::OASIS_PDL_Symbol_Table (void)
{
  OASIS_PDL_Simple_Type * st = 0;

  this->new_symbol <OASIS_PDL_Simple_Type> ("boolean", st);
  st->kind (OASIS_PDL_Simple_Type::tk_boolean);

  this->new_symbol <OASIS_PDL_Simple_Type> ("string", st);
  st->kind (OASIS_PDL_Simple_Type::tk_string);

  this->new_symbol <OASIS_PDL_Simple_Type> ("int8", st);
  st->kind (OASIS_PDL_Simple_Type::tk_int8);

  this->new_symbol <OASIS_PDL_Simple_Type> ("int16", st);
  st->kind (OASIS_PDL_Simple_Type::tk_int16);

  this->new_symbol <OASIS_PDL_Simple_Type> ("int32", st);
  st->kind (OASIS_PDL_Simple_Type::tk_int32);

  this->new_symbol <OASIS_PDL_Simple_Type> ("int64", st);
  st->kind (OASIS_PDL_Simple_Type::tk_int64);

  this->new_symbol <OASIS_PDL_Simple_Type> ("uint8", st);
  st->kind (OASIS_PDL_Simple_Type::tk_uint8);

  this->new_symbol <OASIS_PDL_Simple_Type> ("uint16", st);
  st->kind (OASIS_PDL_Simple_Type::tk_uint16);

  this->new_symbol <OASIS_PDL_Simple_Type> ("uint32", st);
  st->kind (OASIS_PDL_Simple_Type::tk_uint32);

  this->new_symbol <OASIS_PDL_Simple_Type> ("uint64", st);
  st->kind (OASIS_PDL_Simple_Type::tk_uint64);

  this->new_symbol <OASIS_PDL_Simple_Type> ("real32", st);
  st->kind (OASIS_PDL_Simple_Type::tk_real32);

  this->new_symbol <OASIS_PDL_Simple_Type> ("real64", st);
  st->kind (OASIS_PDL_Simple_Type::tk_real64);
}

//
// OASIS_PDL_Symbol_Table
//
OASIS_PDL_Symbol_Table::~OASIS_PDL_Symbol_Table (void)
{
  SYMBOL_TABLE::ITERATOR iter (this->symbols_);

  for (; !iter.done (); ++ iter)
    delete iter->item ();
}

//
// find
//
int OASIS_PDL_Symbol_Table::
find (const std::string & name, OASIS_PDL_Type * & symbol)
{
  if (0 == name.find ("::"))
  {
    return this->symbols_.find (name.c_str () + 2, symbol);
  }
  else
  {
    std::vector <std::string>::reverse_iterator
      iter = this->scopes_.rbegin (),
      iter_end = this->scopes_.rend ();

    for (; iter != iter_end; ++ iter)
    {
      // Construct the fully qualified name.
      std::string fq_name = *iter + "::" + name;

      if (0 == this->symbols_.find (fq_name, symbol))
        return 0;
    }

    return this->symbols_.find (name, symbol);
  }
}

//
// find_builtin
//
int OASIS_PDL_Symbol_Table::
find_builtin (const std::string & name, OASIS_PDL_Type * & symbol)
{
  return this->symbols_.find (name, symbol);
}

//
// push_scope
//
int OASIS_PDL_Symbol_Table::push_scope (const std::string & name)
{
  // Get the fully qualified type name.
  std::string current_type;
  this->get_fq_type (name.c_str (), current_type);

  this->scopes_.push_back (current_type);
  return 0;
}

//
// pop_scope
//
int OASIS_PDL_Symbol_Table::pop_scope (void)
{
  this->scopes_.pop_back ();
  return 0;
}

//
// get_fq_type
//
void OASIS_PDL_Symbol_Table::
get_fq_type (const std::string & name, std::string & fq_type)
{
  if (!this->scopes_.empty ())
  {
    // Get the current scope value. This is needed to ensure we
    // have the fully qualified type name correct.
    fq_type = this->scopes_.back ();
    fq_type += "::";
  }

  fq_type += name;
}
