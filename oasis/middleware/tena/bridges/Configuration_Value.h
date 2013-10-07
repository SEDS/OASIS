// $Id:

#ifndef _OASIS_CONFIGURATION_VALUE_H_
#define _OASIS_CONFIGURATION_VALUE_H_

#include <string>
#include "Tena_Software_Probe_export.h"

namespace OASIS
{
  /**
   * @class Configuration_Value
   *
   * Class which represents a single value
   */
  class OASIS_TENA_SOFTWARE_PROBE_Export Configuration_Value
  {
  public:
    /**
     * Initializing constructor.
     */
    Configuration_Value (void);

    /// Destructor.
    ~Configuration_Value (void);

    /// Setter and getter methods for value
    const std::string & value (void) const;
    void value (std::string & value);

  private:
    /// Value
    std::string value_;
  };
}

#endif // !defined _OASIS_CONFIGURATION_VALUE_H_
