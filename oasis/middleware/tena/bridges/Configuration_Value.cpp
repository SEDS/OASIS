// $Id:

#include "Configuration_Value.h"

namespace OASIS
{

//
// Configuration_Value
//
Configuration_Value::Configuration_Value (void)
 : value_()
{

}

//
// ~Configuration_Value
//
Configuration_Value::~Configuration_Value (void)
{

}

//
// value
//
void Configuration_Value::value (std::string & value)
{
  this->value_ = value;
}

//
// value
//
const std::string & Configuration_Value::value (void) const
{
  return this->value_;
}

}
