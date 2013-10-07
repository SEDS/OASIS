// $Id:

#ifndef _OASIS_CONFIGURATION_MEMBER_H_
#define _OASIS_CONFIGURATION_MEMBER_H_

#include "Configuration_Member_Container.h"
#include "Configuration_Value.h"
#include "Tena_Software_Probe_export.h"

namespace OASIS
{
  /**
   * @class Configuration_Member
   *
   * Class which represents a member.
   * Either aggregates Configuration_Members or
   * contains a single Configuration_Value.
   */
  class OASIS_TENA_SOFTWARE_PROBE_Export Configuration_Member
    : public Configuration_Member_Container
  {
  public:
    /**
     * Initializing constructor.
     */
    Configuration_Member (void);

    /// Destructor.
    ~Configuration_Member (void);

    /// Simple tests to identify contents
    bool has_value (void);
    bool is_container (void);

    /// Find or create child Configuration_Member
    void find_member (std::string needle, Configuration_Member ** result);

    /// Getter/setter for value
    std::string value (void);
    void value (Configuration_Value * value);

  private:
    /// Value stored by member
    Configuration_Value * value_;
  };
}

#endif // !defined _OASIS_CONFIGURATION_MEMBER_H_
