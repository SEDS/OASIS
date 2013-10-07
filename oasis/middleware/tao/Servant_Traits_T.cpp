// $Id: Servant_Traits_T.cpp 1863 2011-08-19 18:39:59Z hillj $

#if !defined (__OASIS_INLINE__)
#include "Servant_Traits_T.inl"
#endif

namespace OASIS
{

///////////////////////////////////////////////////////////////////////////////
// Servant_Trait_T <T, NEXT>

//
// handle_activate
//
template <typename T, typename NEXT>
int Servant_Trait_T <T, NEXT>::
handle_activate (::CORBA::Object_ptr obj)
{
  int retval = 0;

  if (!this->trait_value_.empty ())
    retval += T::handle_activate (obj, this->trait_value_);

  return retval + this->next_.handle_activate (obj);
}

//
// handle_deactivate
//
template <typename T, typename NEXT>
int Servant_Trait_T <T, NEXT>::
handle_deactivate (::CORBA::Object_ptr obj)
{
  int retval = 0;

  if (!this->trait_value_.empty ())
    retval += T::handle_deactivate (obj, this->trait_value_);

  return retval + this->next_.handle_deactivate (obj);
}

//
// set_value
//
template <typename T, typename NEXT>
int Servant_Trait_T <T, NEXT>::
set_value (int id, const ACE_CString & value)
{
  if (id == T::ID)
  {
    this->trait_value_ = value;
    return 0;
  }
  else
    return this->next_.set_value (id, value);
}

//
// get_value
//
template <typename T, typename NEXT>
int Servant_Trait_T <T, NEXT>::
get_value (int id, ACE_CString & value)
{
  if (id == T::ID)
  {
    value = this->trait_value_;
    return 0;
  }
  else
    return this->next_.get_value (id, value);
}

///////////////////////////////////////////////////////////////////////////////
// Servant_Trait_T <T, NIL>

//
// handle_activate
//
template <typename T>
OASIS_INLINE
int Servant_Trait_T <T, NIL>::
handle_activate (::CORBA::Object_ptr obj)
{
  if (!this->trait_value_.empty ())
    return T::handle_activate (obj, this->trait_value_);
  else
    return 0;
}

//
// handle_deactivate
//
template <typename T>
OASIS_INLINE
int Servant_Trait_T <T, NIL>::
handle_deactivate (::CORBA::Object_ptr obj)
{
  if (!this->trait_value_.empty ())
    return T::handle_deactivate (obj, this->trait_value_);
  else
    return 0;
}

//
// set_value
//
template <typename T>
int Servant_Trait_T <T, NIL>::
set_value (int id, const ACE_CString & value)
{
  if (id == T::ID)
  {
    this->trait_value_ = value;
    return 0;
  }
  else
    return -1;
}

//
// get_value
//
template <typename T>
int Servant_Trait_T <T, NIL>::
get_value (int id, ACE_CString & value)
{
  if (id != T::ID)
  {
    value = this->trait_value_;
    return 0;
  }
  else
    return -1;
}

}
