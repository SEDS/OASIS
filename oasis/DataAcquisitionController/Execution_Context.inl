// -*- C++ -*-
// $Id: Execution_Context.inl 2070 2011-12-01 15:29:17Z hillj $

namespace OASIS
{
namespace DAC
{

//
// Execution_Context
//
OASIS_INLINE
Execution_Context::Execution_Context (void)
: name_ ("DAC")
{

}

//
// get_database
//
OASIS_INLINE
const Database & Execution_Context::get_database (void) const
{
  return this->database_;
}

//
// get_database
//
OASIS_INLINE
Database & Execution_Context::get_database (void)
{
  return this->database_;
}

//
// name
//
OASIS_INLINE
void Execution_Context::name (const ACE_CString & n)
{
  this->name_ = n;
}

//
// name
//
OASIS_INLINE
const ACE_CString & Execution_Context::name (void)
{
  return this->name_;
}

//
// get_data_handlers
//
OASIS_INLINE
const Execution_Context::Data_Handler_Manager &
Execution_Context::get_data_handlers (void) const
{
  return this->handlers_;
}

}
}
