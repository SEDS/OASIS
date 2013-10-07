// $Id: IOR_File_Trait.cpp 1934 2011-09-28 14:56:30Z hillj $

#include "IOR_File_Trait.h"
#include "ace/OS_NS_unistd.h"
#include "ace/streams.h"

namespace OASIS
{

//
// handle_activate
//
int IOR_File_Trait::
handle_activate (::CORBA::Object_ptr obj, const ACE_CString & value)
{
  OASIS_TAO_TRACE ("int IOR_File_Trait::handle_activate (::CORBA::Object_ptr, const ACE_CString &)");

  // Get the ORB for this object.
  ::CORBA::ORB_var orb = obj->_get_orb ();

  if (::CORBA::is_nil (orb.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to resolve ORB\n")),
                       1);

  // Convert the object to a string.
  ::CORBA::String_var str = orb->object_to_string (obj);

  // Write the string to the specified file.
  std::ofstream file;
  file.open (value.c_str ());

  if (!file.is_open ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to open %s for writing\n"),
                       value.c_str ()),
                       1);

  file << str.in ();
  file.close ();

  return 0;
}

//
// handle_deactivate
//
int IOR_File_Trait::
handle_deactivate (::CORBA::Object_ptr obj,  const ACE_CString & value)
{
  OASIS_TAO_TRACE ("int IOR_File_Trait::handle_deactivate (::CORBA::Object_ptr,  const ACE_CString &)");

  ACE_OS::unlink (value.c_str ());
  return 0;
}

}
