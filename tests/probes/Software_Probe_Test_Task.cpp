// $Id: Software_Probe_Test_Task.cpp 2095 2012-01-05 15:51:11Z dfeiock $

#include "Software_Probe_Test_Task.h"
#include "oasis/probes/Software_Probe_Impl.h"

namespace OASIS
{
//
// Software_Probe_Test_Task
//
Software_Probe_Test_Task::
Software_Probe_Test_Task (Software_Probe_Impl & probe)
: probe_ (probe)
{

}

//
// ~Software_Probe_Test_Task
//
Software_Probe_Test_Task::~Software_Probe_Test_Task (void)
{

}

//
// svc
//
int Software_Probe_Test_Task::svc (void)
{
  try
  {
    if (0 != this->probe_.handle_collect_data ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - handle_collect_data () failed\n")),
                         -1);

    if (0 != this->probe_.flush ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - flush () failed\n")),
                         -1);

    return 0;
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));
  }

  return -1;
}

}
