// $Id:

#ifndef _OASIS_CONFIGURATION_MANAGER_H_
#define _OASIS_CONFIGURATION_MANAGER_H_

#include "Configuration_Group.h"
#include "Configuration_Parser.h"
#include "ace/SString.h"
#include "Tena_Software_Probe_export.h"

namespace OASIS
{
  /**
   * Class which manages a Configuration_Parser
   */
  class OASIS_TENA_SOFTWARE_PROBE_Export Configuration_Manager
  {
  public:
    /**
     * Initializing constructor.
     */
    Configuration_Manager (void);

    /// Destructor.
    ~Configuration_Manager (void);

    /**
     * Parse the config into the group
     *
     * @param[in]       group     Group to parse into
     * @param[in]       file      File to parse
     */
    bool parse (Configuration_Group & group, const ACE_CString & file);

  private:
    Configuration_Parser parser_;
  };
}

#endif // !defined _OASIS_CONFIGURATION_MANAGER_H_
