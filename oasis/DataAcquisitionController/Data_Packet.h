// -*- C++ -*-

//=============================================================================
/**
 * @file        Data_Packet.h
 *
 * $Id: Data_Packet.h 2152 2012-04-16 20:13:33Z dpuranik $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DAC_DATA_PACKET_H_
#define _OASIS_DAC_DATA_PACKET_H_

#include "oasis/config.h"
#include "ace/UUID.h"
#include "DAC_Core_export.h"

namespace OASIS
{
namespace DAC
{

/**
 * @class Data_Packet
 *
 * Data packet sent from an EINode.
 */
class OASIS_DAC_CORE_Export Data_Packet
{
public:
  // Default ctor
  Data_Packet (void);

  // Dtor
  virtual ~Data_Packet (void);

  /// The byte order of the data
  virtual bool byte_order (void) const = 0;

  /// UUID of the EINode
  virtual void einode_uuid (ACE_Utils::UUID & uuid) const = 0;

  /// The software probe's data.
  virtual const char * probe_data (void) const = 0;

  /// Length of the software probe data.
  virtual size_t probe_data_length (void) const = 0;
};

}
}

#if defined (__OASIS_INLINE__)
#include "Data_Packet.inl"
#endif

#endif  // !defined _OASIS_EINODE_DATA_PACKET_H_
