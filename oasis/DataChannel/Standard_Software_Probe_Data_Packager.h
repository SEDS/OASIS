// -*- C++ -*-

//=============================================================================
/**
 * @file        Software_Probe_Data_Packet.h
 *
 * $Id: Standard_Software_Probe_Data_Packager.h 2224 2012-12-10 06:35:58Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_STANDARD_SOFTWARE_PROBE_DATA_PACKAGER_H_
#define _OASIS_STANDARD_SOFTWARE_PROBE_DATA_PACKAGER_H_

#include "Software_Probe_Data_Packager.h"

#include "ace/Containers_T.h"
#include "ace/CDR_Stream.h"

#include "Data_Channel_export.h"
#include "oasis/config.h"

namespace OASIS
{
/**
 * @class Standard_Software_Probe_Data_Packager
 *
 * Utility class for packaging a software probe's data. The packager
 * uses the Common Data Representation (CDR) format. The layout of
 * the data is as follows:
 *
 *   . Magic (4 bytes)
 *   . Version (2 bytes)
 *   . Uuid (16 bytes)
 *   . Seconds (4 bytes)
 *   . Microseconds (4 bytes)
 *   . Sequence (4 bytes)
 *   . State (2 bytes)
 *   . Data size (4 bytes)
 *   . Instance name (Variable size)
 *
 * The total number of the bytes for the constant portion of the header
 * is 40 bytes. The instance name is 4 bytes + the number of characters
 * in the string, including the NULL terminator.
 *
 * The actual data of the software probe occurs after the instance name
 * in the software probe's header. The amount of data that appears in
 * this section is captured by the data size variable in the header.
 */
class OASIS_DATA_CHANNEL_Export Standard_Software_Probe_Data_Packager :
  public Software_Probe_Data_Packager
{
public:
  /// Default constructor.
  Standard_Software_Probe_Data_Packager (void);

  /// Destructor
  virtual ~Standard_Software_Probe_Data_Packager (void);

  /// Factory method
  virtual Software_Probe_Data_Packager * clone (void);

  /**
   * Initialize the packager.
   *
   * @param[in]         uuid          Uuid of the probe type.
   * @param[in]         name          Name of the probe.
   * @param[in]         data_size     Size of the probe's data.
   */
  virtual bool init (const ACE_Utils::UUID & uuid, const ACE_CString & name, size_t data_size = 0);

  /// Set the instance name for the header.
  virtual bool instance_name (const ACE_CString & name);

  /**
   * Update the package's contents with the latest information.
   *
   * @param[in]       tv              Latest timestamp
   * @param[in]       seqnum          Current sequence number
   * @param[in]       state           Current state
   */
  virtual void update (const ACE_Time_Value & tv, ACE_UINT32 seqnum, ACE_UINT32 state);

  /**
   * Get the binary stream for the data packet. This freezes the
   * current stream for constructing the header.
   *
   * @return        Binary stream of the data packet.
   */
  virtual const char * stream (void);

  /// Get the current size of the stream.
  virtual size_t length (void) const;

  /// Get the current size of the data within the stream
  virtual size_t data_size (void) const;

  /// Reset the packager to be reused.
  virtual void reset (void);

  /// Write methods
  virtual int write_boolean (const bool & in);
  virtual int write_string (const ACE_CString & in);
  virtual int write_int8 (const ACE_INT8 & in);
  virtual int write_int16 (const ACE_INT16  & in);
  virtual int write_int32 (const ACE_INT32 & in);
  virtual int write_int64 (const ACE_INT64 & in);
  virtual int write_uint8 (const ACE_UINT8 & in);
  virtual int write_uint16 (const ACE_UINT16 & in);
  virtual int write_uint32 (const ACE_UINT32 & in);
  virtual int write_uint64 (const ACE_UINT64 & in);
  virtual int write_real32 (const double & in);
  virtual int write_real64 (const long double & in);

protected:
  /// Set the instance name for the header.
  bool instance_name_i (const ACE_CString & name);

  /// Placeholder for the seconds
  char * ph_tv_sec_;

  /// Placeholder for the microseconds
  char * ph_tv_usec_;

  /// Placeholder for the state
  char * ph_state_;

  /// Placeholder for the sequence number
  char * ph_seqnum_;

  /// Placeholder for the data size.
  char * ph_data_size_;

private:
  /// Initialization flag.
  bool is_init_;

  /// Target output CDR stream.
  ACE_OutputCDR probe_;

  /// Location in the stream where the header ends
  size_t end_of_header_;

  /// Size of the stream, if fixed
  size_t fixed_size_;
};

}

#if defined (__OASIS_INLINE__)
#include "Standard_Software_Probe_Data_Packager.inl"
#endif

#endif  // !defined _EISA_SOFTWARE_PROBE_DATA_PACKET_H_
