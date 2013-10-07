// $Id: TestExecutionManager_i.cpp 2190 2012-05-31 18:13:59Z dfeiock $

#include "TestExecutionManager_i.h"
#include "Manager_App.h"

namespace OASIS
{

//
// TestExecutionManager_i
//
TestExecutionManager_i::
TestExecutionManager_i (TestExecutionManager_App & app)
: app_ (app)
{

}

//
// ~TestExecutionManager_i
//
TestExecutionManager_i::~TestExecutionManager_i (void)
{

}

//
// get_DACs
//
DataAcquisitionControllerSeq * TestExecutionManager_i::get_DACs (void)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - getting a list of DACs\n")));

  // Allocate a new sequence for the DACs.
  DataAcquisitionControllerSeq * tmp_list = 0;
  ACE_NEW_THROW_EX (tmp_list,
                    DataAcquisitionControllerSeq (this->dac_list_.current_size ()),
                    ::CORBA::NO_MEMORY ());

  // Initialize the sequence's length.
  DataAcquisitionControllerSeq_var dac_list (tmp_list);
  dac_list->length (this->dac_list_.current_size ());

  // Resolve each of the DACs in the listing.
  ::CORBA::ULong index = 0;
  typedef DAC_List_Manager::ITERATOR ITERATOR;
  ::CORBA::Object_var obj;

  for (ITERATOR iter (this->dac_list_); !iter.done (); ++ iter)
    dac_list[index ++] = DataAcquisitionController::_duplicate ((*iter).int_id_.in ());

  // Set the final size of the DAC list.
  dac_list->length (index);
  return dac_list._retn ();
}

//
// get_DAC
//
DataAcquisitionController_ptr TestExecutionManager_i::get_DAC (const char * name)
{
  DataAcquisitionController_var the_DAC;
  if (0 != this->dac_list_.find (name, the_DAC))
    throw ::OASIS::TestExecutionManagerViewer::NotFound ();

  return the_DAC;
}

//
// register_DAC
//
void TestExecutionManager_i::register_DAC (DataAcquisitionController_ptr the_DAC)
{
  ::CORBA::String_var dac_name = the_DAC->name ();
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - registering a new DAC named %s\n"),
              dac_name.in ()));

  // Copy and store the DAC.
  DataAcquisitionController_var tmp = DataAcquisitionController::_duplicate (the_DAC);
  int result = 0;
  result = this->dac_list_.bind (dac_name.in (), tmp);

  if (result == 0)
    return;
  else if (result == 1)
    throw ::OASIS::TestExecutionManager::DuplicateName ();
  else if (result == -1)
    throw ::OASIS::TestExecutionManager::RegisterFailed ();
}

//
// unregister_DAC
//
void TestExecutionManager_i::unregister_DAC (DataAcquisitionController_ptr the_DAC)
{
  ::CORBA::String_var dac_name = the_DAC->name ();

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - unregistering DAC named %s\n"),
              dac_name.in ()));

  if (0 != this->dac_list_.unbind (dac_name.in ()))
    throw ::OASIS::TestExecutionManager::NotFound ();
}

//
// name
//
char * TestExecutionManager_i::name (void)
{
  CORBA::String_var str = ::CORBA::string_dup (this->app_.name ().c_str ());
  return str._retn ();
}

}
