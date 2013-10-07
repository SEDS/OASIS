// -*- C++ -*-

//=============================================================================
/**
 * @file        Data_Channel.h
 *
 * $Id: Data_Channel.h 2092 2012-01-04 17:01:33Z dfeiock $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DYNAMIC_DATA_CHANNEL_H_
#define _OASIS_DYNAMIC_DATA_CHANNEL_H_

#include "ace/SString.h"
#include "ace/Service_Object.h"
#include "ace/RW_Thread_Mutex.h"
#include "ace/Hash_Map_Manager.h"

#include "oasis/DataChannel/Data_Channel.h"

#include "EINode_Core_export.h"

namespace OASIS
{
// Forward decl.
class Software_Probe_Impl;

// Forward decl.
class Standard_EINode;

/// Type definition of probe map type.
typedef ACE_Hash_Map_Manager <ACE_CString,
                              Software_Probe_Impl *,
                              ACE_RW_Thread_Mutex>
                              SoftwareProbe_Hash_Map;

/**
 * @class Data_Channel_Service
 *
 * Base class for data channel services. These are objects loaded
 * by the service configurator.
 */
class OASIS_EINODE_CORE_Export Data_Channel_Service :
  public ACE_Service_Object,
  public Data_Channel
{
public:
  virtual void set_einode (Standard_EINode * einode) = 0;

  /**
   * Register the probes associated with the EINode to the DAC.
   *
   * @throws  Connect_Error      Connecting to the DAC failed
   * @throws  Transient_Error    Failed to send registration data
   */
  virtual int perform_registration (const SoftwareProbe_Hash_Map & probes) = 0;
};

}

#endif  // !defined _OASIS_STANDARD_EINODE_DATA_CHANNEL_H_
