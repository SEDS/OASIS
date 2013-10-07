// -*- C++ -*-

//=============================================================================
/**
 * @file        Software_Probe_Data_Packet.h
 *
 * $Id: Software_Probe_Data_Packager.h 2224 2012-12-10 06:35:58Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_SOFTWARE_PROBE_DATA_PACKAGER_H_
#define _OASIS_SOFTWARE_PROBE_DATA_PACKAGER_H_

#include "ace/CDR_Stream.h"
#include "ace/UUID.h"
#include "Data_Channel_export.h"
#include "oasis/config.h"

namespace OASIS
{
/**
 * @class Software_Probe_Data_Packager
 *
 * Abstract base classes for all Software_Probe_Data_Packagers.
 * Concrete Software_Probe_Data_Packagers vary their implementation
 * based on the networking middleware technology in use.
 */
class OASIS_DATA_CHANNEL_Export Software_Probe_Data_Packager
{
public:
  /// Default constructor.
  Software_Probe_Data_Packager (void);

  /// Destructor
  virtual ~Software_Probe_Data_Packager (void);

  /// Release the packager
  virtual void release (void);

  /// Factory method
  virtual Software_Probe_Data_Packager * clone (void) = 0;

  /**
   * Initialize the packager.
   *
   * @param[in]         uuid          Uuid of the probe type.
   * @param[in]         name          Name of the probe.
   * @param[in]         data_size     Size of the probe's data.
   */
  virtual bool init (const ACE_Utils::UUID & uuid, const ACE_CString & name, size_t data_size = 0) = 0;

  /// Set the instance name for the header.
  virtual bool instance_name (const ACE_CString & name) = 0;

  /**
   * Update the package's contents with the latest information.
   *
   * @param[in]       tv              Latest timestamp
   * @param[in]       seqnum          Current sequence number
   * @param[in]       state           Current state
   */
  virtual void update (const ACE_Time_Value & tv, ACE_UINT32 seqnum, ACE_UINT32 state) = 0;

  /**
   * Get the binary stream for the data packet. This freezes the
   * current stream for constructing the header.
   *
   * @return        Binary stream of the data packet.
   */
  virtual const char * stream (void) = 0;

  /// Get the current size of the stream.
  virtual size_t length (void) const = 0;

  /// Get the current size of the data within the stream
  virtual size_t data_size (void) const = 0;

  /// Reset the packager to be reused.
  virtual void reset (void) = 0;

  /// Writer methods
  virtual int write_boolean (const bool & in) = 0;
  virtual int write_string (const ACE_CString & in) = 0;
  virtual int write_int8 (const ACE_INT8 & in) = 0;
  virtual int write_int16 (const ACE_INT16  & in) = 0;
  virtual int write_int32 (const ACE_INT32 & in) = 0;
  virtual int write_int64 (const ACE_INT64 & in) = 0;
  virtual int write_uint8 (const ACE_UINT8 & in) = 0;
  virtual int write_uint16 (const ACE_UINT16 & in) = 0;
  virtual int write_uint32 (const ACE_UINT32 & in) = 0;
  virtual int write_uint64 (const ACE_UINT64 & in) = 0;
  virtual int write_real32 (const double & in) = 0;
  virtual int write_real64 (const long double & in) = 0;
};

}

#if defined (__OASIS_INLINE__)
#include "Software_Probe_Data_Packager.inl"
#endif

#endif  // !defined _OASIS_SOFTWARE_PROBE_DATA_PACKET_H_
