// $Id: Sender_App.cpp 2211 2012-07-25 12:55:51Z dfeiock $

#include "Sender_App.h"
#include "ace/High_Res_Timer.h"
#include "ace/Get_Opt.h"
#include <fstream>

//
// Sender_App
//
Sender_App::Sender_App (void)
: is_active_ (false),
  output_file_ ("")
{

}

//
// ~Sender_App
//
Sender_App::~Sender_App (void)
{

}

//
// run_main
//
int Sender_App::run_main (int argc, char * argv [])
{
  if (0 != this->parse_args (argc, argv))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to parse command-line\n")),
                       -1);

  if (0 != this->einode_.load_configuration (this->config_file_.c_str ()))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to load EINode configuration\n")),
                       -1);

  // Run with the proper probe
  if (0 == ACE_OS::strcmp ("0", this->probe_type_.c_str ()))
  {
    ::Test::Byte_0Impl probe;
    probe.init ("--name=Byte_0");
    if (0 != this->einode_.register_probe (&probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to register probe")),
                         -1);

    if (0 != this->run_sender (&probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to run einode")),
                         -1);
  }
  else if (0 == ACE_OS::strcmp ("8", this->probe_type_.c_str ()))
  {
    ::Test::Byte_8Impl probe;
    probe.init ("--name=Byte_8");
    if (0 != this->einode_.register_probe (&probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to register probe")),
                         -1);

    if (0 != this->run_sender (&probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to run einode")),
                         -1);
  }
  else if (0 == ACE_OS::strcmp ("16", this->probe_type_.c_str ()))
  {
    ::Test::Byte_16Impl probe;
    probe.init ("--name=Byte_16");
    if (0 != this->einode_.register_probe (&probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to register probe")),
                         -1);

    if (0 != this->run_sender (&probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to run einode")),
                         -1);
  }
  else if (0 == ACE_OS::strcmp ("32", this->probe_type_.c_str ()))
  {
    ::Test::Byte_32Impl probe;
    probe.init ("--name=Byte_32");
    if (0 != this->einode_.register_probe (&probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to register probe")),
                         -1);

    if (0 != this->run_sender (&probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to run einode")),
                         -1);
  }
  else if (0 == ACE_OS::strcmp ("64", this->probe_type_.c_str ()))
  {
    ::Test::Byte_64Impl probe;
    probe.init ("--name=Byte_64");
    if (0 != this->einode_.register_probe (&probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to register probe")),
                         -1);

    if (0 != this->run_sender (&probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to run einode")),
                         -1);
  }
  else if (0 == ACE_OS::strcmp ("128", this->probe_type_.c_str ()))
  {
    ::Test::Byte_128Impl probe;
    probe.init ("--name=Byte_128");
    if (0 != this->einode_.register_probe (&probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to register probe")),
                         -1);

    if (0 != this->run_sender (&probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to run einode")),
                         -1);
  }
  else if (0 == ACE_OS::strcmp ("256", this->probe_type_.c_str ()))
  {
    ::Test::Byte_256Impl probe;
    probe.init ("--name=Byte_256");
    if (0 != this->einode_.register_probe (&probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to register probe")),
                         -1);

    if (0 != this->run_sender (&probe))
      ACE_ERROR_RETURN ((LM_ERROR,
                         ACE_TEXT ("%T (%t) - %M - failed to run einode")),
                         -1);
  }

  if (0 != this->einode_.deactivate ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to deactivate Einode\n")),
                       -1);

  this->einode_.destroy ();

  return 0;
}

//
// parse_args
//
int Sender_App::parse_args (int argc, char * argv [])
{
  const char * optstr = "c:b:o:";

  ACE_Get_Opt get_opt (argc, argv, optstr);

  get_opt.long_option ("config", 'c', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("bytes", 'b', ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("output", 'o', ACE_Get_Opt::ARG_REQUIRED);

  int opt = 0;

  while ((opt = get_opt ()) != EOF)
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("config", get_opt.long_option ()))
        this->config_file_ = get_opt.opt_arg ();
      else if (0 == ACE_OS::strcmp ("bytes", get_opt.long_option ()))
        this->probe_type_ = get_opt.opt_arg ();
      else if (0 == ACE_OS::strcmp ("output", get_opt.long_option ()))
        this->output_file_ = get_opt.opt_arg ();
      break;

    case 'c':
      this->config_file_ = get_opt.opt_arg ();
      break;

    case 'b':
      this->probe_type_ = get_opt.opt_arg ();
      break;

    case 'o':
      this->output_file_ = get_opt.opt_arg ();
      break;
    }
  }

  return 0;
}

//
// run_sender
//
int Sender_App::run_sender (::OASIS::Software_Probe_Impl * probe)
{
  if (0 != this->einode_.activate ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to activate Einode")),
                       -1);

  this->is_active_ = true;
  size_t count = 0;

  // Start the timer for the application
  ACE_High_Res_Timer timer;
  timer.start ();

  while (this->is_active_)
  {
    probe->flush ();
    ++count;
  }

  timer.stop ();

  // Calculate the events/second.
  ACE_hrtime_t elapsed;
  timer.elapsed_time (elapsed);

  double tput = ((double)count / (double)elapsed) * (double)ACE_ONE_SECOND_IN_NSECS;

  if (0 != ACE_OS::strcmp ("", this->output_file_.c_str ()))
  {
    ofstream output;
    output.open (this->output_file_.c_str (), ios::out | ios::app);
    output << count << "," << tput << ::std::endl;
    output.close ();
  }
  else
    ACE_ERROR ((LM_ERROR,
                ACE_TEXT ("Events sent: %d\n")
                ACE_TEXT ("TPUT: %f\n"),
                count,
                tput));

  return 0;
}

//
// shutdown
//
void Sender_App::shutdown (void)
{
  this->is_active_ = false;
}
