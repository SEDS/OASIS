// $Id: Null_PINtool_Probe_Impl.cpp 2240 2013-08-13 18:13:43Z dfeiock $

#include "oasis/tools/PINtool/PINtool.h"

#include "Null_PINtool_Probe_Impl.h"
#if !defined (__OASIS_INLINE__)
#include "Null_PINtool_Probe_Impl.inl"
#endif  // !defined __OASIS_INLINE__

#include "ace/ARGV.h"
#include "ace/Get_Opt.h"

namespace OASIS
{
namespace PIN
{

OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_IMPL (create_OASIS_PIN_Null_PINtool_Probe_Impl_Factory,
                                          Null_PINtool_Probe_Impl_Factory);

//
// setup_instruction
//
void Null_PINtool_Probe_Impl::setup_instruction (Instruction_Builder & builder)
{
  if (this->callback_type_ == "Null_Instruction_Callback0")
    builder.insert_call (IPOINT_BEFORE, (Null_Instruction_Callback0 *)this->callback_);
  else if (this->callback_type_ == "Null_Instruction_Callback1_INST_PTR")
    builder.insert_call (IPOINT_BEFORE, (Null_Instruction_Callback1_INST_PTR *)this->callback_);
}

//
// init
//
int Null_PINtool_Probe_Impl::init (const char * args, const char * name)
{
  // Init base probe
  if (0 != ::OASIS::PIN::Null_PINtool_ProbeImpl::init (args, name))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to init\n")),
                       -1);

  if (0 != ::OASIS::PIN::Instruction_Probe::init ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to init\n")),
                       -1);
  if (0 != this->parse_args (args))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to parse probe options\n")),
                       -1);

  return 0;
}

//
// parse_args
//
int Null_PINtool_Probe_Impl::parse_args (const char * args)
{
  // Convert the command string into a vector of commands.
  ACE_ARGV_T <char> argv (args);
  const char * optargs = "";

  // Parse the command-line options.
  ACE_Get_Opt get_opt (argv.argc (), argv.argv (), optargs, 0);
  get_opt.long_option ("callback", ACE_Get_Opt::ARG_REQUIRED);

  int opt = 0;

  while (EOF != (opt = get_opt ()))
  {
    switch (opt)
    case 0:
      if (0 == ACE_OS::strcmp ("callback", get_opt.long_option ()))
      {
        this->callback_type_ = get_opt.opt_arg ();
        if (this->callback_type_ == "Null_Instruction_Callback0")
          this->callback_ = new Null_Instruction_Callback0 ();
        else if (this->callback_type_ == "Null_Instruction_Callback1_INST_PTR")
          this->callback_ = new Null_Instruction_Callback1_INST_PTR ();
      }
    break;
  }

  if (0 == this->callback_)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - Invalid callback provided\n")),
                       -1);

  return 0;
}

//
// handle_collect_data
//
int Null_PINtool_Probe_Impl::handle_collect_data (void)
{
  return 0;
}

} // namespace OASIS
} // namespace PIN
