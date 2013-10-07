// -*- C++ -*-
// $Id: Servant_Manager_T.inl 1934 2011-09-28 14:56:30Z hillj $

namespace OASIS
{

///////////////////////////////////////////////////////////////////////////////
// Servant_Manager_T

//
// Servant_Manager_T
//
template <typename T>
OASIS_INLINE
Servant_Manager_T <T>::Servant_Manager_T (T * servant, bool managed)
: servant_ (servant),
  is_managed_ (managed)
{
  OASIS_TAO_TRACE ("Servant_Manager_T <T>::Servant_Manager_T (T *, bool)");
}

//
// get
//
template <typename T>
OASIS_INLINE
T * Servant_Manager_T <T>::get (void)
{
  OASIS_TAO_TRACE ("T * Servant_Manager_T <T>::get (void)");

  return this->servant_;
}

//
// operator ->
//
template <typename T>
OASIS_INLINE
T * Servant_Manager_T <T>::operator -> (void)
{
  OASIS_TAO_TRACE ("T * Servant_Manager_T <T>::operator -> (void)");

  return this->servant_;
}

//
// operator ->
//
template <typename T>
OASIS_INLINE
bool Servant_Manager_T <T>::is_managed (void) const
{
  OASIS_TAO_TRACE ("bool Servant_Manager_T <T>::is_managed (void) const");

  return this->is_managed_;
}

///////////////////////////////////////////////////////////////////////////////
// Servant_Manager_Ex_T

//
// Servant_Manager_Ex_T
//
template <typename T, typename TRAITS>
OASIS_INLINE
Servant_Manager_Ex_T <T, TRAITS>::
Servant_Manager_Ex_T (T * servant, bool managed)
: Servant_Manager_T <T> (servant, managed)
{
  OASIS_TAO_TRACE ("Servant_Manager_Ex_T (T *, bool)");
}

//
// ~Servant_Manager_Ex_T
//
template <typename T, typename TRAITS>
OASIS_INLINE
Servant_Manager_Ex_T <T, TRAITS>::~Servant_Manager_Ex_T (void)
{
  OASIS_TAO_TRACE ("Servant_Manager_Ex_T <T, TRAITS>::~Servant_Manager_Ex_T (void)");

  this->deactivate ();
}

//
// set_trait_value
//
template <typename T, typename TRAITS>
template <typename TRAIT>
OASIS_INLINE
int Servant_Manager_Ex_T <T, TRAITS>::
set_trait_value (TRAIT trait, const ACE_CString & value)
{
  OASIS_TAO_TRACE ("int Servant_Manager_Ex_T <T, TRAITS>::set_trait_value (TRAIT, const ACE_CString &)");

  return this->traits_.set_value (trait.ID, value);
}

//
// get_trait_value
//
template <typename T, typename TRAITS>
template <typename TRAIT>
OASIS_INLINE
int Servant_Manager_Ex_T <T, TRAITS>::
get_trait_value (TRAIT trait, ACE_CString & value)
{
  OASIS_TAO_TRACE ("int Servant_Manager_Ex_T <T, TRAITS>::get_trait_value (TRAIT, ACE_CString &)");

  return this->traits_.get_value (trait.ID, value);
}

}
