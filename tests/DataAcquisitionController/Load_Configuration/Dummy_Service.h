// -*- C++ -*-

//=============================================================================
/**
 * @file        Dummy_Service.h
 *
 * $Id: Dummy_Service.h 1991 2011-10-10 02:05:19Z hillj $
 *
 * @author      James H. Hill
 */
//=============================================================================

#ifndef _OASIS_DAC_DUMMY_SERVICE_H_
#define _OASIS_DAC_DUMMY_SERVICE_H_

#include "oasis/DataAcquisitionController/Data_Handler.h"
#include "oasis/DataAcquisitionController/Data_Channel.h"

#include "Load_Configuration_export.h"

namespace OASIS
{

/**
 * @class Dummy_Data_Handler
 *
 * Publisher service for the DAC. This is a static service handler
 * in that it is always loaded by the DAC.
 */
class OASIS_LOAD_CONFIGURATION_TEST_Export Dummy_Data_Handler :
  public DAC::Data_Handler
{
public:
  /// Default constructor.
  Dummy_Data_Handler (void);

  /// Destructor.
  virtual ~Dummy_Data_Handler (void);

  /**
   * Initialize the archive data handler service.
   *
   * @param[in]       argc        Number of command-line arguments
   * @param[in]       argv        The command-line arguments
   */
  virtual int init (int argc, ACE_TCHAR *argv[]);

  /// Finalize the data handler.
  virtual int fini (void);
};

/**
 * @class Dummy_Data_Handler
 *
 * Publisher service for the DAC. This is a static service handler
 * in that it is always loaded by the DAC.
 */
class OASIS_LOAD_CONFIGURATION_TEST_Export Dummy_Data_Channel :
  public DAC::Data_Channel
{
public:
  /// Default constructor.
  Dummy_Data_Channel (void);

  /// Destructor.
  virtual ~Dummy_Data_Channel (void);

  /**
   * Initialize the archive data handler service.
   *
   * @param[in]       argc        Number of command-line arguments
   * @param[in]       argv        The command-line arguments
   */
  virtual int init (int argc, ACE_TCHAR *argv[]);

  /// Finalize the data handler.
  virtual int fini (void);
};

}

OASIS_DAC_DATA_HANDLER_DECL (OASIS_LOAD_CONFIGURATION_TEST, _make_OASIS_Dummy_Data_Handler);

ACE_FACTORY_DECLARE (OASIS_LOAD_CONFIGURATION_TEST, OASIS_Dummy_Data_Channel)

#endif  // !defined _OASIS_DAC_DUMMY_SERVICE_H_
