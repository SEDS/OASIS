// $Id: OASIS_PDL_Symbol_Table_T.cpp 1896 2011-09-07 14:56:19Z hillj $

//
// new_symbol
//
template <typename T>
int OASIS_PDL_Symbol_Table::new_symbol (const std::string & name)
{
  T * symbol = 0;
  return this->new_symbol (name, symbol);
}

//
// new_symbol
//
template <typename T>
int OASIS_PDL_Symbol_Table::
new_symbol (const std::string & name, T * & symbol)
{
  // Get the fully qualified name for the symbol.
  std::string fq_type;
  this->get_fq_type (name, fq_type);

  // Make sure the symbol is not duplicated.
  if (0 == this->symbols_.find (fq_type))
    return 1;

  // Allocate the new symbol element.
  symbol = new T ();
  symbol->name (name.c_str ());

  return this->symbols_.bind (fq_type, symbol);
}
