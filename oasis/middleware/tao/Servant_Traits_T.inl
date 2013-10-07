// -*- C++ -*-
// $Id: Servant_Traits_T.inl 1863 2011-08-19 18:39:59Z hillj $

namespace OASIS
{

///////////////////////////////////////////////////////////////////////////////
// Servant_Trait_T <T, NEXT>

//
// Servant_Trait_T
//
template <typename T, typename NEXT>
OASIS_INLINE
Servant_Trait_T <T, NEXT>::Servant_Trait_T (void)
{

}

//
// ~Servant_Trait_T
//
template <typename T, typename NEXT>
OASIS_INLINE
Servant_Trait_T <T, NEXT>::~Servant_Trait_T (void)
{

}

//
// is_set
//
template <typename T, typename NEXT>
OASIS_INLINE
bool Servant_Trait_T <T, NEXT>::is_set (void) const
{
  return !this->trait_value_.empty ();
}

///////////////////////////////////////////////////////////////////////////////
// Servant_Trait_T <T, NIL>

//
// Servant_Trait_T
//
template <typename T>
OASIS_INLINE
Servant_Trait_T <T, NIL>::Servant_Trait_T (void)
{

}

//
// ~Servant_Trait_T
//
template <typename T>
OASIS_INLINE
Servant_Trait_T <T, NIL>::~Servant_Trait_T (void)
{

}

//
// is_set
//
template <typename T>
OASIS_INLINE
bool Servant_Trait_T <T, NIL>::is_set (void) const
{
  return !this->trait_value_.empty ();
}

}
