// -*- C++ -*-

//=============================================================================
/**
 * @file        Software_Probe_Data_Preparer.h
 *
 * $Id: Software_Probe_Data_Preparer.h 2140 2012-03-23 16:51:45Z dfeiock $
 *
 * @author      Dennis Feiock
 */
//=============================================================================

#ifndef _OASIS_SOFTWARE_PROBE_DATA_PREPARER_H_
#define _OASIS_SOFTWARE_PROBE_DATA_PREPARER_H_

#include "SoftwareProbe_Core_export.h"
#include "oasis/config.h"

#include "ace/CDR_Base.h"
#include "ace/Message_Block.h"
#include "oasis/DataAcquisitionController/Data_Packet.h"

namespace OASIS
{
/**
 * @class Software_Probe_Data_Preparer
 *
 * Utility class for preparing a software probe's data for recall.
 *
 */
class OASIS_SOFTWAREPROBE_CORE_Export Software_Probe_Data_Preparer
{
public:
  /// Initializing constructor.
  Software_Probe_Data_Preparer (const char * data, size_t length);

  /// Initializing constructor.
  Software_Probe_Data_Preparer (OASIS::DAC::Data_Packet & packet);

  /// Destructor
  ~Software_Probe_Data_Preparer (void);

  /// Get the prepared message block
  ACE_Message_Block * message_block (void);

private:
  /// Message block the preparer is working with.
  ACE_Message_Block block_;
};

}

#if defined (__OASIS_INLINE__)
#include "Software_Probe_Data_Preparer.inl"
#endif

#endif  // !defined _OASIS_SOFTWARE_PROBE_DATA_PREPARER_H_
