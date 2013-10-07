// $Id: Tao_Data_Packet.cpp 2235 2013-02-06 20:18:09Z dfeiock $

#include "Tao_Data_Packet.h"
#include "oasis/middleware/tao/UUID.h"

#if !defined (__OASIS_INLINE__)
#include "Tao_Data_Packet.inl"
#endif

namespace OASIS
{

//
// einode_uuid
//
void Tao_Data_Packet::einode_uuid (ACE_Utils::UUID & uuid) const
{
  this->packet_.einode_uuid >>= uuid;
}
}
