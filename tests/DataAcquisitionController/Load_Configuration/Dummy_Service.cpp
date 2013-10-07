// $Id: Dummy_Service.cpp 1991 2011-10-10 02:05:19Z hillj $

#include "Dummy_Service.h"

namespace OASIS
{

//
// Archive_Data_Handler
//
Dummy_Data_Handler::Dummy_Data_Handler (void)
{

}

//
// ~Archive_Data_Handler
//
Dummy_Data_Handler::~Dummy_Data_Handler (void)
{

}

//
// init
//
int Dummy_Data_Handler::init (int argc, ACE_TCHAR *argv [])
{
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - initializing Dummy_Data_Handler service\n")));

  return 0;
}

//
// fini
//
int Dummy_Data_Handler::fini (void)
{
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - finalizing Dummy_Data_Handler service\n")));

  return 0;
}

///////////////////////////////////////////////////////////////////////////////
// class Dummy_Data_Channel

//
// Dummy_Data_Channel
//
Dummy_Data_Channel::Dummy_Data_Channel (void)
{

}

//
// ~Dummy_Data_Channel
//
Dummy_Data_Channel::~Dummy_Data_Channel (void)
{

}

//
// init
//
int Dummy_Data_Channel::init (int argc, ACE_TCHAR *argv [])
{
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - initializing Dummy_Data_Channel service\n")));

  return 0;
}

//
// fini
//
int Dummy_Data_Channel::fini (void)
{
  ACE_ERROR ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - finalizing Dummy_Data_Channel service\n")));

  return 0;
}

}

OASIS_DAC_DATA_HANDLER_IMPL (_make_OASIS_Dummy_Data_Handler, OASIS::Dummy_Data_Handler);

ACE_FACTORY_NAMESPACE_DEFINE (OASIS_LOAD_CONFIGURATION_TEST,
                              OASIS_Dummy_Data_Channel,
                              OASIS::Dummy_Data_Channel)
