// $Id: Simple_Data_Subscriber.cpp 1805 2011-06-04 21:46:30Z hillj $

#include "Simple_Data_Subscriber.h"

//
// Simple_Data_Subscriber
//
Simple_Data_Subscriber::Simple_Data_Subscriber (void)
{

}

//
// Simple_Data_Subscriber
//
Simple_Data_Subscriber::~Simple_Data_Subscriber (void)
{

}

//
// name
//
char * Simple_Data_Subscriber::name (void)
{
  CORBA::String_var str = CORBA::string_dup ("Simple_Data_Subscriber");
  return str._retn ();
}

//
// handle_data
//
void Simple_Data_Subscriber::handle_data (const OASIS::SubscriberDataPacket & packet)
{
  ACE_DEBUG ((LM_DEBUG, "we received data!!!\n"));
}
