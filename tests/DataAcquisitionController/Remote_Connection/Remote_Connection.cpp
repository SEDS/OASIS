// $Id: Remote_Connection.cpp 1897 2011-09-07 22:11:00Z hillj $

#include "oasis/DataAcquisitionController/DataAcquisitionControllerC.h"

//
// ACE_TMAIN
//
int ACE_TMAIN (int argc, char * argv [])
{
  try
  {
    // Initialize the ORB.
    CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

    if (CORBA::is_nil (orb.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to initialize ORB\n")),
                         1);

    // Resolve the DAC reference.
    CORBA::Object_var obj = orb->resolve_initial_references ("DAC");

    if (CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve DAC\n")),
                         1);

    OASIS::DataAcquisitionController_var the_DAC = OASIS::DataAcquisitionController::_narrow (obj.in ());

    if (CORBA::is_nil (the_DAC.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - object is not a OASIS::DataAcquisitionController\n")),
                         1);

    // Validate the DAC's information.
    CORBA::String_var name = the_DAC->name ();

    const char * expected_name = "Remote_Connection_Test";
    if (0 != ACE_OS::strcmp (name.in (), expected_name))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - the DAC's name is ")
                         ACE_TEXT ("incorrect; expected %s, received %s\n"),
                         expected_name,
                         name.in ()),
                         1);

    ACE_ERROR ((LM_INFO,
                ACE_TEXT ("%T (%t) - %M - the test completed successfully\n")));

    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }

  return 1;
}
