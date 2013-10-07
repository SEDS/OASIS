// $Id:

#ifndef _OASIS_CONFIGURATION_GROUP_H_
#define _OASIS_CONFIGURATION_GROUP_H_

#include "Configuration_Instance.h"
#include <string>
#include "Configuration_Exception.h"
#include "Tena_Software_Probe_export.h"

namespace OASIS
{
  /**
   * @class Configuration_Group
   *
   * Class which represents a group of configurations.
   * Aggregates Configuration_Instances.
   */
  class OASIS_TENA_SOFTWARE_PROBE_Export Configuration_Group
  {
  public:
    /// Initializing constructor.
    Configuration_Group (void);

    /// Destructor.
    ~Configuration_Group (void);

    /// Find or Create a child instance
    virtual void find_instance (std::string needle, Configuration_Instance ** result);

    /// Getter/setter for child member
    void instance (std::string name, Configuration_Instance * child);
    Configuration_Instance * instance (std::string name);

    /// [] overload
    Configuration_Instance & operator[] (std::string child);

  private:
    /// Map of instances
    std::map <std::string, Configuration_Instance *> instances_;
  };
}

#endif // !defined _OASIS_CONFIGURATION_GROUP_H_
