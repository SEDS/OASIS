// $Id:

#ifndef _OASIS_CONFIGURATION_MEMBER_CONTAINER_H_
#define _OASIS_CONFIGURATION_MEMBER_CONTAINER_H_

#include <string>
#include <map>
#include "Configuration_Exception.h"
#include "Tena_Software_Probe_export.h"

namespace OASIS
{
  // Forward decl.
  class Configuration_Member;

  /**
   * @class Configuration_Member_Container
   *
   * Base class which centralizes logic
   */
  class OASIS_TENA_SOFTWARE_PROBE_Export Configuration_Member_Container
  {
  public:
    /**
     * Initializing constructor.
     */
    Configuration_Member_Container (void);

    /// Destructor.
    ~Configuration_Member_Container (void);

    /// Find or Create a child member
    virtual void find_member (std::string needle, Configuration_Member ** result);

    /// Getter/setter for name
    void name (std::string name);
    std::string name (void);

    /// Getter/setter for child member
    void member (std::string name, Configuration_Member * child);
    Configuration_Member * member (std::string name);

    /// [] overload
    virtual Configuration_Member & operator[] (std::string child);

  protected:
    /// Child members
    std::map <std::string, Configuration_Member *> children_;

    /// name
    std::string name_;
  };
}

#endif // !defined _OASIS_CONFIGURATION_MEMBER_CONTAINER_H_
