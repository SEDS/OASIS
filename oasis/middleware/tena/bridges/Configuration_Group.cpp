// $Id:

#include "Configuration_Group.h"

namespace OASIS
{

//
// Configuration_Group
//
Configuration_Group::Configuration_Group (void)
{

}

//
// ~Configuration_Group
//
Configuration_Group::~Configuration_Group (void)
{

}

//
// instance
//
void Configuration_Group::instance (std::string name, Configuration_Instance * child)
{
  this->instances_.insert (std::pair <std::string, Configuration_Instance * > (name, child));
}

//
// instance
//
Configuration_Instance *
Configuration_Group::instance (std::string name)
{
  std::map <std::string, Configuration_Instance * >::iterator iter = this->instances_.find (name);

  if (iter != this->instances_.end())
    return iter->second;

  return 0;
}

//
// [] operator
//
Configuration_Instance &
Configuration_Group::operator [] (std::string child)
{
  Configuration_Instance * result = this->instance (child);
  if (result != 0)
    return *result;

  throw Invalid_Child ("Requested child does not exist.");
}



//
// find_instance
//
void
Configuration_Group::find_instance (std::string needle, Configuration_Instance ** result)
{
  Configuration_Instance * child = this->instance (needle);

  if (child != 0)
    *result = child;
  else
  {
    // Create instance
    Configuration_Instance * child = new Configuration_Instance ();
    child->name (needle);
    this->instances_.insert (std::pair <std::string, Configuration_Instance * > (needle, child));
    *result = child;
  }
}

}
