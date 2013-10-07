// -*- C++ -*-

//=============================================================================
/**
 *  @file       ACE_Logging_Software_Probe.h
 *
 *  $Id: ACE_Logging_Software_Probe.h 2211 2012-07-25 12:55:51Z dfeiock $
 *
 *  @author     Manjula Peiris
 */
//=============================================================================

#ifndef _OASIS_ACE_LOGGING_SOFTWARE_PROBE_H_
#define _OASIS_ACE_LOGGING_SOFTWARE_PROBE_H_

#include "ace/Log_Msg_Callback.h"
#include "../LoggingProbeImpl.h"

#include "ACE_Logging_Software_Probe_export.h"

namespace OASIS
{

/**
 * @class OASIS_ACE_Logging_Software_Probe
 *
 * ACE implementation of the logging probe. This probe also implements
 * the ACE_Log_Msg_Callback interface so it can be registered with the
 * ACE Logging Facilities. When a new log message is received by ACE, it
 * will invoke this callback. This probe will, in turn, send the newly
 * received message to the EINode. This class therefore is a bridge between
 * ACE and OASIS.
 */
class OASIS_ACE_LOGGING_SOFTWARE_PROBE_Export ACE_Logging_Software_Probe :
  public ACE_Log_Msg_Callback,
  public OASIS::LoggingProbeImpl
{
public:
  /// Default constructor.
  ACE_Logging_Software_Probe (void);

  /// Destructor
  virtual ~ACE_Logging_Software_Probe (void);

  /**
   * Callback method to send the log message data
   *
   * @param[in]         log_record          The actual data
   */
  virtual void log (ACE_Log_Record & log_record);
};

}

#if defined (__OASIS_INLINE__)
#include "ACE_Logging_Software_Probe.inl"
#endif

#endif /* _OASIS_ACE_LOGGING_SOFTWARE_PROBE_H_ */
