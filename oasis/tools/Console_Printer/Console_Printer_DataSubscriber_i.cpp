// $Id: Console_Printer_DataSubscriber_i.cpp 2071 2011-12-01 15:48:16Z hillj $

#include "Console_Printer_DataSubscriber_i.h"
#include "oasis/middleware/tao/UUID.h"
#include "ace/streams.h"

namespace OASIS
{

//
// Console_Printer_DataSubscriber_i
//
Console_Printer_DataSubscriber_i::Console_Printer_DataSubscriber_i (void)
{

}

//
// Console_Printer_DataSubscriber_i
//
Console_Printer_DataSubscriber_i::~Console_Printer_DataSubscriber_i (void)
{

}

//
// name
//
char * Console_Printer_DataSubscriber_i::name (void)
{
  ::CORBA::String_var str = ::CORBA::string_dup ("OASIS::ConoleDataSubscriber");
  return str._retn ();
}

//
// handle_data
//
void Console_Printer_DataSubscriber_i::
handle_data (const OASIS::SubscriberDataPacket & packet)
{
  ACE_Utils::UUID einode;
  packet.einode >>= einode;

  std::cout
    << "received " << packet.data.length ()
    << " bytes of data from " << *einode.to_string () << std::endl;
}

}
