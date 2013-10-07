// $Id:

#ifndef _OASIS_CONFIGURATION_INSTANCE_H_
#define _OASIS_CONFIGURATION_INSTANCE_H_

#include "Configuration_Member_Container.h"
#include "Configuration_Member.h"
#include "Tena_Software_Probe_export.h"

namespace OASIS
{
  /**
   * @class Configuration_Instance
   *
   * Class which represents an instance.
   * Aggregates Configuration_Members.
   */
  class OASIS_TENA_SOFTWARE_PROBE_Export Configuration_Instance
    : public Configuration_Member_Container
  {
  public:
    /**
     * Initializing constructor.
     */
    Configuration_Instance (void);

    /// Destructor.
    ~Configuration_Instance (void);
  };
}

#endif // !defined _OASIS_CONFIGURATION_INSTANCE_H_
