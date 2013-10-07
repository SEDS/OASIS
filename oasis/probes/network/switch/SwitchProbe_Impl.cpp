// $Id: SwitchProbe_Impl.cpp 2232 2013-01-28 16:07:41Z dfeiock $

#include "ace/ARGV.h"
#include "ace/Get_Opt.h"
#include <iostream>
#include "SwitchProbe_Impl.h"



#if !defined (__OASIS_INLINE__)
#include "SwitchProbe_Impl.inl"
#endif  // !defined __OASIS_INLINE__

namespace OASIS
{
namespace Network
{
namespace Switch
{

//
// create_MemoryProbe_Impl_Factory
//
OASIS_SOFTWARE_PROBE_FACTORY_EXPORT_IMPL (create_OASIS_Network_Switch_SwitchProbe_Impl_Factory,
                                          SwitchProbe_Impl_Factory);

//
// init
//
int SwitchProbe_Impl::init (const char * args, const char * name)
{
  if (0 != ::OASIS::Network::Switch::SwitchProbeImpl::init (args, name))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to init\n")),
                       -1);


  // Parse the command-line options.
  if (0 != this->parse_args (args))
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to parse probe options\n")),
                       -1);

  try
  {
    // Initalize the snmp wrapper
    this->snmp_.init (this->host_.c_str (), this->community_.c_str ());

    // Attach the device oids
    this->uptime_oid_.init (".1.3.6.1.2.1.1.3.0");
    this->cpu_oid_.init (".1.3.6.1.4.1.11.2.14.11.5.1.9.6.1.0");
    this->memory_usage_oid_.init (".1.3.6.1.4.1.11.2.14.11.5.1.1.2.2.1.1.7.1");
    this->total_memory_oid_.init (".1.3.6.1.4.1.11.2.14.11.5.1.1.2.2.1.1.5.1");
    this->snmp_.add_oid (this->uptime_oid_);
    this->snmp_.add_oid (this->cpu_oid_);
    this->snmp_.add_oid (this->memory_usage_oid_);
    this->snmp_.add_oid (this->total_memory_oid_);


    // Populate the port oids
    std::vector <ACE_CString>::iterator arg_it, arg_end, base_it, base_end;
    arg_end = this->port_args_.end ();
    base_end = this->base_port_oids_.end ();
    for (arg_it = this->port_args_.begin (); arg_it != arg_end; arg_it++)
    {
      std::vector <OID> port;
      ACE_CString oid_string;
      for (base_it = this->base_port_oids_.begin (); base_it != base_end; base_it++)
      {
        oid_string = *base_it + *arg_it;
        port.push_back (OID (oid_string.c_str ()));
      }
      this->port_oids_.push_back (port);
    }

    // Attach the oids to the snmp request, net-snmp uses pointers for
    // everything so we have to iterate over the final storage location
    std::vector < std::vector <OID> >::iterator list_it, list_end;
    std::vector <OID>::iterator oid_it, oid_end;
    list_end = this->port_oids_.end ();
    for (list_it = this->port_oids_.begin (); list_it != list_end; list_it++)
    {
      oid_end = (*list_it).end ();
      for (oid_it = (*list_it).begin (); oid_it != oid_end; oid_it++)
        this->snmp_.add_oid(*oid_it);
    }
  }
  catch (std::exception)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to initalize snmp objects\n")),
                       -1);
  }
  return 0;
}

//
// parse_args
//
int SwitchProbe_Impl::parse_args (const char * args)
{
  // Convert the command string into a vector of commands.
  ACE_ARGV_T <char> argv (args);
  const char * optargs = "";

  // Parse the command-line options.
  ACE_Get_Opt get_opt (argv.argc (), argv.argv (), optargs, 0);
  get_opt.long_option ("host", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("community", ACE_Get_Opt::ARG_REQUIRED);
  get_opt.long_option ("port", ACE_Get_Opt::ARG_REQUIRED);

  int opt = 0;

  while (EOF != (opt = get_opt ()))
  {
    switch (opt)
    {
    case 0:
      if (0 == ACE_OS::strcmp ("host", get_opt.long_option ()))
        this->host_ = get_opt.opt_arg ();
      else if (0 == ACE_OS::strcmp ("community", get_opt.long_option ()))
        this->community_ = get_opt.opt_arg ();
      else if (0 == ACE_OS::strcmp ("port", get_opt.long_option ()))
        this->port_args_.push_back (ACE_CString (get_opt.opt_arg ()));
      break;
    }
  }

  return 0;
}

//
// handle_collect_data
//
int SwitchProbe_Impl::handle_collect_data (void)
{
  // Query the device
  if (this->snmp_.query ())
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to execute snmp query\n")),
                       -1);
  try
  {
    // Copy device metrics
    this->uptime_ = this->uptime_oid_.as_long ();
    this->cpu_load_ = this->cpu_oid_.as_long ();
    this->memory_total_ = this->total_memory_oid_.as_long ();
    this->memory_used_ = this->memory_usage_oid_.as_long ();

    // Copy port metrics
    std::vector < std::vector <OID> >::iterator it, end;
    end = this->port_oids_.end ();
    this->ports_.clear ();
    for (it = this->port_oids_.begin (); it != end; it++)
      this->process_port (*it);
  }
  catch (std::exception)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("%T (%t) - %M - failed to read snmp values\n")),
                       -1);
  }

  return 0;
}

//
// process_port
//
void SwitchProbe_Impl::process_port (std::vector <OID> & oids)
{
  SwitchPortImpl port;
  port.description = oids[0].as_string ();
  port.status = oids[1].as_long ();
  port.speed = oids[2].as_long ();
  port.bytes_in = oids[3].as_long ();
  port.discards_in = oids[4].as_long ();
  port.errors_in = oids[5].as_long ();
  port.bytes_out = oids[6].as_long ();
  port.discards_out = oids[7].as_long ();
  port.errors_out = oids[8].as_long ();
  port.queue_length = oids[9].as_long ();
  port.type = oids[10].as_long ();
  this->ports_.push_back (port);
}

} // namespace OASIS
} // namespace Network
} // namespace Switch
