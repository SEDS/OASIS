// $Id:

#include "Configuration_Member_Container.h"
#include "Configuration_Member.h"

namespace OASIS
{

//
// Configuration_Member_Container
//
Configuration_Member_Container::Configuration_Member_Container (void)
{

}

//
// ~Configuration_Member_Container
//
Configuration_Member_Container::~Configuration_Member_Container (void)
{

}

//
// name
//
void Configuration_Member_Container::name (std::string name)
{
  this->name_ = name;
}

//
// name
//
std::string Configuration_Member_Container::name (void)
{
  return this->name_;
}

//
// member
//
void Configuration_Member_Container::member (std::string name, Configuration_Member * child)
{
  this->children_.insert (std::pair <std::string, Configuration_Member * > (name, child));
}

//
// member
//
Configuration_Member *
Configuration_Member_Container::member (std::string name)
{
  std::map <std::string, Configuration_Member * >::iterator iter = this->children_.find (name);

  if (iter != this->children_.end())
    return iter->second;

  return 0;
}

//
// [] operator
//
Configuration_Member &
Configuration_Member_Container::operator [] (std::string child)
{
  Configuration_Member * result = this->member (child);

  if (result != 0)
    return *result;

  throw Invalid_Child ("Requsted child does not exist.");
}

//
// find_member
//
void
Configuration_Member_Container::find_member (std::string needle, Configuration_Member ** result)
{
  Configuration_Member * child = this->member (needle);

  // Member exists?
  if (child != 0)
    *result = child;
  else
  {
    // Create member
    Configuration_Member * child (new Configuration_Member);
    child->name (needle);
    this->children_.insert (std::pair <std::string, Configuration_Member *> (needle, child));
    *result = child;
  }
}

}
