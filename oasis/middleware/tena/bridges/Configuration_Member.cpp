// $Id:

#include "Configuration_Member.h"
#include "ace/Log_Msg.h"

namespace OASIS
{

//
// Configuration_Member
//
Configuration_Member::Configuration_Member (void)
{

}

//
// ~Configuration_Member
//
Configuration_Member::~Configuration_Member (void)
{

}

//
// has_value
//
bool Configuration_Member::has_value (void)
{
  if (this->value_ == 0)
    return false;

  return true;
}

//
// is_container
//
bool Configuration_Member::is_container (void)
{
  return !this->children_.empty ();
}

//
// find_member
//
void
Configuration_Member::find_member (std::string needle, Configuration_Member ** result)
{
  if (!this->has_value ())
    Configuration_Member_Container::find_member (needle, result);
  else
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - Attempted to find member %s on a ")
                ACE_TEXT ("Configuration_Member which has a value."),
                needle.c_str ()));
    *result = 0;
  }
}

//
// value
//
std::string
Configuration_Member::value (void)
{
  return this->value_->value ();
}

//
// value
//
void Configuration_Member::value (Configuration_Value * value)
{
  if (!this->is_container ())
    this->value_ = value;
}

}
