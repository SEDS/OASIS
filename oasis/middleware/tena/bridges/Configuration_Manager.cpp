// $Id:

#include "Configuration_Manager.h"
#include <fstream>
#include "ace/Log_Msg.h"

namespace OASIS
{

//
// Configuration_Manager
//
Configuration_Manager::Configuration_Manager (void)
{

}

//
// ~Configuration_Manager
//
Configuration_Manager::~Configuration_Manager (void)
{

}

//
// parse
//
bool
Configuration_Manager::parse (Configuration_Group & group,
                              const ACE_CString & file)
{
  std::ifstream stream;
  stream.open (file.c_str ());
  if (!stream)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - Unable to open configuration file at %s\n"),
                       file.c_str()),
                       false);
  return this->parser_.read_data (stream, group);
}

}
