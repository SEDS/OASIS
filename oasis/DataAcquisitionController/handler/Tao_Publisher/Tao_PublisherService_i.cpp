// $Id: Tao_PublisherService_i.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "Tao_PublisherService_i.h"

#include "oasis/probes/Software_Probe_Header.h"
#include "oasis/DataAcquisitionController/Data_Packet.h"
#include "oasis/middleware/tao/UUID.h"

namespace OASIS
{

//
// Tao_PublisherService_i
//
Tao_PublisherService_i::Tao_PublisherService_i (void)
{

}

//
// ~Tao_PublisherService_i
//
Tao_PublisherService_i::~Tao_PublisherService_i (void)
{

}

//
// name
//
char * Tao_PublisherService_i::name (void)
{
  CORBA::String_var service_name = CORBA::string_dup ("TaoPublisherService");
  return service_name._retn ();
}

//
// register_subscriber
//
void Tao_PublisherService_i::
register_subscriber (const ::OASIS::UUID & probe, ::OASIS::DataSubscriber_ptr subscriber)
{
  // Turn the probe ID into something we can use.
  ACE_Utils::UUID uuid;
  if (!(probe >>= uuid))
    throw ::CORBA::INTERNAL ();

  CORBA::String_var name = subscriber->name ();

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - received request from %s to subscribe to %s\n"),
              name.in (),
              uuid.to_string ()->c_str ()));

  Subscriber_Set * subscribers = 0;

  if (0 != this->subscribers_.find (uuid, subscribers))
  {
    // Allocate a new subscriber set and add it the map.
    ACE_NEW_THROW_EX (subscribers,
                      Subscriber_Set (),
                      ::CORBA::NO_MEMORY ());

    ACE_Auto_Ptr <Subscriber_Set> auto_clean (subscribers);

    if (0 != this->subscribers_.bind (uuid, subscribers))
      throw ::CORBA::INTERNAL ();

    // We can safely release the auto pointer.
    auto_clean.release ();
  }

  // Make a duplicate copy of the subscriber, then store it in the
  // container. Using the var_type will ensure that reference counting
  // is handled correctly.
  ::OASIS::DataSubscriber_var tmp = ::OASIS::DataSubscriber::_duplicate (subscriber);
  subscribers->insert (tmp);
}

//
// unregister_subscriber
//
void Tao_PublisherService_i::
unregister_subscriber (const ::OASIS::UUID & probe, ::OASIS::DataSubscriber_ptr subscriber)
{
  // Turn the probe ID into something we can use.
  ACE_Utils::UUID uuid;
  if (!(probe >>= uuid))
    throw ::CORBA::INTERNAL ();

  CORBA::String_var name = subscriber->name ();

  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - received request from %s to unsubscribe to %s\n"),
              name.in (),
              uuid.to_string ()->c_str ()));

  // Locate the subscriber set and remove the subscriber.
  Subscriber_Set * subscribers = 0;

  if (0 == this->subscribers_.find (uuid, subscribers))
    subscribers->remove (subscriber);
}

//
// handle_data
//
int Tao_PublisherService_i::
handle_data (const DAC::Data_Packet & packet)
{
  // Recall the software probe portion of the data sent from the
  // EINode. This will be needed for locating the publisher set
  // that should receive this data.
  Software_Probe_Header probe;
  int retval = probe.recall (packet.probe_data (),
                             packet.probe_data_length (),
                             packet.byte_order ());

  if (0 != retval)
  {
    ACE_Utils::UUID uuid;
    packet.einode_uuid (uuid);
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to recall data ")
                       ACE_TEXT ("from EINode %s\n"),
                       uuid.to_string ()->c_str ()),
                       -1);
  }

  // Locate the subscriber set for the software probe. If we are
  // not able to find a subscriber set, then we can just abort.
  Subscriber_Set * subscribers = 0;
  if (0 != this->subscribers_.find (probe.uuid_, subscribers))
    return 0;

  // Convert the data packet into subscriber data.
  SubscriberDataPacket sdp;
  sdp.byte_order = packet.byte_order ();
  ACE_Utils::UUID uuid;
  packet.einode_uuid (uuid);
  sdp.einode <<= uuid;
  sdp.data.replace (packet.probe_data_length (),
                    packet.probe_data_length (),
                    (::CORBA::Octet *)packet.probe_data ());

  // Iterate over each subscriber and send them the data.
  DataSubscriber_var * subscriber = 0;

  for (Subscriber_Set::ITERATOR iter (*subscribers); !iter.done (); iter.advance ())
  {
    // Get the next subscriber.
    iter.next (subscriber);

    // Send the data to the subscriber.
    (*subscriber)->handle_data (sdp);
  }

  return 0;
}

}

