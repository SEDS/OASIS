// -*- C++ -*-

//=============================================================================
/**
 *  @file       OASIS_PDL_Symbol_Table.h
 *
 *  $Id: OASIS_PDL_Symbol_Table.h 1896 2011-09-07 14:56:19Z hillj $
 *
 *  @author     James H. Hill
 */
//=============================================================================

#ifndef _OASIS_PDL_SYMBOL_TABLE_H_
#define _OASIS_PDL_SYMBOL_TABLE_H_

#include "fe/PDL_Type.h"
#include "ace/Containers_T.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"
#include "ace/Singleton.h"

#include <string>
#include <vector>

/**
 * @class OASIS_PDL_Symbol_Table
 */
class OASIS_PDL_Symbol_Table
{
public:
  /// Default constructor.
  OASIS_PDL_Symbol_Table (void);

  /// Destructor.
  ~OASIS_PDL_Symbol_Table (void);

  template <typename T>
  int new_symbol (const std::string & name);

  template <typename T>
  int new_symbol (const std::string & name, T * & symbol);

  /**
   * Locate the symbol in the specified table.
   *
   * @param[in]       name          Name of the symbol
   * @param[out]      symbol        Pointer to the actual symbol
   */
  int find (const std::string & name, OASIS_PDL_Type * & symbol);
  int find_builtin (const std::string & name, OASIS_PDL_Type * & symbol);

  /**
   * Push a new scope onto the symbol table. This determine the
   * order of lookup for a symbol.
   *
   * @param[in]       name          Name of the scope
   */
  int push_scope (const std::string & name);

  /// Pop the current scope value.
  int pop_scope (void);

private:
  void get_fq_type (const std::string & name, std::string & fq_type);

  /// Type definition of the symbol table.
  typedef
    ACE_Hash_Map_Manager <std::string,
                          OASIS_PDL_Type *,
                          ACE_Null_Mutex> SYMBOL_TABLE;

  /// The actual symbol table.
  SYMBOL_TABLE symbols_;

  /// The stack of scopes.
  std::vector <std::string> scopes_;
};

#include "OASIS_PDL_Symbol_Table_T.cpp"

/// Type definition for the global symbol table.
typedef ACE_Singleton <OASIS_PDL_Symbol_Table,
                       ACE_Null_Mutex>
                       OASIS_PDL_GLOBAL_SYMBOL_TABLE;

#endif  // !defined _OASIS_PDL_SYMBOL_TABLE_H_
