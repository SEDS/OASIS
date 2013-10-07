// -*- C++ -*-
// $Id: Standard_DAC_App.inl 2238 2013-03-08 20:50:44Z tmpeiris $

namespace OASIS
{

//
// Standard_DAC_App
//
OASIS_INLINE
Standard_DAC_App::Standard_DAC_App (void)
: connstr_ ("DAC.db"),
  exit_ (lock_)
#if defined (OASIS_HAS_TAO_DAC_SERVANT)
  ,servant_ (&servant_impl_, false)
#endif
{
}

//
// ~Standard_DAC_App
//
OASIS_INLINE
Standard_DAC_App::~Standard_DAC_App (void)
{

}

}
