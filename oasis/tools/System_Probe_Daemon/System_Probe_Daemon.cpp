// $Id:

#include "System_Probe_Daemon.h"

#include "ace/Get_Opt.h"
#include "ace/streams.h"

// System probes
#include "oasis/probes/system/memory/MemoryProbe_Impl.h"
#include "oasis/probes/system/processor/ProcessorProbe_Impl.h"

namespace OASIS
{
namespace System
{

//
// System_Probe_Daemon
//
System_Probe_Daemon::System_Probe_Daemon (void)
 : exit_ (lock_),
   hertz_ ("--hertz=1"),
   dump_ ("")
{

}

//
// ~System_Probe_Daemon
//
System_Probe_Daemon::~System_Probe_Daemon (void)
{

}

//
// run_main
//
int System_Probe_Daemon::run_main (int argc, char * argv [])
{
  if (0 != this->parse_args (argc, argv))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to parse command-line\n")),
                       -1);

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Starting daemon...\n")));

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Loading EINode configuration from %s...\n"),
              this->config_file_.c_str ()));

  if (0 != this->einode_.load_configuration (this->config_file_.c_str ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to load EINode configuration ")
                       ACE_TEXT ("from %s\n"),
                       this->config_file_.c_str ()),
                       -1);

  if (0 != this->attach_and_run ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - Unable to attach system probes\n")),
                       -1);

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Destroying EINode...\n")));

  // Destroy the EINode and its resources.
  this->einode_.destroy ();

  return 0;
}

//
// parse_args
//
int System_Probe_Daemon::parse_args (int argc, char * argv [])
{
  const char * optstr = "c:h";

  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("config", 'c', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("help", 'h', ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("debug", ACE_Get_Opt::NO_ARG);
  get_opt.long_option ("hertz", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("disable", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("dump", ACE_Get_Opt::ARG_REQUIRED);

  // Parse the remaining command-line arguments
  int opt = 0;

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("help", get_opt.long_option ()))
        this->print_help ();
      else if (0 == ACE_OS::strcmp ("debug", get_opt.long_option ()))
        this->enable_log_level (LM_DEBUG);
      else if (0 == ACE_OS::strcmp ("hertz", get_opt.long_option ()))
        this->hertz_ = ACE_CString ("--hertz=") + get_opt.opt_arg ();
      else if (0 == ACE_OS::strcmp ("disable", get_opt.long_option ()))
        this->disabled_ = get_opt.opt_arg ();
      else if (0 == ACE_OS::strcmp ("config", get_opt.long_option ()))
        this->config_file_ = get_opt.opt_arg ();
      else if (0 == ACE_OS::strcmp ("dump", get_opt.long_option ()))
        this->dump_ = get_opt.opt_arg ();
      break;

    case 'h':
      this->print_help ();
      break;

    case 'c':
      this->config_file_ = get_opt.opt_arg ();
      break;
    }
  }

  return 0;
}

//
// attach_and_run
//
int System_Probe_Daemon::attach_and_run (void)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Disabled probes are %s\n"),
              this->disabled_.c_str ()));

  ::OASIS::System::Processor::ProcessorProbe_Impl processor_probe;
  ::OASIS::System::Memory::MemoryProbe_Impl memory_probe;

  // Get the EINode name to unique-ify the probe names
  ::std::string einode_name = this->einode_.configuration ().name ();

  if (::ACE_CString::npos == this->disabled_.find ("Processor"))
  {
    ::std::string probe_name = "ProcessorProbe_" + einode_name;
    ACE_CString init_args (this->hertz_);

    if (::ACE_CString::npos != this->dump_.find ("Processor"))
      init_args += " --dump";

    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - Initializing Processor probe with %s\n"),
                          init_args.c_str ()));

    processor_probe.init (init_args.c_str (), probe_name.c_str ());

    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - Adding processor probe as %s...\n"),
                          probe_name.c_str ()));


    // Attach processor probe
    if (0 != this->einode_.register_probe (&processor_probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to register ProcessorProbe")),
                         -1);
  }

  if (::ACE_CString::npos == this->disabled_.find ("Memory"))
  {
    ::std::string probe_name = "MemoryProbe_" + einode_name;
    ACE_CString init_args (this->hertz_);

    if (::ACE_CString::npos != this->dump_.find ("Memory"))
      init_args += " --dump";

    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - Initializing Memory probe with %s...\n"),
                          init_args.c_str ()));

    // Attach memory probe
    memory_probe.init (init_args.c_str (), probe_name.c_str ());

    ACE_ERROR ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - Adding memory probe as %s...\n"),
                          probe_name.c_str ()));

    if (0 != this->einode_.register_probe (&memory_probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to register MemoryProbe")),
                         -1);
  }

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Activating daemon...\n")));

  // Run the einode
  if (0 != this->einode_.activate ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to activate Einode")),
                       -1);

  // Wait for interrupt
  ACE_GUARD_RETURN (ACE_Thread_Mutex, guard, this->lock_, -1);
  this->exit_.wait ();

  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Deactivating daemon...\n")));

  // Deactivate the EINode, and destroy it.
  if (0 != this->einode_.deactivate ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to deactivate Einode\n")),
                       -1);

  return 0;
}

//
// shutdown
//
void System_Probe_Daemon::shutdown (void)
{
  ACE_ERROR ((LM_DEBUG,
              ACE_TEXT ("%T (%t) - %M - Shutting down daemon...\n")));

  try
  {
    // Signal the application to exit.
    ACE_GUARD (ACE_Thread_Mutex, guard, this->lock_);
    this->exit_.signal ();
  }
  catch (const std::exception & ex)
  {
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("%T (%t) - %M - %s\n"),
                ex.what ()));
  }
}

//
// print_help
//
void System_Probe_Daemon::print_help (void)
{
  static const char * help_msg =
    "Daemon implementation of an OASIS EINode with built-in system probes\n"
    "\n"
    "USAGE: oasis_mon [OPTIONS]\n"
    "\n"
    "General options:\n"
    "  --disable=ProbeID,ProbeID\tSystem probes to disable\n"
    "  --hertz=INT\t\t\tReporting rate for system probes (default: 1/sec)\n"
    "  -c, --config=FILE\t\tEINode Configuration file\n"
    "\n"
    "Output options:\n"
    "  --debug\t\t\tShow debugging output\n"
    "  -h, --help\t\t\tPrint this help message\n"
    "\n"
    "Built-in system probe IDs:\n"
    "  Processor\n"
    "  Memory";

  // Print the help message.
  std::cerr << help_msg << std::endl;

  ACE_OS::exit (1);
}

//
// enable_log_level
//
void System_Probe_Daemon::enable_log_level (int level)
{
  // Get the current priority levels.
  u_long prio = ACE_Log_Msg::instance ()->priority_mask (ACE_Log_Msg::PROCESS);

  // Update the priority levels.
  prio |= level;
  ACE_Log_Msg::instance ()->priority_mask (prio, ACE_Log_Msg::PROCESS);
}

}
}
