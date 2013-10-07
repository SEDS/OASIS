// $Id:

#ifndef _OASIS_CONFIGURATION_EXCEPTION_H_
#define _OASIS_CONFIGURATION_EXCEPTION_H_

#include <stdexcept>
#include "Tena_Software_Probe_export.h"

namespace OASIS
{

class OASIS_TENA_SOFTWARE_PROBE_Export Invalid_Child
  : public std::runtime_error
{
public:
  Invalid_Child (const std::string & err) : std::runtime_error (err) {}
};

}
#endif // !defined _OASIS_CONFIGURATION_EXCEPTION_H_

