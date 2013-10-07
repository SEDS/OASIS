// $Id: Tao_Data_Packet.inl 2235 2013-02-06 20:18:09Z dfeiock $

namespace OASIS
{

//
// Tao_Data_Packet
//
OASIS_INLINE
Tao_Data_Packet::Tao_Data_Packet (const DataPacket & packet)
: packet_ (packet)
{

}

//
// ~Tao_Data_Packet
//
OASIS_INLINE
Tao_Data_Packet::~Tao_Data_Packet (void)
{

}

//
// byte_order
//
OASIS_INLINE
bool Tao_Data_Packet::byte_order (void) const
{
  return this->packet_.byte_order;
}

//
// probe_data_length
//
OASIS_INLINE
size_t Tao_Data_Packet::probe_data_length (void) const
{
  return this->packet_.data.length ();
}

//
// probe_data
//
OASIS_INLINE
const char * Tao_Data_Packet::probe_data (void) const
{
  return (const char *)this->packet_.data.get_buffer ();
}

}
