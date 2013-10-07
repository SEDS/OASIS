// -*- C++ -*-

//=============================================================================
/**
 * @file        Data_Packet.h
 *
 * $Id: Tao_Data_Packet.h 2141 2012-03-23 17:50:34Z dfeiock $
 *
 * @author      Dennis Feiock
 */
//=============================================================================

#ifndef _OASIS_TAO_DATA_PACKET_H_
#define _OASIS_TAO_DATA_PACKET_H_

#include "oasis/DataAcquisitionController/Data_Packet.h"
#include "DataChannelC.h"

namespace OASIS
{

/**
 * @class Tao_Data_Packet
 *
 * Wrapper for the ::OASIS::DataPacket used by tao
 */
class Tao_Data_Packet : public DAC::Data_Packet
{
public:
  // Initalizing ctor
  Tao_Data_Packet (const DataPacket & packet);

  // Dtor
  virtual ~Tao_Data_Packet (void);

  // The byte order of the data
  virtual bool byte_order (void) const;

  // UUID of the EINode
  virtual void einode_uuid (ACE_Utils::UUID & uuid) const;

  // The software probe's data
  virtual const char * probe_data (void) const;

  // Length of the software probe data
  virtual size_t probe_data_length (void) const;

private:
  // DataPacket this object wraps
  const DataPacket & packet_;
};

}

#if defined (__OASIS_INLINE__)
#include "Tao_Data_Packet.inl"
#endif

#endif // !defined _OASIS_DAC_TAO_DATA_PACKET_H_
