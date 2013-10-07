// -*- C++ -*-

//=============================================================================
/**
 * @file        Json_Flatfile_Publisher_Service.h
 *
 * $Id &
 *
 * @author      Darshan G. Puranik
 */
//=============================================================================

#ifndef _OASIS_DAC_JSON_FLATFILE_PUBLISHER_SERVICE_H_
#define _OASIS_DAC_JSON_FLATFILE_PUBLISHER_SERVICE_H_

#include "oasis/DataAcquisitionController/Data_Handler.h"
#include "Json_Flatfile_Publisher_Service_export.h"

#include <iostream>
#include <fstream>

namespace OASIS
{
// Forward decl.
class Software_Probe_Metadata;

/**
 * @class DAC_Websocket_Service
 *
 */
class DAC_Json_Flatfile_Publisher_Service
  : public DAC::Data_Handler
{
public:
  /// Default constructor.
  DAC_Json_Flatfile_Publisher_Service (void);

  /// Destructor.
  virtual ~DAC_Json_Flatfile_Publisher_Service (void);

  /// Initialize the service.
  //virtual int init (int argc, char *argv []);
  virtual int fini (void);

  /// Handle a new data packet.
  virtual int handle_data (const DAC::Data_Packet & packet);

private:
  /// stream to write json objects to flat file.
  std::fstream flat_file;
};

}

//Declare the service factory.
OASIS_DAC_DATA_HANDLER_DECL (OASIS_DAC_JSON_FLATFILE_PUBLISHER_SERVICE, _make_OASIS_DAC_Json_Flatfile_Publisher_Service);

#endif //_OASIS_DAC_JSON_FLATFILE_PUBLISHER_SERVICE_H_