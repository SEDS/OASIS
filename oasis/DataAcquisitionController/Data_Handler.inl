// -*- C++ -*-
// $Id: Data_Handler.inl 2070 2011-12-01 15:29:17Z hillj $

namespace OASIS
{
namespace DAC
{

//
// Data_Handler
//
OASIS_INLINE
Data_Handler::Data_Handler (void)
{

}

//
// ~Data_Handler
//
OASIS_INLINE
Data_Handler::~Data_Handler (void)
{

}

//
// init
//
OASIS_INLINE
int Data_Handler::init (int argc, char * argv [])
{
  return 0;
}

//
// fini
//
OASIS_INLINE
int Data_Handler::fini (void)
{
  return 0;
}

//
// handle_activate
//
OASIS_INLINE
int Data_Handler::handle_activate (void)
{
  return 0;
}

//
// handle_deactivate
//
OASIS_INLINE
int Data_Handler::handle_deactivate (void)
{
  return 0;
}

//
// handle_data
//
OASIS_INLINE
int Data_Handler::handle_data (const Data_Packet & )
{
  return 0;
}

//
// handle_registration
//
OASIS_INLINE
int Data_Handler::handle_registration (const Registration_Packet & )
{
  return 0;
}

//
// handle_unregister_einode
//
OASIS_INLINE
int Data_Handler::handle_unregister_einode (const Unregistration_Packet & )
{
  return 0;
}

#if defined (OASIS_HAS_TAO_DAC_SERVANT)
::OASIS::RemoteService_ptr Data_Handler::get_remote_service (void)
{
  return ::OASIS::RemoteService::_nil ();
}

#endif

}
}
