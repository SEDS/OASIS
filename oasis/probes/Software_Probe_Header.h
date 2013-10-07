//  $Id: Software_Probe_Header.h 2257 2013-09-08 03:34:37Z hillj $

#ifndef _SOFTWARE_PROBE_HEADER_H_
#define _SOFTWARE_PROBE_HEADER_H_

#include "SoftwareProbe_Core_export.h"
#include "oasis/config.h"

#include <iostream>
#include "ace/Time_Value.h"
#include "ace/UUID.h"
#include "ace/CDR_Stream.h"

namespace OASIS
{

/**
 * @struct Software_Probe_Header
 *
 * Header for all software probes. It contains infomration related
 * to the latest collect metrics.
 */
class OASIS_SOFTWAREPROBE_CORE_Export Software_Probe_Header
{
public:
  /// Default constructor.
  Software_Probe_Header (void);

  /// Destructor
  ~Software_Probe_Header (void);

  /// Compare the metadata for equality.
  bool operator == (const Software_Probe_Header & rhs) const;

  /// Compare the metadata for inequality.
  bool operator != (const Software_Probe_Header & rhs) const;

  /// Dump the contents of the metadata to ACE_DEBUG
  void dump (std::ostream & output) const;

  /**
   * Recall a software probe's header
   *
   * @param[in]       data          Pointer to the data
   * @param[in]       length        Length of the data
   * @param[in]       byte_order    The order of the bytes
   * @return          Number of bytes recalled.
   */
  int recall (const char * data,
              size_t length,
              int byte_order);

  /// Helper version of the recall method that will return the
  /// current location in data for the next read after this method
  /// has returned.
  int recall (ACE_InputCDR & input);

  /// UUID assigned to this software probe.
  ACE_Utils::UUID uuid_;

  /// The lastest timestamp.
  ACE_Time_Value last_ts_;

  /// The current sequence number for the data.
  ACE_UINT32 seqnum_;

  /// The state of the software probe.
  ACE_UINT16 state_;

  /// The size of the software probe's data.
  ACE_UINT32 datasize_;

  /// Instance name of the probe
  ACE_CString name_;
};

}

#if defined (__OASIS_INLINE__)
#include "Software_Probe_Header.inl"
#endif

#endif  // !defined _SOFTWARE_PROBE_HEADER_H_
