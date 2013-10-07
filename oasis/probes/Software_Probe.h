// -*- C++ -*-

//=============================================================================
/**
 * @file        Software_Probe.h
 *
 * $Id: Software_Probe.h 2211 2012-07-25 12:55:51Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_SOFTWARE_PROBE_H_
#define _OASIS_SOFTWARE_PROBE_H_

#include "SoftwareProbe_Core_export.h"
#include "oasis/config.h"

#include "ace/CDR_Stream.h"
#include "ace/Time_Value.h"
#include "ace/UUID.h"

#include "Software_Probe_Metadata.h"

namespace OASIS
{

/**
 * @class Software_Probe
 *
 * Base class for all software probes stubs. The software probe stub
 * constains the metadata for a given probe. In addition, it contains
 * a method for recalling a software probe's data that was previously
 * packaged by an implementation.
 */
class OASIS_SOFTWAREPROBE_CORE_Export Software_Probe
{
public:
  /**
   * Initializing constructor.
   *
   * @param[in]         metadata        Binding metadata for probe.
   */
  Software_Probe (void);

  /// Destructor
  virtual ~Software_Probe (void);

  /// Get the software probe's metadata.
  virtual const Software_Probe_Metadata & metadata (void) const = 0;

  /**
   * Recall the software probes data.
   *
   * @param[in]       data          Pointer to the data
   * @param[in]       length        Length of the data
   * @param[in]       byte_order    The order of the bytes
   * @return          Number of bytes recalled.
   */
  virtual int recall (const char * data,
                      size_t length,
                      int byte_order);

  /// Dump the contents of the probe to ACE_DEUBG
  virtual void dump (std::ostream & output) const;

  /// Get the software probe's UUID
  const ACE_Utils::UUID & uuid (void) const;

  /// Get the software probe's latest timestamp for the data
  const ACE_Time_Value & timestamp (void) const;

  /// Get the software probe's current sequence number for the data
  const ACE_UINT32 & sequence_number (void) const;

  /// Get the software probe's state for the data
  const ACE_UINT16 & state (void) const;

  /// Get the size of the software probe's data
  const ACE_UINT32 & data_size (void) const;

  /// Get the software probe's instance name.
  const ACE_CString & instance_name (void) const;

protected:
  /// Helper version of the recall method that will return the
  /// current location in data for the next read after this method
  /// has returned.
  virtual int recall (ACE_InputCDR & input);

  /// UUID of the probe
  ACE_Utils::UUID uuid_;

  /// The latest timestamp of the probe
  ACE_Time_Value last_ts_;

  /// The current sequence number for the probe
  ACE_UINT32 seqnum_;

  /// The state of the probe
  ACE_UINT16 state_;

  /// The size of the software probe's data
  ACE_UINT32 datasize_;

  /// Instance name assigned to the probe.
  ACE_CString name_;
};

}

#if defined (__OASIS_INLINE__)
#include "Software_Probe.inl"
#endif

#endif  // !defined _OASIS_SOFTWARE_PROBE_H_
