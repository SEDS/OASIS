// $Id: Data_Channel_Service.cpp 2095 2012-01-05 15:51:11Z dfeiock $

#include "Data_Channel_Service.h"
#include "DataChannel_i.h"

#include "ace/Get_Opt.h"

namespace OASIS
{

//
// Tao_Data_Channel_Service
//
Tao_Data_Channel_Service::Tao_Data_Channel_Service (void)
{

}

//
// ~Tao_Data_Channel_Service
//
Tao_Data_Channel_Service::~Tao_Data_Channel_Service (void)
{

}

//
// init
//
int Tao_Data_Channel_Service::init (int argc, ACE_TCHAR * argv [])
{
  try
  {
    // Parse the command-line arguments.
    if (0 != this->parse_args (argc, argv))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to parse command-line arguments\n")),
                         -1);

    // Get the root POA for this ORB.
    ::CORBA::Object_var obj = this->orb_->resolve_initial_references ("RootPOA");

    if (::CORBA::is_nil (obj.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to resolve RootPOA")),
                         -1);

    // Activate the servant for this data channel.
    ::PortableServer::POA_var root_poa = ::PortableServer::POA::_narrow (obj.in ());

    if (::CORBA::is_nil (root_poa.in ()))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - object is not a POA")),
                         -1);

    // Initialize the POA for this object.
    this->initialize_poa (root_poa.in ());
    this->initialize_servant ();

    // Activate the task. This will also the channel to begin receiving
    // events. Right now, we have 1 thread for this service. We should
    // add a command-line parameter that controls the number of threads.
    if (0 != this->task_.get () && 0 != this->task_->activate ())
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to activate task; ")
                         ACE_TEXT ("channel cannot receive any data\n")),
                         -1);

    return 0;
  }
  catch (const ::CORBA::Exception & ex)
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

  return -1;
}

//
// parse_args
//
int Tao_Data_Channel_Service::parse_args (int argc, ACE_TCHAR * argv [])
{
  // Initialize the ORB.
  this->orb_ = ::CORBA::ORB_init (argc, argv);

  if (::CORBA::is_nil (this->orb_.in ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to initialize ORB\n")),
                       -1);

  bool run_orb = false;

  // Parse the remaining command-line arguments.
  const char * optargs = "r";
  ACE_Get_Opt get_opt (argc, argv, optargs, 0);
  int opt = 0;

  get_opt.long_option ("run-orb", 'r', ACE_Get_Opt::NO_ARG);

  while (EOF != (opt = get_opt ()))
  {
    switch (opt)
    {
    case 0:
      if (0 != ACE_OS::strcmp ("run-orb", get_opt.long_option ()))
        run_orb = true;

      break;

    case 'r':
      run_orb = true;
      break;
    }
  }

  if (run_orb)
  {
    // Since we are running our own ORB, we need to allocate a task for
    // processing requests.
    ORB_Server_Task * task = 0;
    ACE_NEW_RETURN (task, ORB_Server_Task (this->orb_.in ()), -1);
    this->task_.reset (task);
  }

  return 0;
}

//
// initialize_poa
//
void Tao_Data_Channel_Service::initialize_poa (::PortableServer::POA_ptr poa)
{
  // Construct the policy list for the LoggingServerPOA.
  ::CORBA::PolicyList policies (6);
  policies.length (6);

  policies[0] = poa->create_thread_policy (PortableServer::ORB_CTRL_MODEL);
  policies[1] = poa->create_servant_retention_policy (PortableServer::RETAIN);
  policies[2] = poa->create_id_assignment_policy (PortableServer::SYSTEM_ID);
  policies[3] = poa->create_id_uniqueness_policy (PortableServer::UNIQUE_ID);
  policies[4] = poa->create_lifespan_policy (PortableServer::TRANSIENT);
  policies[5] = poa->create_request_processing_policy (PortableServer::USE_ACTIVE_OBJECT_MAP_ONLY);

  // Create the child POA for the test logger factory servants.
  this->poa_ =
    poa->create_POA ("DataChannelPOA",
                     ::PortableServer::POAManager::_nil (),
                     policies);

  for (size_t i = 0; i < 6; ++ i)
    policies[i]->destroy ();

  // Activate this POA's manager.
  PortableServer::POAManager_var the_mgr = this->poa_->the_POAManager ();
  the_mgr->activate ();
}

//
// initialize_servant
//
void Tao_Data_Channel_Service::initialize_servant (void)
{
  // Create DAC servant for this application server.
  Tao_DataChannel_i * channel = 0;
  ACE_NEW_THROW_EX (channel,
                    Tao_DataChannel_i (),
                    ::CORBA::NO_MEMORY ());

  this->servant_.reset (channel, true);
  this->servant_.set_trait_value (IOR_Table_Trait (), "DataChannel");
}


//
// handle_activate
//
int Tao_Data_Channel_Service::handle_activate (void)
{
  try
  {
    this->servant_.activate (this->poa_);
    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
}

//
// handle_deactivate
//
int Tao_Data_Channel_Service::handle_deactivate (void)
{
  try
  {
    this->servant_.deactivate ();
    return 0;
  }
  catch (const ::CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
}

//
// fini
//
int Tao_Data_Channel_Service::fini (void)
{
  try
  {
    // Destroy the POA.
    if (!::CORBA::is_nil (this->poa_.in ()))
      this->poa_->destroy (0, 0);

    if (0 != this->task_.get ())
    {
      // Shutdown the ORB, if it exists.
      if (!CORBA::is_nil (this->orb_.in ()))
        this->orb_->shutdown ();

      // Wait for all task to return, then destroy the orb.
      this->task_->wait ();
      this->orb_->destroy ();
    }

    return 0;
  }
  catch (const CORBA::Exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex._info ().c_str ()));
  }
  catch (...)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - caught unknown exception\n")));
  }

  return -1;
}

}

ACE_FACTORY_NAMESPACE_DEFINE (OASIS_TAO_DATACHANNEL,
                              OASIS_Tao_Data_Channel_Service,
                              OASIS::Tao_Data_Channel_Service)
