// $Id: IOR_Table_Trait.cpp 1863 2011-08-19 18:39:59Z hillj $

#include "IOR_Table_Trait.h"
#include "tao/IORTable/IORTable.h"

namespace OASIS
{

//
// handle_activate
//
int IOR_Table_Trait::
handle_activate (::CORBA::Object_ptr obj, const ACE_CString & value)
{
  // Get the ORB from the object.
  ::CORBA::ORB_var orb = obj->_get_orb ();

  if (::CORBA::is_nil (orb.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to resolve ORB\n")),
                       1);

  // Locate the IORTable for the application.
  ::CORBA::Object_var temp = orb->resolve_initial_references ("IORTable");
  ::IORTable::Table_var ior_table = IORTable::Table::_narrow (temp.in ());

  if (::CORBA::is_nil (ior_table.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to resolve IOR table\n")),
                       1);

  // Get the IOR string for the object reference.
  ::CORBA::String_var str  = orb->object_to_string (obj);

  ACE_DEBUG ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - registering object with IORTable (%s)\n"),
              value.c_str ()));

  ior_table->bind (value.c_str (), str.in ());

  return 0;
}

//
// handle_deactivate
//
int IOR_Table_Trait::
handle_deactivate (::CORBA::Object_ptr obj,  const ACE_CString & value)
{
  // Get the ORB from the object.
  ::CORBA::ORB_var orb = obj->_get_orb ();

  if (::CORBA::is_nil (orb.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to resolve ORB\n")),
                       1);

  // Locate the IORTable for the application.
  ::CORBA::Object_var temp = orb->resolve_initial_references ("IORTable");
  ::IORTable::Table_var ior_table = IORTable::Table::_narrow (temp.in ());

  if (::CORBA::is_nil (ior_table.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to resolve IOR table\n")),
                       1);

  // Get the IOR string for the object reference.
  ACE_DEBUG ((LM_INFO,
              ACE_TEXT ("%T (%t) - %M - unregistering object with IORTable (%s)\n"),
              value.c_str ()));

  ior_table->unbind (value.c_str ());

  return 0;
}

}
